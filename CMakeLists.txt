cmake_minimum_required(VERSION 3.0)
project(csvtables)

set(CMAKE_CXX_STANDARD 11)

add_executable(csvtables main.cpp Table.cpp Table.h Formula.cpp Formula.h)