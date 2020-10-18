
#This should be the first line of the CMakeLists.txt

cmake_minimum_required(VERSION 3.8)

# Poor practice, but very common
set(projectName MyProject)
project(${projectName} VERSION 4.7.2 LANGUAGES C)
#----------------------------------------------------------------------------------

message("---------------------------------------------------------------")
message("top:   CMAKE_SOURCE_DIR      = ${CMAKE_SOURCE_DIR}")
message("top:   CMAKE_BINARY_DIR      = ${CMAKE_BINARY_DIR}")
message("top:   CMAKE_CURRENT_SOURCE_DIR      = ${CMAKE_CURRENT_SOURCE_DIR}")
message("top:   CMAKE_CURRENT_BINARY_DIR      = ${CMAKE_CURRENT_BINARY_DIR}")
message("---------------------------------------------------------------")

add_library(collectorsub src1.c)
add_library(echo_demosub echo_demo.c)

#add_executable(targetName [WIN32] [MACOSX_BUNDLE]
#    [EXCLUDE_FROM_ALL]
#    source1 [source2 ...]
#)
# EXCLUDE_FROM_ALL 不对该可执行程序进行编译
set(executeProcess myExesub)  # 使用变量
add_executable(${executeProcess} 
            main.c)

# PUBLIC 的链接方式可以直接在链接echo_demo的目标中使用 collector库中的函数
target_link_libraries(echo_demosub
        PUBLIC collectorsub)

target_link_libraries(${executeProcess}
    PRIVATE echo_demosub        
)           



