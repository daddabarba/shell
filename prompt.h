//
// Created by daddabarba on 06/03/19.
//

#ifndef SHELL_PROMPT_H
#define SHELL_PROMPT_H

#include <stdlib.h>

void type_prompt();
size_t read_command(char **command, char ***parameters);

#endif //SHELL_PROMPT_H