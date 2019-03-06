//
// Created by daddabarba on 06/03/19.
//

#ifndef SHELL_PROMPT_H
#define SHELL_PROMPT_H

#include <stdlib.h>

typedef struct Program{
    size_t num_pars;
    char **parameters;
}Program;

void type_prompt(); //print terminal's prompt
size_t read_command(char **command, Program ***programs); //parse command (until \n) and split in instructions

#endif //SHELL_PROMPT_H