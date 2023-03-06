cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(polynomes)

include(CMakeFuncs/functions.cmake)

add_subdirectory(lib)
add_subdirectory(exe)
	add_subdirectory(gtest)
	add_subdirectory(test)
