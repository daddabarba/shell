//
// Created by daddabarba on 06/03/19.
//

#include "Program.h"

#include <unistd.h>
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

    int status, child_pid;

    if ((child_pid = fork()) != 0){
        waitpid(child_pid, &status, 0);
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

        exit(0);
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