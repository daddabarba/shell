//
// Created by daddabarba on 3/17/19.
//

#include "builtInCommand.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void cdFunc(char* path){

    char dir[256];

    // if it is a relative path
    if(path[0] == '.') {
        getcwd(dir, sizeof(dir));
        strcat(dir, "/");
        strcat(dir, path);
    } else{
        strcpy(dir, path);
    }

    chdir(dir);
}