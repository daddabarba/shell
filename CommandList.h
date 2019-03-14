//
// Created by daddabarba on 06/03/19.
//

#ifndef SHELL_COMMANDLIST_H
#define SHELL_COMMANDLIST_H

#include <stdlib.h>
#include "Program.h"

typedef struct CommandList {

    size_t num_programs, size_programs;
    int in_fd;
    int out_fd;
    Program **programs;
    int error_code;

    void (*run_commandlist)(struct CommandList*);
    void (*free_commandlist)(struct CommandList*);
    void (*add_program)(struct CommandList*, Program*);

}CommandList;

CommandList* make_CommandList(size_t num_programs);

#endif //SHELL_COMMANDLIST_H
