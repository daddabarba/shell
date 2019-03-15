//
// Created by daddabarba on 3/14/19.
//

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#include "Program.h"
#include "CommandList.h"
#include "Process.h"

size_t read_buffer(char **buffer){
    // read the full stdin buffer (command) up to '\n'

    char cc;
    size_t i=0, buffer_size = 20; // currect index in buffer and total buffer size
    *buffer = (char *)calloc(buffer_size, sizeof(char)); // allocate buffer
    short in_string = 0;

    // read char by char
    while((cc = (char)getchar()) > 0 && cc!='\n') {

        // ignore spaces

        if(cc == '\"') {
            in_string = !in_string;
            continue;
        }

        if(cc != ' ' || in_string) {
            // pad < or > with \0
            if((cc == '<' || cc == '>') && !in_string){
                //check if \0 wasnt added already
                if((*buffer)[i-1] != '\0'){
                    (*buffer)[i] = '\0';
                    i++;
                }

                // add symbol
                (*buffer)[i] = cc;
                i++;

                (*buffer)[i] = '\0';
                i++;
            } else {
                (*buffer)[i] = cc;
                i++;
            }
        } else if(i==0 || (*buffer)[i-1]!='\0') { // first space means split of string (parameter)
            (*buffer)[i] = '\0';
            i++;
        }

        // dynamically adjust buffer size
        if(i == buffer_size-5){
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

void skip_word(size_t buffer_size, char *buffer, size_t *index){
    // skip to next buffer substring
    for(; (*index)<buffer_size && buffer[*index]!='\0'; (*index)++);
    (*index)++; // start of next sub-string
}

unsigned short parse_program(size_t buffer_size, char *buffer, Program **program, size_t *index){
    // parse the command for a single program in $PATH

    *program = make_Program(20);

    // read the buffer (until the program part ends)
    for(; (*index)<buffer_size; skip_word(buffer_size, buffer, index)) {

        // Stop characters for program
        if(buffer[*index] == '<' || buffer[*index] == '>' || buffer[*index] == '&' || buffer[*index]=='|')
            break;

        // parameter just points to part of buffer array (save memory space)
        (*program)->add_parameter(*program, buffer + (*index));
    }

    // return parsing status
    if((*program)->num_pars>0) {
        (*program)->parameters = (char **)realloc((*program)->parameters, ((*program)->num_pars+1)*sizeof(char *));
        return 1;
    }

    (*program)->free_program(*program);
    return 0;

}

int parse_commandlist(size_t buffer_size, char* buffer, CommandList **ptr, size_t *index){


    char *file_in = NULL, *file_out = NULL;
    *ptr = make_CommandList(1);

    Program *next_program; // result of program parsing is stored here

    // as long as there is a program to parse
    // read the buffer (until the program part ends)
    while((*index)<buffer_size) {

        // Stop characters for program
        if(buffer[*index] == '<' || buffer[*index] == '>' || buffer[*index] == '&')
            break;

        if(buffer[*index] == '|') { //skip this characters
            (*index) += 2;
            continue;
        }

        if(!parse_program(buffer_size, buffer, &next_program, index))
            break;

        (*ptr)->add_program(*ptr, next_program);
    }

    if((*ptr)->num_programs<1) {
        (*ptr)->free_commandlist(*ptr);
        return 0;
    }

    // perfect fit array size
    (*ptr)->programs = (Program **)realloc((*ptr)->programs, (*ptr)->num_programs*sizeof(Program));

    // Parse I/O redirection
    for(; (*index)<buffer_size; skip_word(buffer_size, buffer, index)){

        if(buffer[*index]!='>' && buffer[*index]!='<')
            break;

        if(buffer[*index]=='<'){

            if(file_in != NULL || (*index+2)>=buffer_size){
                (*ptr)->error_code = 2;
                return 1;
            }

            file_in = buffer + (*index +=2);
        }

        if(buffer[*index]=='>'){

            if(file_out != NULL || (*index+2)>=buffer_size){
                (*ptr)->error_code = 2;
                return 1;
            }

            file_out = buffer + (*index+=2);
        }

    }

    if(file_in != NULL && file_out != NULL && strcmp(file_in, file_out) == 0){
        (*ptr)->error_code = 1;
        return 1;
    }

    if(file_in!=NULL)
        (*ptr)->in_fd = open(file_in, O_RDONLY);

    if(file_out!=NULL)
        (*ptr)->out_fd = open(file_out, O_WRONLY | O_CREAT, S_IWUSR);

    if((*ptr)->out_fd < 0 || (*ptr)->in_fd < 0) {
        (*ptr)->error_code = 2;
        return 1;
    }

    (*ptr)->programs[(*ptr)->num_programs - 1]->pipe[0] = (*ptr)->out_fd;
    (*ptr)->programs[(*ptr)->num_programs - 1]->pipe[1] = (*ptr)->out_fd;
    return 1;
}

Process* parse_Process(){


    size_t index = 0;
    Process* ptr = make_Process(1);
    size_t buffer_size = read_buffer(&(ptr->buffer));

    CommandList *new_commandlist;

    while(index<buffer_size) {

        if((ptr->buffer)[index] == '&') { // skip this character
            (index) +=2;
            continue;
        }

        if(!parse_commandlist(buffer_size, ptr->buffer, &new_commandlist, &index))
            break;

        ptr->add_commandlist(ptr, new_commandlist);
    }

    ptr->commandLists = (CommandList**)realloc(ptr->commandLists, ptr->num_processes*sizeof(CommandList*));

    return ptr;
}
