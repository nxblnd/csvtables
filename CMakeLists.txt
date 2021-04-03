cmake_minimum_required(VERSION 3.17)
project(csvtables)

set(CMAKE_CXX_STANDARD 14)

add_executable(csvtables main.cpp Table.cpp Table.h)