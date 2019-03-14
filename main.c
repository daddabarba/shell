#include <stdio.h>
#include <memory.h>
#include <wait.h>

#include "Parsing.h"

#define TRUE 1

int main() {

    setbuf(stdout, NULL);

    Process *cl;

    while(TRUE){

        // parse programs to run
        cl = parse_Process();

        if((*cl->commandLists)->error_code == 1){
            printf("Error: input and output files cannot be equal!\n");
            continue;
        } else if((*cl->commandLists)->error_code == 2){
            printf("Invalid syntax!\n");
            continue;
        }

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