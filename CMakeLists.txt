cmake_minimum_required(VERSION 3.22)
project(feup-dal-proj2)

set(CMAKE_CXX_STANDARD 14)

add_executable(feup-dal-proj2 main.cpp
                src/Graph.cpp includes/Graph.h
                src/Menu.cpp includes/Menu.h)
