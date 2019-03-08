//
// Created by daddabarba on 08/03/19.
//

#ifndef SHELL_PROCESS_H
#define SHELL_PROCESS_H

#include "CommandList.h"

typedef struct Process{

    char *buffer;
    size_t num_processes, size_commandlists;
    CommandList **commandLists;

    void (*run_processes)(struct Process*);
    void (*free_processes)(struct Process*);

    void (*add_commandlist)(struct Process*, CommandList*);

}Process;

Process* make_Process();
Process* parse_Process();

#endif //SHELL_PROCESS_H
