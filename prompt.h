//
// Created by daddabarba on 06/03/19.
//

#ifndef SHELL_PROMPT_H
#define SHELL_PROMPT_H

#include <stdlib.h>
#include "Program.h"

void type_prompt(); //print terminal's prompt
size_t read_command(char **command, Program ***programs); //parse command (until \n) and split in instructions

#endif //SHELL_PROMPT_H