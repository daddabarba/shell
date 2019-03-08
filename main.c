#include <stdio.h>
#include <zconf.h>
#include <memory.h>

#include "prompt.h"
#include "Process.h"

#define TRUE 1

int main() {

    Process *cl;

    while(TRUE){
        type_prompt();

        // parse programs to run
        cl = parse_Process();

        // Might have to check for still running processes
        if(!strcmp(cl->buffer, "exit")){
            break;
        }

        // run each program
        cl->run_processes(cl);
        cl->free_processes(cl);
    }

    return 0;
}