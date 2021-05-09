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
add_executable(stl-list
        stl/stl_list.cpp)
add_executable(stl-priority_queue
        stl/stl_priority_queue.cpp)
add_executable(stl-set
        stl/stl_set.cpp)
add_executable(stl-set_multiset
        stl/stl_set_multiset.cpp)
add_executable(stl-map
        stl/stl_map.cpp)
add_executable(lock_guard
        concurrency_in_action/lock_guard.cpp)
add_executable(concurrency_test
        concurrency_in_action/test.cpp)
target_link_libraries(concurrency_test
        PUBLIC pthread)
add_executable(thread_safe_stack
        concurrency_in_action/thread_safe_stack.cpp)
add_executable(condition_variable
        concurrency_in_action/condition_variable.cpp)
target_link_libraries(condition_variable
        PUBLIC pthread)
add_executable(stl-algorithm
        stl/stl_algorithm.cpp)
add_executable(stl-plus
        stl/stl_plus.cpp)
add_executable(compare_exchange_weak
        concurrency_in_action/compare_exchange_weak.cpp)
target_link_libraries(compare_exchange_weak
        PUBLIC pthread)
add_executable(template_test
        template_programing/template_test.cpp)
add_executable(convert_cplusplus
        template_programing/convert_cplusplus.cpp)
add_executable(try_catch
        template_programing/try_catch.cpp)
add_executable(iostream_demo
        template_programing/iostream_demo.cpp)
add_executable(thread_pool
        concurrency_in_action/thread_pool.cpp)
