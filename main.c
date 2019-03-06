#include <stdio.h>
#include <zconf.h>
#include <wait.h>

#include "prompt.h"

#define TRUE 1


int main() {

    int status;
    size_t num_pars;
    char *command, **parameters;

    while(TRUE){
        type_prompt();
        num_pars = read_command(&command, &parameters);
        
        if(fork()!=0){
            waitpid(-1, &status, 0);
        }else{
            execvp(command, parameters);
        }
    }

    return 0;
}