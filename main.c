#include <stdio.h>
#include <zconf.h>

#include "prompt.h"

#define TRUE 1

int main() {

    size_t num_programs;
    char *buffer; // command in prompt
    struct Program **programs; // array of programs (pipeable) to be run

    while(TRUE) {
        type_prompt();

        // parse programs to run
        num_programs = read_command(&buffer, &programs);

        // run each program
        for (size_t i = 0; i < num_programs; i++)
            programs[i]->run(programs[i]);

        // free buffer and programs before restarting
        free(buffer);
        free(programs);
    }

    return 0;
}