//
// Created by daddabarba on 08/03/19.
//

#include "Process.h"

#include <stdio.h>
#include <unistd.h>
#include <wait.h>

void m_add_command_list(Process *this, CommandList *new){

    this->commandLists[this->num_processes] = new;
    this->num_processes++;

    if(this->num_processes == this->size_commandlists){
        this->size_commandlists*=2;
        this->commandLists = realloc(this->commandLists, this->size_commandlists*sizeof(CommandList*));
    }

}

void m_run_processes(Process*this) {

    for (size_t i = 0; i < (this->num_processes -1); i++){

        if(fork() == 0) {
            if (fork() != 0) {

                int status;
                waitpid(-1, &status, 0);

                this->commandLists[i]->free_commandlist(this->commandLists[i]);

                exit(0);
            } else {

                this->commandLists[i]->run_commandlist(this->commandLists[i]);
                exit(0);
            }
        }
    }

    this->commandLists[this->num_processes -1]->run_commandlist(this->commandLists[this->num_processes -1]);
}

void m_free_process(Process* this){


    this->commandLists[this->num_processes -1]->free_commandlist(this->commandLists[this->num_processes -1]);


    free(this->commandLists);
    free(this->buffer);
    free(this);
}

Process* make_Process(size_t num_commandlists){

    Process* ptr = calloc(1, sizeof(Process));

    ptr->run_processes = &m_run_processes;
    ptr->add_commandlist = &m_add_command_list;
    ptr->free_processes = &m_free_process;

    ptr->num_processes = 0;
    ptr->size_commandlists = num_commandlists;
    ptr->buffer = NULL;
    ptr->commandLists = calloc(num_commandlists, sizeof(CommandList*));

}