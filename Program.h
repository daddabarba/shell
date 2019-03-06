//
// Created by daddabarba on 06/03/19.
//

#ifndef SHELL_PROGRAM_H
#define SHELL_PROGRAM_H

#include <stdlib.h>

typedef struct Program{
    size_t num_pars;
    size_t size_pars;
    char **parameters;

    void (*run_program)(struct Program*);
    void (*add_parameter)(struct Program*, char *parameter);
    void (*free_program)(struct Program*);
}Program;

Program* make_Program(size_t num_pars);

#endif //SHELL_PROGRAM_H
