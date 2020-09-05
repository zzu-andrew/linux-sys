## building simple targets

### `Executables`

If an executable is defined with the EXCLUDE_FROM_ALL option, it will not be included in that default ALL target.

```cmake
add_executable(targetName [WIN32] [MACOSX_BUNDLE]
	[EXCLUDE_FROM_ALL]
	source1 [source2 ...]
)
```

`EXCLUDE_FROM_ALL`设置之后将不再生成该可执行程序

### `Defining Libraries`

```cmake
add_library(targetName [STATIC | SHARED | MODULE]
    [EXCLUDE_FROM_ALL]
    source1 [source2 ...]
)
```

`STATIC`生成静态库

`SHARED`生成动态库

`MODULE` `windows`上的`DLL`

要是在`add_library`中省略了动态库还是静态库的选项，可以在调用`cmake`的时候通过编译选项指定如

```cmake
cmake -DBUILD_SHARED_LIBS=YES /path/to/source
```

等价于在`CMakeLists.txt`中设置

```cmake
set(BUILD_SHARED_LIBS YES)
```



### `Linking Targets`

`CMake` captures this richer set of dependency relationships with its target_link_libraries() command, not just the simplistic idea of needing to link. The general form of the command is:

```cmake
target_link_libraries(targetName
    <PRIVATE|PUBLIC|INTERFACE> item1 [item2 ...]
    [<PRIVATE|PUBLIC|INTERFACE> item3 [item4 ...]]
    ...
)
```

`PRIVATE`

Private dependencies specify that library A uses library B in its own internal implementation. Anything else that links to library A doesn’t need to know about B because it is an internal implementation detail of A.
`PUBLIC`

Public dependencies specify that not only does library A use library B internally, it also uses B in its interface. This means that A cannot be used without B, so anything that uses A will also have a direct dependency on B. An example of this would be a function defined in library A which has at least one parameter of a type defined and implemented in library B, so code cannot call the function from A without providing a parameter whose type comes from B.
`INTERFACE`

Interface dependencies specify that in order to use library A, parts of library B must also be `17used.` This differs from a public dependency in that library A doesn’t require B internally, it only uses B in its interface. An example of where this is useful is when working with library targets defined using the INTERFACE form of add_library(), such as when using a target to represent a header-only library’s dependencies

`target_link_libraries`允许定义一个库是怎样依赖其他库，按照下面的顺序定义进行定义

```cmake
add_library(collector src1.cpp)
add_library(algo src2.cpp)
add_library(engine src3.cpp)
add_library(ui src4.cpp)
add_executable(myApp main.cpp)
target_link_libraries(collector 
    PUBLIC ui
    PRIVATE algo engine
)
target_link_libraries(myApp PRIVATE collector)
```

In this example, the `ui` library is linked to the collector library as PUBLIC, so even though `myApp` only directly links to collector, `myApp` will also be linked to `ui` because of that PUBLIC relationship。

the `targetName` used with target_link_libraries() must have been defined by an add_executable() or add_library() command in the same directory from which target_link_libraries() is being called.

### Linking Non-targets

`target_link_libraries()` command is more flexible than that. In addition to `CMake` targets, the following things can also be specified as items in a target_link_libraries() command`:`

**`Full path to a library file`**

`CMake` will add the library file to the linker command. If the library file changes, `CMake` will detect that change and re-link the target. prior 3.3 version (`e.g. replace /usr/lib/libfoo.so with -lfoo`)`CMake`会去查找库，带来的问题就是有大量历史缓存。

**`Plain library name`**

If just the name of the library is given with no path, the linker command will search for that library (`e.g. foo becomes -lfoo or foo.lib`, depending on the platform). This would be common for libraries provided by the system.

**`Link flag`**

As a special case, items starting with a hyphen other than -l or -framework will be treated as flags to be added to the linker command. `Cmake`手册中禁止这样使用，因为当是`PUBLIC`或者`INTERFACE`连接的时候这些命令可能会传递给其他的目标。



### `TIPS`

目标名字和工程名字不必必须一样，当时通常教程和示例中会通过变量的形式将两者设置成一样的。

```cmake
# Poor practice, but very common
set(projectName MyExample)
project(${projectName})
add_executable(${projectName} ...)
```







本章源码：

```cmake

#This should be the first line of the CMakeLists.txt

cmake_minimum_required(VERSION 3.2)

# Poor practice, but very common
set(projectName MyProject)
project(${projectName} VERSION 4.7.2 LANGUAGES C)


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

`echo_demo.c`

```c
#include <stdio.h>

int echo_demo(void)
{
    printf("echo demo\n");


    return 0;
}
```

```c
#include <stdio.h>

int echo_demo(void);

int main(int argc, char const *argv[])
{
    int ret = 0;
    ret = echo_demo();
    if(ret != 0)
    {
        printf("call echo demo failed\n");
    }

    return 0;
}
```

`src1.c`

```c
#include <stdio.h>


void src1(void)
{
    printf("src1, is Linked.\n");
    return;
}
```









































