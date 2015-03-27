cmake_minimum_required(VERSION 3.1)
project(Tiny)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
add_executable(Tiny ${SOURCE_FILES} tiny.h tiny.c io.h io.c http.h http.c)