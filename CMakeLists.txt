cmake_minimum_required(VERSION 3.13)
project(shell C)

set(CMAKE_C_STANDARD 11)

set(SOURCES ${SOURCES}
        ./prompt.c
        ./prompt.h
        ./Program.c
        ./Program.h
        ./CommandList.c
        ./CommandList.h
)

add_executable(shell main.c ${SOURCES})