cmake_minimum_required(VERSION 3.10)
project(toddcox-faster)

option(TC_BUILD_EXAMPLE "Build example executables" OFF)

add_library(tc STATIC
        src/groups.cpp
        src/solve.cpp
        src/core.cpp)

target_include_directories(tc PUBLIC include)

if (TC_BUILD_EXAMPLE)
    add_subdirectory(example)
endif ()
