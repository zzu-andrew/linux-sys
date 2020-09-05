
#This should be the first line of the CMakeLists.txt

cmake_minimum_required(VERSION 3.8)

# Poor practice, but very common
set(projectName MyProject)
project(${projectName} VERSION 4.7.2 LANGUAGES C)
#----------------------------------------------------------------------------------
if(WIN32)
    set(platformImpl source_win.cpp)
else()
    set(platformImpl source_generic.cpp)
endif()

message("platformImpl = ${platformImpl} WIN32 = ${WIN32}")


option(BUILD_MYLIB "Enable building the myLib target" OFF)
if(BUILD_MYLIB)
	add_library(myLib src1.c)
endif()

message("BUILD_MYLIB=${BUILD_MYLIB}")


set(list1 A B)
set(list2)
set(foo WillNotBeShown)
foreach(loopVar IN LISTS list1 list2 ITEMS foo bar)
message("Iteration for: ${loopVar}")
endforeach()

foreach(loopVar RANGE 1 10 6)
    message("echo loopVar = ${loopVar}")
endforeach()

foreach(signalVar RANGE 4)
    message("echo signalVar = ${signalVar}")
endforeach()

foreach(outerVar IN ITEMS a b c)
    unset(s)
    foreach(innerVar IN ITEMS 1 2 3)
        # Stop inner loop once string s gets long
        list(APPEND s "${outerVar}${innerVar}")
        string(LENGTH s length)
        if(length GREATER 5)
       		break()
        endif()
        # Do no more processing if outer var is "b"
        if(outerVar STREQUAL "b")
        	continue()
        endif()
        message("Processing ${outerVar}-${innerVar}")
    endforeach()
    message("Accumulated list: ${s}")
endforeach()



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



