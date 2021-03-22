cmake_minimum_required(VERSION 3.2)

project(c-algorithms)


add_executable(array_list
        array_list/main.cpp
        array_list/array_list.cpp)
#target_link_libraries(array_list pthread)
target_include_directories(array_list
        PUBLIC ./)

add_executable(stl-string
        stl/stl_strings.cpp)
target_include_directories(stl-string
        PUBLIC ./)

add_executable(stl-vector
        stl/stl_vector.cpp)
target_include_directories(stl-vector
        PUBLIC ./)

add_executable(stl-deque
        stl/stl_deque.cpp)

add_executable(stl-stack
        stl/stl_stack.cpp)
add_executable(stl-queue
        stl/stl_queue.cpp)