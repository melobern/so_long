cmake_minimum_required(VERSION 3.24)
project(so_long C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(so_long
        so_long.c)
