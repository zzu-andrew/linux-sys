#This should be the first line of the CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

# Poor practice, but very common
set(projectName MyProject)
project(${projectName} VERSION 4.7.2 LANGUAGES C)
#---------------------------------------------------------------------------------
# test 4 markdown
message("================================test4========================")

add_library(echo_demo echo_demo.c)

add_library(myHeaderOnlyToolkit INTERFACE)
target_include_directories(myHeaderOnlyToolkit
    INTERFACE ./inc
)
target_compile_definitions(myHeaderOnlyToolkit
    INTERFACE COOL_FEATURE=1
)

add_executable(myApp main.c)
# 通过interface透传 头文件的路径
target_link_libraries(myApp PRIVATE myHeaderOnlyToolkit)
# 通过interface透传 头文件的路径
target_link_libraries(echo_demo PRIVATE myHeaderOnlyToolkit)
target_link_libraries(myApp PRIVATE echo_demo)


#================================================




