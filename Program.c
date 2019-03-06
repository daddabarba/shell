//
// Created by daddabarba on 06/03/19.
//

#include "Program.h"

#include <zconf.h>
#include <wait.h>

void m_free_program(Program *this){
    free(this->parameters);
    free(this);
}

void m_add_parameter(Program *this, char *parameter){
    this->parameters[this->num_pars] = parameter;
    this->num_pars++;

    if( (this->num_pars) == (this->size_pars -1) ){
        this->size_pars*=2;
        this->parameters = (char **)realloc(this->parameters, this->size_pars*sizeof(char*));
    }
}

void m_run(Program* this){

    int status;

    if(fork() != 0) {
        waitpid(-1, &status, 0);
        this->free_program(this);
    } else {
        execvp(this->parameters[0], this->parameters);
    }
}

Program* make_Program(size_t num_pars){

    Program* ptr = calloc(1, sizeof(Program));

    ptr->num_pars = 0;
    ptr->size_pars = num_pars;
    ptr->parameters = (char **)calloc(num_pars, sizeof(char *));

    ptr->run = &m_run;
    ptr->add_parameter = &m_add_parameter;
    ptr->free_program = &m_free_program;

    return ptr;
}