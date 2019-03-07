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

    int pipe[2];
    unsigned short piped;

    int (*run_program)(struct Program*, int in);
    void (*add_parameter)(struct Program*, char *parameter);
    int (*set_pipe)(struct Program*);
    void (*free_program)(struct Program*);
}Program;

Program* make_Program(size_t num_pars);

#endif //SHELL_PROGRAM_H
