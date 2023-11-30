cmake_minimum_required(VERSION 3.26)
project(joske_coder)

set(CMAKE_CXX_STANDARD 17)

add_executable(joske_coder main.cpp
        dictionary.cpp
        dictionary.h)
