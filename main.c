#include <stdio.h>
#include <memory.h>
#include <wait.h>

#include "prompt.h"
#include "builtInCommands.h"
#include "Parsing.h"

#define TRUE 1

int main() {

    setbuf(stdout, NULL);

    Process *cl;

    while(TRUE){

        type_prompt();

        // parse programs to run
        cl = parse_Process();

        if(strlen(cl->buffer) == 0) {
            cl->free_processes;
            continue;
        }

        if((*cl->commandLists)->error_code == 1){
            printf("Error: input and output files cannot be equal!\n");
            cl->free_processes(cl);
            continue;
        } else if((*cl->commandLists)->error_code == 2){
            printf("Invalid syntax!\n");
            cl->free_processes(cl);
            continue;
        }

        int status;
        // Might have to check for still running processes
        if(!strcmp(cl->buffer, "exit")){

            cl->free_processes(cl);

            if(waitpid(-1, &status, WNOHANG) == 0){
                printf("There are still background processes running!\n");
                continue;
            }
            else {
                break;
            }
        }else if(cl->num_processes==1
            && cl->commandLists[0]->num_programs == 1
            && cl->commandLists[0]->programs[0]->num_pars == 2
            && !strcmp(cl->commandLists[0]->programs[0]->parameters[0], "cd")){

            cdFunc(cl->commandLists[0]->programs[0]->parameters[1]);
            continue;
        }

        // run each program
        cl->run_processes(cl);

        cl->free_processes(cl);
    }

    return 0;
}