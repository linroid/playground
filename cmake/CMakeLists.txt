cmake_minimum_required(VERSION 2.8)

project(cmake_test)
set(CMAKE_INSTALL_PREFIX ./build)
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

option(USE_MY_MATH "Use provided math implementation" ON)
if(USE_MY_MATH)
    include_directories("${PROJECT_SOURCE_DIR}/math")
    add_subdirectory(math)
    set(EXTRAS_LIBS ${EXTRA_LIBS} math_lib)
endif(USE_MY_MATH)

aux_source_directory(. DIR_SRCS)

add_executable(cmake_test ${DIR_SRCS})

target_link_libraries(cmake_test ${EXTRA_LIBS})

install (TARGETS cmake_test DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)