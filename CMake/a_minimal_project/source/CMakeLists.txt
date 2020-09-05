
#This should be the first line of the CMakeLists.txt

cmake_minimum_required(VERSION 3.2)
project(MyApp VERSION 4.7.2 LANGUAGES C)


add_executable(myExe 
            main.c
            echo_demo.c)

add_executable(testExe 
            main.c
            echo_demo.c)