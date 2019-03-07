#include <stdio.h>
#include <zconf.h>
#include <memory.h>

#include "prompt.h"
#include "CommandList.h"

#define TRUE 1

int main() {

    CommandList *cl;

    int a = 5;

    while(TRUE){
        type_prompt();

        // parse programs to run
        cl = make_CommandList();

        // Might have to check for still running processes
        if(!strcmp(cl->buffer, "exit")){
            break;
        }

        // run each program
        cl->run_commandlist(cl);
        cl->free_commandlist(cl);
    }

    return 0;
}