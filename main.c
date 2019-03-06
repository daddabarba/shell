#include <stdio.h>
#include <zconf.h>
#include <wait.h>

#include "prompt.h"

#define TRUE 1


int main() {

    int status;

    size_t num_programs;
    char *buffer; // command in prompt
    struct Program **programs; // array of programs (pipeable) to be run

    while(TRUE) {
        type_prompt();

        // parse programs to run
        num_programs = read_command(&buffer, &programs);

        // run each program
        for (size_t i = 0; i < num_programs; i++){

            if (fork() != 0) {
                waitpid(-1, &status, 0); // serially run the programs one after the other
                free(programs[i]); // free unused data
            } else {
                execvp(programs[i]->parameters[0], programs[i]->parameters);
                break;
            }

        }

        // free buffer and programs before restarting
        free(buffer);
        free(programs);
    }

    return 0;
}