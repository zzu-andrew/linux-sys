cmake_minimum_required(VERSION 3.2)

project(c-algorithms)


add_executable(array_list
        array_list/main.cpp
        array_list/array_list.cpp)
#target_link_libraries(array_list pthread)
target_include_directories(array_list
        PUBLIC ./)