cmake_minimum_required(VERSION 3.10)
project(toddcox-faster)

add_library(tc STATIC
        src/groups.cpp
        src/solve.cpp
        src/core.cpp)

target_include_directories(tc PUBLIC include)

add_subdirectory(example)
