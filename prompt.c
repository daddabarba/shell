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

size_t read_word(char **string, char *last_char){
    char cc;

    size_t i, word_size = 20;
    *string = (char *)calloc(sizeof(char), word_size);

    for(i=0; (cc = (char)getchar()) > 0 && cc!=' ' && cc!='\n'; i++) {
        (*string)[i] = cc;

        if(i == word_size-2){
            word_size *= 2;
            *string = realloc(*string, word_size);
        }
    }

    *last_char = cc;
    (*string)[i] = '\0';

    *string = realloc(*string, i+1);
    return i;
}

size_t read_command(char **command, char ***parameters){

    size_t i=1, num_pars = 5;
    char last_char;
    *parameters = (char **)calloc(sizeof(char *), num_pars);

    read_word(command, &last_char);
    (*parameters)[0] = *command;

    while(last_char != '\n'){

        read_word(*parameters + i, &last_char);

        if(i == num_pars-1){
            num_pars *= 2;
            *parameters = realloc(*parameters, num_pars);
        }

        i++;
    }

    *parameters = realloc(*parameters, i);
    return i;
}