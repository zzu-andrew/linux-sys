
#This should be the first line of the CMakeLists.txt

cmake_minimum_required(VERSION 3.16)

# Poor practice, but very common
set(projectName MyProject)
project(${projectName} VERSION 4.7.2 LANGUAGES C)
#---------------------------------------------------------------------------------
# test 3 markdown
message("================================test3========================")
set(echo_demo_location "/work/libecho_demo.a")
add_library(echo_demo UNKNOWN IMPORTED)
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




