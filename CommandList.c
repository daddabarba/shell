//
// Created by daddabarba on 06/03/19.
//

#include "CommandList.h"

#include <zconf.h>
#include <stdio.h>
#include <memory.h>
#include <fcntl.h>

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
    for(; (*index)<buffer_size && buffer[*index]!='|'; (*index)++) {

        if(buffer[*index] == '<' || buffer[*index] == '>'){
            break;
        }

        // split parameter at end of string
        if ((*index) == 0 || buffer[*index - 1] == '\0')
            // parameter just points to part of buffer array (save memory space)
            (*program)->add_parameter(*program, buffer + (*index));
    }

    if(buffer[*index]=='|')
        *index += 2;

    // return parsing status
    if((*program)->num_pars>0) {
        (*program)->parameters = (char **)realloc((*program)->parameters, ((*program)->num_pars+1)*sizeof(char *));
        return 1;
    }

    (*program)->free_program(*program);
    return 0;

}

void m_run_commandlist(CommandList* this){

    int in = this->in_fd; // first program in pipe gets input from stdin

    for (size_t i = 0; i < this->num_programs; i++)
        in = this->programs[i]->run_program(this->programs[i], in);
}

void m_free_commandlist(CommandList* this){

    for (size_t i = 0; i < this->num_programs; i++)
        this->programs[i]->free_program(this->programs[i]);

    if(this->in_fd!=0)
        close(this->in_fd);

    if(this->out_fd!=1)
        close(this->out_fd);

    free(this->buffer);
    free(this->programs);
    free(this);
}

int get_fd(char *buffer, size_t buffer_size, char symbol, int start_index){
    int char_at_index = -1;

    // read char by char
    for(int i = start_index; i < buffer_size; i++) {

        if(buffer[i] == symbol){
            char_at_index = i + 2;
            break;
        }
    }

    if(char_at_index != -1){
        int fd;
        if(symbol == '<'){
            fd = open(&buffer[char_at_index], O_RDONLY);
        }else if(symbol == '>'){
            fd = open(&buffer[char_at_index], O_WRONLY | O_CREAT, S_IWUSR);
        }

        return fd;
    }

    return symbol == '<' ? 0 : 1;
}

CommandList* make_CommandList(){
    //parse command (until \n) and split in instructions

    CommandList* ptr = calloc(1, sizeof(CommandList));
    ptr->in_fd = 0;
    ptr->out_fd = 1;

    ptr->run_commandlist = &m_run_commandlist;
    ptr->free_commandlist = &m_free_commandlist;

    // current number of programs, programs array size, index in buffer, buffer size
    size_t i=0, num_programs = 1, index = 0, buffer_size = read_buffer(&(ptr->buffer));
    ptr->programs = (Program **)calloc(num_programs, sizeof(Program *)); //allocate array of programs

    Program *next_program; // result of program parsing is stored here

    // as long as there is a program to parse
    while(parse_program(buffer_size, ptr->buffer, &next_program, &index) > 0){
        // store it
        (ptr->programs)[i] = next_program;

        if(i>0)
            (ptr->programs)[i-1]->set_pipe((ptr->programs)[i-1]);

        i++;

        // dynamically adjust array size
        if(i == num_programs-1){
            num_programs *= 2;
            (ptr->programs) = (Program **)realloc(ptr->programs, num_programs* sizeof(Program));
        }
    }

    int fd_out = get_fd(ptr->buffer, buffer_size, '>', index);
    int fd_in = get_fd(ptr->buffer, buffer_size, '<', index);

    if(fd_in>0)
        ptr->in_fd = fd_in;

    if(fd_out>0)
        ptr->out_fd = fd_out;

    // perfect fit array size
    ptr->programs = (Program **)realloc(ptr->programs, i*sizeof(Program));
    ptr->num_programs = i;

    ptr->programs[i - 1]->pipe[0] = ptr->out_fd;
    ptr->programs[i - 1]->pipe[1] = ptr->out_fd;

    return ptr;
}