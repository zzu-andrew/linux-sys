
#This should be the first line of the CMakeLists.txt

cmake_minimum_required(VERSION 3.16)

# Poor practice, but very common
set(projectName MyProject)
project(${projectName} VERSION 4.7.2 LANGUAGES C)
#----------------------------------------------------------------------------------
message("================================test6========================")

-----------------------------------------
add_library(echo_demo echo_demo.c)
# EXCLUDE_FROM_ALL 不对该可执行程序进行编译
set(executeProcess myExe)  # 使用变量
add_executable(${executeProcess} 
             main.c echo_demo)
target_link_libraries(${executeProcess}
   # PRIVATE echo_demo
    PRIVATE name_test
)

#================================================




