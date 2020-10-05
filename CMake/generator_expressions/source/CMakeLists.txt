
#This should be the first line of the CMakeLists.txt

cmake_minimum_required(VERSION 3.8)

# Poor practice, but very common
set(projectName MyProject)
project(${projectName} VERSION 4.7.2 LANGUAGES C)



#-----------------------------------------------------




















#--------------------------------------------------------------


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

#target_link_libraries(${executeProcess}
 #   PRIVATE echo_demo        
#)

# Before CMake 3.8
#target_link_libraries(${executeProcess} PRIVATE
#$<$<CONFIG:Debug>:checkedAlgo>
#$<$<NOT:$<CONFIG:Debug>>:fastAlgo>
#)
# CMake 3.8 or later allows a more concise form
# 主要作用就是在使用的时候，可以根据某些定义是否定义，或者一些条件是否符合，链接不同的库
target_link_libraries(${executeProcess} PRIVATE
  $<1:echo_demo>
)        



