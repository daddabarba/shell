#include <stdio.h>
#include <memory.h>
#include <wait.h>

#include "Process.h"

#define TRUE 1

int main() {

    Process *cl;

    while(TRUE){

        // parse programs to run
        cl = parse_Process();

        int status;
        // Might have to check for still running processes
        if(!strcmp(cl->buffer, "exit")){
            if(waitpid(-1, &status, WNOHANG) == 0){
                printf("There are still background processes running!\n");
                continue;
            }
            else {
                break;
            }
        }

        // run each program
        cl->run_processes(cl);
        cl->free_processes(cl);
    }

    return 0;
}