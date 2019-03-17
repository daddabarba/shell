//
// Created by daddabarba on 3/17/19.
//

#include "prompt.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int command_in_line(char *argv[]){

    int pipeFD[2], childPID, status;

    if(pipe(pipeFD)<0){
        fprintf(stderr, "Could not make pipe for username process\n");
        return (EXIT_FAILURE);
    }

    if((childPID = fork())!=0){

        close(pipeFD[1]);

        char cc;

        waitpid(childPID, & status, 0);

        while(read(pipeFD[0], &cc, 1)>0 && cc!='\n')
            putchar(cc);

        close(pipeFD[0]);
    }else{

        close(pipeFD[0]);
        dup2(pipeFD[1],1);

        execvp(argv[0], argv);

        close(pipeFD[1]);
        exit(0);
    }

}

int type_username(){
    char *argv[2];

    argv[0] = "whoami";
    argv[1] = NULL;

    return command_in_line(argv);
}

int type_directory(){
    char *argv[2];

    argv[0] = "pwd";
    argv[1] = NULL;

    return command_in_line(argv);
}

void type_prompt(){
    type_username();
    putchar('@');
    type_directory();
    printf("> ");
}
