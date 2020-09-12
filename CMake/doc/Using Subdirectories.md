## Using Subdirectories

[代码仓库地址](https://github.com/zzu-andrew/linux-sys/tree/dfew/CMake)

```bash
https://github.com/zzu-andrew/linux-sys/tree/dfew/CMake 
```

现实世界中很多的项目都是有多个目录组成的，一个良好的目录结构更有利于编译系统的构建

add_subdirectory() and include() have quite different characteristics, so it is important to understand the strengths and weaknesses of both.

### `add_subdirectory()`

The add_subdirectory() command allows a project to bring another directory into the build. That directory must have its own `CMakeLists.txt` file which will be processed at the point where add_subdirectory() is called and a corresponding directory will be created for it in the project’s build tree.

```cmake
add_subdirectory(sourceDir [ binaryDir ] [ EXCLUDE_FROM_ALL ])
```

The `sourceDir` does not have to be a subdirectory within the source tree, although it usually is. Any directory can be added, with `sourceDir` being specified as either an absolute or relative path, the latter being relative to the current source directory. Absolute paths are typically only needed when adding directories that are outside the main source tree.

Normally, the `binaryDir` does not need to be specified. When omitted, `CMake` creates a directory in the build tree with the same name as the `sourceDir`. If `sourceDir` contains any path components, these will be mirrored in the `binaryDir` created by `CMake`.

The optional `EXCLUDE_FROM_ALL` keyword is intended to control whether targets defined in the subdirectory being added should be included in the project’s ALL target by default.

#### Source And Binary Directory Variables

`CMake`可以通过`add_subdirectory()`设置任意复杂的源码和二进制目录，常用的宏如下：

**`CMAKE_SOURCE_DIR`**

最顶层源码目录所在位置

**`CMAKE_BINARY_DIR`**

最顶层构建目录。

**`CMAKE_CURRENT_SOURCE_DIR`**

当前`CMake`所处理的`CMakeLists.txt`所在目录

**`CMAKE_CURRENT_BINARY_DIR`**

当前`CMake`处理的`CMakeLists.txt`正在构建的目录

一个小例子：

主目录下的`CMakeLists.txt`文件

```cmake

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
```

`mysub`文件夹下的`CMakeLists.txt`文件

```cmake

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
```

执行输出结果：

```bash
andrew@andrew-G3-3590:/work/linux-sys/CMake/subdir/build$ cmake ./../source/
-- The C compiler identification is GNU 9.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
===========================================================
# 主目录下输出
top:   CMAKE_SOURCE_DIR      = /work/linux-sys/CMake/subdir/source
top:   CMAKE_BINARY_DIR      = /work/linux-sys/CMake/subdir/build
top:   CMAKE_CURRENT_SOURCE_DIR      = /work/linux-sys/CMake/subdir/source
top:   CMAKE_CURRENT_BINARY_DIR      = /work/linux-sys/CMake/subdir/build
---------------------------------------------------------------
# 子目录下输出
top:   CMAKE_SOURCE_DIR      = /work/linux-sys/CMake/subdir/source
top:   CMAKE_BINARY_DIR      = /work/linux-sys/CMake/subdir/build
top:   CMAKE_CURRENT_SOURCE_DIR      = /work/linux-sys/CMake/subdir/source/mysub
top:   CMAKE_CURRENT_BINARY_DIR      = /work/linux-sys/CMake/subdir/build/mysub
---------------------------------------------------------------
===========================================================
# 主目录下输出
top:   CMAKE_CURRENT_SOURCE_DIR      = /work/linux-sys/CMake/subdir/source
top:   CMAKE_CURRENT_BINARY_DIR      = /work/linux-sys/CMake/subdir/build
===========================================================
-- Configuring done
-- Generating done
-- Build files have been written to: /work/linux-sys/CMake/subdir/build
```

#### `Scope`作用域





































