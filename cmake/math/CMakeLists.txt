cmake_minimum_required(VERSION 2.8)
project(math_lib)
aux_source_directory(. DIR_LIB_SRCS)

add_library(math_lib ${DIR_LIB_SRCS})
install(TARGETS math_lib DESTINATION bin)
install(FILES math.h  DESTINATION include)