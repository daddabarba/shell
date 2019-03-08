//
// Created by daddabarba on 06/03/19.
//

#ifndef SHELL_COMMANDLIST_H
#define SHELL_COMMANDLIST_H

#include <stdlib.h>
#include "Program.h"

typedef struct CommandList {

    size_t num_programs;
    int in_fd;
    int out_fd;
    Program **programs;

    void (*run_commandlist)(struct CommandList*);
    void (*free_commandlist)(struct CommandList*);

}CommandList;

CommandList* make_CommandList();
int parse_commandlist(size_t buffer_size, char *buffer, CommandList **ptr, size_t *index);

#endif //SHELL_COMMANDLIST_H
