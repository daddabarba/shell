#include <stdio.h>
#include <zconf.h>

#include "prompt.h"
#include "CommandList.h"

#define TRUE 1

int main() {

    CommandList *cl;

    while(TRUE){
        type_prompt();

        // parse programs to run
        cl = make_CommandList();

        // run each program
        cl->run_commandlist(cl);
        cl->free_commandlist(cl);
    }

    return 0;
}