cmake_minimum_required(VERSION 3.7)
project(BCoint)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES library.c library.h)
add_library(BCoint ${SOURCE_FILES})