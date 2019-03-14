//
// Created by daddabarba on 06/03/19.
//

#include "Program.h"

#include <zconf.h>
#include <wait.h>
#include <stdio.h>

void m_free_program(Program *this){

    if(this->piped) {
        close(this->pipe[0]);
        close(this->pipe[1]);
    }

    free(this->parameters);
    free(this);
}

int m_set_pipe(Program *this){

    this->piped = 1;

    if(this->pipe[0] == 1 && this->pipe[1] == 1) 
        return pipe(this->pipe);
}

void m_add_parameter(Program *this, char *parameter){
    this->parameters[this->num_pars] = parameter;
    this->num_pars++;

    if( (this->num_pars) == (this->size_pars -1) ){
        this->size_pars*=2;
        this->parameters = (char **)realloc(this->parameters, this->size_pars*sizeof(char*));
    }
}

int m_run_program(Program* this, int in) {

    int status;

    if (fork() != 0){
        waitpid(-1, &status, 0);
        return this->pipe[0];
    }else{

        if(this->piped)
            close(this->pipe[0]);

        dup2(this->pipe[1], 1); // write in pipe (or stdout by default)
        dup2(in, 0);

        int result = 1;
        result = execvp(this->parameters[0], this->parameters);
        if(result == -1){
            printf("Error: command not found!\n");
        }

        if(this->piped)
            close(this->pipe[1]);
    }
}

Program* make_Program(size_t num_pars){

    Program* ptr = calloc(1, sizeof(Program));

    ptr->run_program = &m_run_program;
    ptr->add_parameter = &m_add_parameter;
    ptr->free_program = &m_free_program;
    ptr->set_pipe = &m_set_pipe;

    ptr->num_pars = 0;
    ptr->size_pars = num_pars;
    ptr->parameters = (char **)calloc(num_pars, sizeof(char *));

    ptr->piped = 0;
    ptr->pipe[0] = 1;
    ptr->pipe[1] = 1;

    return ptr;
}

unsigned short parse_program(size_t buffer_size, char *buffer, Program **program, size_t *index){
    // parse the command for a single program in $PATH

    size_t tot_pars = 20; // size of parameters array and current number of parameters
    *program = make_Program(tot_pars);

    // read the buffer (until the program part ends)
    for(; (*index)<buffer_size && buffer[*index]!='|'; (*index)++) {

        if(buffer[*index] == '<' || buffer[*index] == '>' || buffer[*index] == '&'){
            break;
        }

        // split parameter at end of string
        if ((*index) == 0 || buffer[*index - 1] == '\0')
            // parameter just points to part of buffer array (save memory space)
            (*program)->add_parameter(*program, buffer + (*index));
    }

    if(buffer[*index]=='|')
        *index += 2;

    // return parsing status
    if((*program)->num_pars>0) {
        (*program)->parameters = (char **)realloc((*program)->parameters, ((*program)->num_pars+1)*sizeof(char *));
        return 1;
    }

    (*program)->free_program(*program);
    return 0;

}