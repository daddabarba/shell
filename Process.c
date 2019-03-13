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

    if(this->num_processes == this->size_commandlists-1){
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

size_t read_buffer(char **buffer){
    // read the full stdin buffer (command) up to '\n'

    char cc;
    size_t i=0, buffer_size = 20; // currect index in buffer and total buffer size
    *buffer = (char *)calloc(buffer_size, sizeof(char)); // allocate buffer
    short in_string = 0;

    // read char by char
    while((cc = (char)getchar()) > 0 && cc!='\n') {

        // ignore spaces

        if(cc == '\"')
            in_string = !in_string;

        if(cc != ' ' || in_string) {
            (*buffer)[i] = cc;
            i++;
        } else if(i==0 || (*buffer)[i-1]!='\0') { // first space means split of string (parameter)
            (*buffer)[i] = '\0';
            i++;
        }

        // dynamically adjust buffer size
        if(i == buffer_size-2){
            buffer_size *= 2;
            *buffer = realloc(*buffer, buffer_size*sizeof(char));
        }
    }

    // perfect fit of buffer
    (*buffer)[i] = '\0';
    *buffer = realloc(*buffer, (i+1)* sizeof(char));

    // return final size
    return i;
}

Process* parse_Process(){


    size_t index = 0;
    Process* ptr = make_Process(1);
    size_t buffer_size = read_buffer(&(ptr->buffer));

    CommandList *new_commandlist;

    while(parse_commandlist(buffer_size, ptr->buffer, &new_commandlist, &index) > 0)
        ptr->add_commandlist(ptr, new_commandlist);

    ptr->commandLists = realloc(ptr->commandLists, ptr->num_processes*sizeof(CommandList));

    return ptr;
}