cmake_minimum_required(VERSION 3.28)
project(GreenSearch)

set(CMAKE_CXX_STANDARD 20)

add_executable(GreenSearch main.cpp
        header.h
        eightProblem.cpp
        Astarsearch.cpp
)
