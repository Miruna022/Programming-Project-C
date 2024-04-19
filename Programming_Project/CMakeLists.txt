cmake_minimum_required(VERSION 3.27)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        "Headers/menu functions.h"
        "Sources/menu functions.c"
        Sources/donate.c
        Headers/donate.h
        Sources/search.c
        Sources/borrow.c
        Headers/borrow.h
        Sources/return.c
        Headers/return.h
)
