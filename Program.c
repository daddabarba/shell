//
// Created by daddabarba on 06/03/19.
//

#include "Program.h"

#include <zconf.h>

void m_free_program(Program *this){
    free(this->parameters);
    free(this);
}

void m_run(Program* this){
    execvp(this->parameters[0], this->parameters);
}

Program* make_Program(size_t num_pars){

    Program* ptr = calloc(1, sizeof(Program));

    ptr->num_pars = num_pars;
    ptr->parameters = (char **)calloc(num_pars, sizeof(char *));

    ptr->run = &m_run;
    ptr->free_program = &m_free_program;

    return ptr;
}