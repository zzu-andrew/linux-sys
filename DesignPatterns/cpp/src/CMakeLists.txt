
# 针对cmake版本的要求
# cmake version 3.18.3
cmake_minimum_required(VERSION 3.5)

project(cppDesignPatterns)

add_definitions("-Wall -g")

# 开闭原则
add_executable(open_close_principle open_close_principle.cpp)
# 依赖颠倒原则
add_executable(reverse_dependencies reverse_dependencies.cpp)
# 懒汉式单例模式
add_executable(sluggard_singleton sluggard_singleton.cpp)
# 饿汉式单例模式
add_executable(hungry_singleton hungry_singleton.cpp)

#target_include_directories( PUBLIC ./../lib)

