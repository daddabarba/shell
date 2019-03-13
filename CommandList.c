//
// Created by daddabarba on 06/03/19.
//

#include "CommandList.h"

#include <zconf.h>
#include <stdio.h>
#include <memory.h>
#include <fcntl.h>

void m_run_commandlist(CommandList* this){

    int in = this->in_fd; // first program in pipe gets input from stdin

    for (size_t i = 0; i < this->num_programs; i++)
        this->programs[i]->run_program(this->programs[i], in);
}

void m_free_commandlist(CommandList* this){

    for (size_t i = 0; i < this->num_programs; i++)
        this->programs[i]->free_program(this->programs[i]);

    if(this->in_fd!=0)
        close(this->in_fd);

    if(this->out_fd!=1)
        close(this->out_fd);

    free(this->programs);
    free(this);
}

int get_fd(char *buffer, char symbol, int index){

    if(index != -1){
        int fd;
        if(symbol == '<'){
            fd = open(&buffer[index], O_RDONLY);
        }else if(symbol == '>'){
            fd = open(&buffer[index], O_WRONLY | O_CREAT, S_IWUSR);
        }

        return fd;
    }

    return symbol == '<' ? 0 : 1;
}

int get_index_file(char *buffer, size_t buffer_size, char symbol, int *start_index){
    int char_at_index = -1;

    // read char by char
    for(int i = *start_index; i < buffer_size && buffer[i]!='&'; i++) {

        if(buffer[i] == symbol){
            char_at_index = i + 2;
            break;
        }
    }

    return char_at_index;
}

CommandList* make_CommandList(){
    //parse command (until \n) and split in instructions

    CommandList* ptr = calloc(1, sizeof(CommandList));
    ptr->in_fd = 0;
    ptr->out_fd = 1;

    ptr->run_commandlist = &m_run_commandlist;
    ptr->free_commandlist = &m_free_commandlist;

    return ptr;
}

int parse_commandlist(size_t buffer_size, char* buffer, CommandList **ptr, size_t *index){

    *ptr = make_CommandList();

    // current number of programs, programs array size, index in buffer, buffer size
    size_t i=0, num_programs = 1;
    (*ptr)->programs = (Program **)calloc(num_programs, sizeof(Program *)); //allocate array of programs

    Program *next_program; // result of program parsing is stored here

    // as long as there is a program to parse
    while(buffer[*index]!= '&' && parse_program(buffer_size, buffer, &next_program, index) > 0){
        // store it
        ((*ptr)->programs)[i] = next_program;

        if(i>0)
            ((*ptr)->programs)[i-1]->set_pipe(((*ptr)->programs)[i-1]);

        i++;

        // dynamically adjust array size
        if(i == num_programs-1){
            num_programs *= 2;
            ((*ptr)->programs) = (Program **)realloc((*ptr)->programs, num_programs* sizeof(Program));
        }
    }

    if(i<1) {
        (*ptr)->free_commandlist(*ptr);
        return 0;
    }

    int out_index = get_index_file(buffer, buffer_size, '>', (int*)index);
    int in_index = get_index_file(buffer, buffer_size, '<', (int*)index);

    if(out_index != -1 && in_index != -1 && strcmp(buffer + out_index + 2, buffer + in_index + 2) == 0){
        (*ptr)->error_code = 1;
        return 1;
    }

    int fd_out = get_fd(buffer, '>', out_index);
    int fd_in = get_fd(buffer, '<', in_index);

    while(*index < buffer_size && buffer[*index]!='&')
        (*index)++;

    if(*index < buffer_size)
        (*index)+=2;

    if(fd_in >= 0 && fd_out >= 0){
        (*ptr)->in_fd = fd_in;
        (*ptr)->out_fd = fd_out;
    } else {
        (*ptr)->error_code = 2;
        return 1;
    }
    // perfect fit array size
    (*ptr)->programs = (Program **)realloc((*ptr)->programs, i*sizeof(Program));
    (*ptr)->num_programs = i;

    (*ptr)->programs[i - 1]->pipe[0] = (*ptr)->out_fd;
    (*ptr)->programs[i - 1]->pipe[1] = (*ptr)->out_fd;

    (*ptr)->error_code = 0;

    return 1;
}