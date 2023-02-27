cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(polynomes)

include(CMakeFuncs/functions.cmake)

add_subdirectory(lib)
add_subdirectory(exe)

option(BTEST "build test?" OFF)

if(BTEST)
    add_subdirectory(GTests)
    add_subdirectory(test_main)
endif()
