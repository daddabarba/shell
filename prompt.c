//
// Created by daddabarba on 06/03/19.
//

#include "prompt.h"

#include <stdio.h>
#include <zconf.h>
#include <malloc.h>

void type_prompt(){
    write(1, ">> ", 3);
}

size_t read_buffer(char **buffer){
    // read the full stdin buffer (command) up to '\n'

    char cc;
    size_t i=0, buffer_size = 20; // currect index in buffer and total buffer size
    *buffer = (char *)calloc(buffer_size, sizeof(char)); // allocate buffer

    // read char by char
    while((cc = (char)getchar()) > 0 && cc!='\n') {

        // ignore spaces
        if(cc != ' ') {
            (*buffer)[i] = cc;
            i++;
        } else if(i==0 || (*buffer)[i-1]!='\0') { // first space means split of string (parameter)
            (*buffer)[i] = '\0';
            i++;
        }

        // dynamically adjust buffer size
        if(i == buffer_size-2){
            buffer_size *= 2;
            *buffer = realloc(*buffer, buffer_size*sizeof(char));
        }
    }

    // perfect fit of buffer
    (*buffer)[i] = '\0';
    *buffer = realloc(*buffer, (i+1)* sizeof(char));

    // return final size
    return i;
}

unsigned short parse_program(size_t buffer_size, char *buffer, Program **program, size_t *index){
    // parse the command for a single program in $PATH

    size_t tot_pars = 20; // size of parameters array and current number of parameters
    *program = make_Program(tot_pars);

    // read the buffer (until the program part ends)
    for(; (*index)<buffer_size; (*index)++)
        // split parameter at end of string
        if ((*index) == 0 || buffer[*index - 1] == '\0')
            // parameter just points to part of buffer array (save memory space)
            (*program)->add_parameter(*program, buffer+(*index));

    // return parsing status
    if((*program)->num_pars>0) {
        (*program)->parameters = (char **)realloc((*program)->parameters, ((*program)->num_pars+1)*sizeof(char *));
        return 1;
    }

    (*program)->free_program(*program);
    return 0;

}

size_t read_command(char **command, Program ***programs){
    //parse command (until \n) and split in instructions

    // current number of programs, programs array size, index in buffer, buffer size
    size_t i=0, num_programs = 2, index = 0, buffer_size = read_buffer(command);

    Program *next_program; // result of program parsing is stored here
    *programs = (Program **)calloc(num_programs, sizeof(Program *)); //allocate array of programs

    // as long as there is a program to parse
    while(parse_program(buffer_size, *command, &next_program, &index) > 0){

        // store it
        (*programs)[i] = next_program;
        i++;

        // dynamically adjust array size
        if(i == num_programs-1){
            num_programs *= 2;
            *programs = (Program **)realloc(*programs, num_programs* sizeof(Program));
        }
    }

    // perfect fit array size
    *programs = (Program **)realloc(*programs, i*sizeof(Program));
    return i;
}