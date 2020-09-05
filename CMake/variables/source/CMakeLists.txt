
#This should be the first line of the CMakeLists.txt

cmake_minimum_required(VERSION 3.8)

# Poor practice, but very common
set(projectName MyProject)
project(${projectName} VERSION 4.7.2 LANGUAGES C)

variable_watch(myVar)

set(myVar a "b c")  # myVar = "a;b c"
set(myVar "a b c")  # myVar = "a;b c"

# 临时变量一旦设置，GUI届满除非退出或者选中 remove entry之后重新生成否则不会重新显示新的值，UBUNTU 20 CMAKE 3.18
#set(optVar initialValue CACHE BOOL helpString)
option(optVar "sting" OFF)
set(sqlite ON CACHE BOOL "sqlite3")



# 设置临时变量
set(trafficLight Green CACHE STRING "Status of something")
# 为临时变量增加GUi界面修改可选项
set_property(CACHE trafficLight PROPERTY STRINGS Red Orange Green)

set(newVar "new string" CACHE STRING "new value" FORCE)  # myVar = "a;b c"

#设置变量  并打印  cmake中的所有变量其实都是字符串形式的变量
set(testVar HiThere)
message(STATUS "The value of myVar = ${testVar}")
#通常会高亮输出，实测没有效果
#message(WARNING "The value of myVar = ${testVar}")

#message(SEND_ERROR "The value of myVar = ${testVar}")

#message(FATAL_ERROR "The value of myVar = ${testVar}")

message(DEPRECATION "The value of myVar = ${testVar}")

set(longStr abcdefabcdef)
set(shortBit def)
string(FIND ${longStr} ${shortBit} fwdIndex)
# 反方向查找
string(FIND ${longStr} ${shortBit} revIndex REVERSE)
message("fwdIndex = ${fwdIndex}, revIndex = ${revIndex}")

message("replace test ============")

set(matchString abc)
set(replaceWith zzz)
string(REPLACE ${matchString} ${replaceWith} replaceOutVar abcdjdiuegnkajkjfajabcabcabcdskfjksdjkabc abc)
message("replace string = ${replaceOutVar}")

# 提取子串 string(SUBSTRING input index length outVar)
string(SUBSTRING ${replaceOutVar} 1 -1 subOutVar)
message("subOutVar = ${subOutVar}")

# Example
set(myList a b c) # Creates the list "a;b;c"
list(LENGTH myList len)
message("length = ${len}")
list(GET myList 2 1 letters)
message("letters = ${letters}")

#追加和插入
set(myList a b c)
list(APPEND myList d e f)
message("myList (first) = ${myList}")
list(INSERT myList 2 X Y Z)
message("myList (second) = ${myList}")

message("list test +++++++++++++++++++++")
# Example
set(testList a b c d e)
list(FIND testList d bIndex)
message("index = ${bIndex}")


# Math
set(x 3)
set(y 7)
math(EXPR z "(${x}+${y}) / 2")
message("result = ${z}")



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



