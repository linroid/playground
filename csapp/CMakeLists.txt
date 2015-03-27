cmake_minimum_required(VERSION 3.1)
project(csapp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    chapter11/client.c
    chapter11/dd2hex.c
    chapter11/hex2dd.c
    chapter11/hostinfo.c
    chapter11/server.c
    csapp.c
    csapp.h
    showbytes.c
    showbytes.h
    template.c)

add_executable(csapp ${SOURCE_FILES})