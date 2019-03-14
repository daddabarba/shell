//
// Created by daddabarba on 06/03/19.
//

#include "CommandList.h"


#include <unistd.h>
#include <memory.h>
#include <fcntl.h>

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

    free(this->programs);
    free(this);
}

void m_add_program(CommandList* this, Program* p){

    (this->programs)[this->num_programs] = p;

    // If more than one program, pipe the previous one with the following
    if(this->num_programs>0)
        (this->programs)[this->num_programs-1]->set_pipe((this->programs)[this->num_programs-1]);

    this->num_programs++;

    if( this->num_programs >= (this->size_programs-1) ){
        this->size_programs *=2;
        this->programs = (Program**)realloc(this->programs, this->size_programs*sizeof(Program*));
    }

}

CommandList* make_CommandList(size_t num_programs){
    //parse command (until \n) and split in instructions

    CommandList* ptr = calloc(1, sizeof(CommandList));
    ptr->in_fd = 0;
    ptr->out_fd = 1;

    ptr->run_commandlist = &m_run_commandlist;
    ptr->free_commandlist = &m_free_commandlist;
    ptr->add_program = &m_add_program;

    ptr->num_programs = 0;
    ptr->size_programs = num_programs;

    ptr->error_code = 0;

    ptr->programs = (Program **)calloc(num_programs, sizeof(Program *)); //allocate array of programs

    return ptr;
}