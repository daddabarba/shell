#include <stdio.h>
#include <zconf.h>
#include <wait.h>

#include "prompt.h"

#define TRUE 1


int main() {

    int status;
    char *command, **parameters;

    while(TRUE){
        type_prompt();
        read_command(command, parameters);

        if(fork()!=0){
            waitpid(-1, &status, 0);
        }else{
            execve(command, parameters, 0);
        }
    }

    return 0;
}