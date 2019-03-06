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