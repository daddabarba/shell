//
// Created by daddabarba on 06/03/19.
//

#ifndef SHELL_COMMANDLIST_H
#define SHELL_COMMANDLIST_H

#include <stdlib.h>
#include "Program.h"

typedef struct CommandList {

    size_t num_programs;
    char *buffer;
    Program **programs;

    void (*run_commandlist)(struct CommandList*);
    void (*free_commandlist)(struct CommandList*);

}CommandList;

CommandList* make_CommandList();

#endif //SHELL_COMMANDLIST_H
