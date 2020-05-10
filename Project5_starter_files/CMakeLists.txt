cmake_minimum_required(VERSION 3.14)
project(Project5_starter_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project5_starter_files
        header.txt
        main.cpp
        Makefile
        Project5.cpp
        Set.h)
