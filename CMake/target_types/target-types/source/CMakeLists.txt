
#This should be the first line of the CMakeLists.txt

cmake_minimum_required(VERSION 3.16)

# Poor practice, but very common
set(projectName MyProject)
project(${projectName} VERSION 4.7.2 LANGUAGES C)
#----------------------------------------------------------------------------------
message("================================test1========================")
# test 1
# add_executable测试，其中的targetName可以随便写
# add_executable(targetName IMPORTED [GLOBAL])
set(GIT_EXECUTABLE "/usr/bin/git")
add_executable(AAAAA IMPORTED)
set_property(TARGET AAAAA PROPERTY IMPORTED_LOCATION "${GIT_EXECUTABLE}")
get_target_property(git_location AAAAA IMPORTED_LOCATION)
get_target_property(git_imported AAAAA IMPORTED)
message(">>> git location: ${git_location}, ${git_imported}")
#---------------------------------------------------------------------------------
# test 2  markdown
message("================================test2========================")
set(echo_demo_location "/work/libecho_demo.a")
add_library(echo_demo STATIC IMPORTED)
set_target_properties(echo_demo PROPERTIES
    IMPORTED_LOCATION "${echo_demo_location}"
    #INTERFACE_LINK_LIBRARIES collector
)
get_target_property(collector_data echo_demo IMPORTED_LOCATION)
get_target_property(collector_IMPORT_data echo_demo IMPORTED)
message(">>> : ${collector_data}, ${collector_IMPORT_data}")

#-------------------------------------------------------

# EXCLUDE_FROM_ALL 不对该可执行程序进行编译
set(executeProcess myExe)  # 使用变量
add_executable(${executeProcess} 
             main.c echo_demo)

#================================================




