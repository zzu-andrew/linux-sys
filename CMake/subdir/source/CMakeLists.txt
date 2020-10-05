
#This should be the first line of the CMakeLists.txt

cmake_minimum_required(VERSION 3.8)

# Poor practice, but very common
set(projectName MyProject)
project(${projectName} VERSION 4.7.2 LANGUAGES C)
#----------------------------------------------------------------------------------


message("===========================================================")
message("top:   CMAKE_SOURCE_DIR      = ${CMAKE_SOURCE_DIR}")
message("top:   CMAKE_BINARY_DIR      = ${CMAKE_BINARY_DIR}")
message("top:   CMAKE_CURRENT_SOURCE_DIR      = ${CMAKE_CURRENT_SOURCE_DIR}")
message("top:   CMAKE_CURRENT_BINARY_DIR      = ${CMAKE_CURRENT_BINARY_DIR}")

#make的时候不编译子目录下的源码
#add_subdirectory(./mysub EXCLUDE_FROM_ALL)
# 编译子目录下的源码 并创建子编译目录aaadd
#add_subdirectory(./mysub aaadd)
#
add_subdirectory(./mysub)
message("===========================================================")

message("top:   CMAKE_CURRENT_SOURCE_DIR      = ${CMAKE_CURRENT_SOURCE_DIR}")
message("top:   CMAKE_CURRENT_BINARY_DIR      = ${CMAKE_CURRENT_BINARY_DIR}")
message("===========================================================")
#---------------------------------------------------------------------------------
add_library(collector src1.c)
add_library(echo_demo echo_demo.c)

#add_executable(targetName [WIN32] [MACOSX_BUNDLE]
#    [EXCLUDE_FROM_ALL]
#    source1 [source2 ...]
#)
# EXCLUDE_FROM_ALL 不对该可执行程序进行编译
set(executeProcess myExe)  # 使用变量
add_executable(${executeProcess} 
            main.c)

# PUBLIC 的链接方式可以直接在链接echo_demo的目标中使用 collector库中的函数
target_link_libraries(echo_demo
        PUBLIC collector)

target_link_libraries(${executeProcess}
    PRIVATE echo_demo        
)           



