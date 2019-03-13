cmake_minimum_required(VERSION 3.13)
project(shell C)

set(CMAKE_C_STANDARD 11)

set(SOURCES ${SOURCES}
        ./Program.c
        ./Program.h
        ./CommandList.c
        ./CommandList.h
        ./Process.c
        ./Program.h
)

add_executable(shell main.c ${SOURCES})