cmake_minimum_required(VERSION 3.2)

project(c-algorithms)

set(CMAKE_CXX_FLAGS "-std=c++11")


set(CXX_FLAGS
    -g
    # -DVALGRIND
    # -DCHECK_PTHREAD_RETURN_VALUE
    # -D_FILE_OFFSET_BITS=64
    #-Wall
    # -Wextra
    -fpermissive
    # -Werror
    # -Wconversion
    # -Wno-unused-parameter
    # -Wold-style-cast
    # -Woverloaded-virtual
    # -Wpointer-arith
    # -Wshadow
    # -Wwrite-strings
    # -march=native
)

message(STATUS "==========" ${PROJECT_SOURCE_DIR})

include_directories("${PROJECT_SOURCE_DIR}/inc/")

add_subdirectory(src/)