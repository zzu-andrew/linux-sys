## 介绍

为了将源码转化为最终用户可以实际使用的东西，需要使用到==编译器、链接器、测试框架、打包系统==等，这些都增加了开发高质量、健壮性软件的复杂性，虽然一些`IDE`能够将这些过程简化一点，但是开发跨平台的软件并不是总能用到这些`IDE`的特性。

幸运的是，`CMake`就是一套可以使上述开发过程易于管理的==一套工具==，它涵盖了从建立代码工程到发布包的<font color = red>所有</font>过程everything)，`CMake`不仅涵盖了所有的开发流程，还支持广泛的平台、工具和不同的编程语言。

`CMake`使用的几个阶段如下：

![image-20200809084051990](/work/linux-sys/CMake/doc/picture/image-20200809084051990.png)

- 阶段一、`CMake`最出名的阶段-使用项目描述文件，生成特定平台的项目文件，这些生成的项目文件适合开发者结合(`make`、`Xcode`、`Visual Studio`)使用。
- 阶段二、使用阶段一生成的构建工具构建工程工程(如 make)
- 阶段三、后台测试管理
- 阶段四、打包管理

上述整个过程`CMake`都可以通过调用对应的工具完成，甚至构建工具(make)也可以被`CMake`调用。



---

## 建立一个工程

脱离构建系统，工程只是一堆文件的集合。

`CMakeLists.txt` 是一个平台无关的描述文件。`CMake`使用可读文件`CMakeLists.txt`为工程的构建制定了一些规则，定义了哪些文件应该编译，以及如何编译、跑哪些测试和创建什么包，`cmake`使用该描述文件生成特定平台相关工程文件。

`CMake`的基本原则就是项目同时要拥有一个源码路径和二进制文件目录，源码目录是放置`CMakeLists.txt` 文件、源码文件和一些需要构建的文件的地方，源码目录通常处于`git、subversion`或者类似工具的版本控制之下。

所有构建过程生成的文件都会放置到二进制目录，因此二进制目录通常也被称为构建目录。本书中倾向于使用构建目录，因为这样更直观。`CMake`调用构建工具(`eg: make`)、`CTest`和`CPack`的过程中，会在构建目录中生成一系列的文件- 可执行文件、库、测试输出和包。`CMake`还会在构建目录中生成一个名为`CMakeCache.txt`的特殊文件，用于存储各种后期运行时可重用的信息，开发人员不需要关心`CMakeCache.txt`文件，后面章节会讨论`CMakeCache.txt`文件。构建工具的项目文件也是在构建目录中创建的(`eg:makefile`)，这些`CMake`生成的文件不应该处于版本控制之下。

### 在源码中构建

虽然不是很鼓励这样做，但是在使用`CMake`时是可以在源码的目录进行构建的，并将这种构建方式称为内源构建`in-source build`，因为这种方式更加简单，所以开发者刚开始通常会使用这种构建方式。

在源码目录进行构建的主要问题：

- 源码和构建输出都混杂在一起，使得工程的管理变得非常的困难
- 要承担源文件可能被构建输出覆盖的风险
- 许多由构建创建的文件，使得版本控制系统的工作变得更加的困难
- 清除所有构建输出并使用干净源码树并不是件容易的事情

基于以上原因，不建议开发人员在源码中进行构建，即使是一个简单的项目

### 在源码外构建(`out-of-source builds`)

相比之下在源码外构建更加可取，因为：

- 源码与构建文件彻底分离
- 开发人员可以为一份源码创建多个构建目录，比如调试版本一个构建目录，发布版本一个构建目录

本书将始终使用源码外构建，并和遵循源目录和构建目录位于公共父目录下的模式，构建根目录将称为`build`

![image-20200809163501606](/work/linux-sys/CMake/doc/picture/image-20200809163501606.png)

一些开发人员会使用该方法的一些变体，将构建目录作为源目录的子目录，这样做虽然能顾有在源码外构建的大部分优势，但是让然会有部分内源构建的部分缺点，除非有很好的理由这样使用，否则建议将构建目录完全置于源码树之外。



### 生成项目文件

目录结构定下来后，开发人员可以运行`CMake`，它读入`CMakeList.txt`文件并在构建目录中创建项目文件。开发人员通过选择特定的项目文件生成器，来选择要创建的项目文件的类型。支持一系列不同的生成器，下表列出了更常用的生成器。

| `Category`      | `Generator Examples`    | `Multi-config` |
| --------------- | ----------------------- | -------------- |
| `Visual Studio` | `Visual Studio 15 2017` | `YES`          |
| `Visual Studio` | `Visual Studio 14 2015` | `YES`          |
| `Xcode`         | `Xcode`                 | `YES`          |
| `NinJa`         | `NinJa`                 | `NO`           |
| `Makefiles`     | `UNIX Makefiles`        | `NO`           |
| `Makefiles`     | `MSYS Makefiles`        | `NO`           |
| `Makefiles`     | `MinGW Makefiles`       | `NO`           |
| `Makefiles`     | `NMake Makefiles`       | `NO`           |

` Multi-config`-是否支持多配置构建项目，支持就可以在不重新运行`CMake`的前提下构建不同的项目(`eg: debug release`)

**最简单的调用`CMake`方式**

- 在构建目录中将生成器类型和源码目录的位置传递给`cmake`

```cmake
mkdir build
cd build
cmake -G "Unix Makefiles" ../source
```

如果省略`-G`选项，`cmake`会根据主机的平台选择默认的生成器类型。对于所有的生成器类型，`CMake`将执行一系列的测试并询问系统，以确定如何建立项目文件。这些工作包含验证编译器是否工作、确定支持的编译器特性集和其他的各种任务，在`CMake`完成之前将会给出类似如下的日志信息：

```bash
-- Configuring done
-- Generating done
-- Build files have been written to: /some/path/build
```

上面强调了项目文件的创建，实际上包含两个步骤-配置和生成。在配置阶段，`CMake`通过读取`CMakeLists.txt`文件完成对整个项目的内部表示的构建。在完成这些之后，生成阶段创建项目文件，配置和生成对与基本的`CMake`使用，并不是很重要，但是在后面的章节中，配置和生成分离变得很重要。会在` Chapter 10, Generator Expressions.`章节中进行更加详细的介绍。

当首次完成`CMake`的运行时，它将在构建目录中保存一个`cmakecase.txt`的文件，`CMake`使用这个文件来保存详细信息，这样当它再次运行时，他可以重用第一次计算的信息，并加速项目的生成。后面的章节将会介绍如何使用该文件在不同的运行之间保留开发者选项。`CMake`的`gui`程序使用将在第5章中进行介绍。

### 运行构建工具

此时，项目文件已经可用，开发人员可以按照他们习惯使用他们选择的构建工具。构建目录将包含必要的项目文件，这些文件可以加载到`IDE`中、通过命令行工具读取等，或者`CMake`能够代表开发者调用构建工具如：

```bash
cmake --build /some/path/build --config Debug --target MyApp
```

使用`Xcode`或`Visual Studio`这样`IDE`的开发者，更加习惯这种工作方式。`build`选项指向生成步骤中使用的构建目录对于支持多配置生成器，`config`选项指定要构建哪个配置，而单个配置生成器将忽略`--config`选项，详细信息将在第13章中进行介绍，`target`选项可以用来告诉构建工具要构建什么，或者如果省略将构建默认的目标。

虽然在日常开发中，开发人员通常自己调用构建工具，但是通过`cmake`进行调用在脚本驱动的自动化构建中更加的有用。使用这种方法，一个简单的脚本构建如下：

```bash
mkdir build
cd build
cmake -G "Unix Makefiles" ../source
cmake --build . --config Release --target MyApp
```

如果开发人员想更换不同的生成器，所需要做的就是更改`-G`参数，然后将`cmake`将自动调用正确的构建工具。

### 建议

即使首次使用`cmake`也建议将构建目录与源码进行完全分离，为相同的源码目录设置两个设置跟多不同的构建。

跨平台工作的开发者，定期使用不同生成器进行构建

## A minimal project

```cmake
# 说明最低cmake版本要求
cmake_minimum_required(VERSION 3.2)
# 工程名
project(MyApp)
# 可执行程序名
add_executable(myExe main.cpp)
```

支持添加多个文件

```cmake
add_executable(myExe
    main.cpp
    src1.cpp
    src2.cpp
)
```

命令不区分大小写

```cmake
add_executable(myExe main.cpp)
ADD_EXECUTABLE(myExe main.cpp)
Add_Executable(myExe main.cpp)
```

可只填写主版本和次版本

```cmake
cmake_minimum_required(VERSION major.minor[.patch[.tweak]])
```

每个`CMake`工程都应该包含一个`project()`命令，该命令应该在`cmake_minimum_required()`命令之后调用。虽然能只给一个工程名，但是最好给出工程的版本信息，方便其他模块能够调用

```cmake
project(projectName
    [VERSION major[.minor[.patch[.tweak]]]]
    [LANGUAGES languageName ...]
)
```

The optional LANGUAGES argument defines the programming languages that should be enabled for the project. Supported values include C, `CXX`, Fortran, `ASM`, Java and others. If specifying multiple languages, separate each with a space. In some special situations, projects may want to indicate that no languages are used, which can be done using LANGUAGES NONE.

If no LANGUAGES option is provided, `CMake` will default to C and `CXX`.

`CMake` versions prior to 3.0 do not support the LANGUAGES keyword, but languages can still be specified after the project name using the older form of the command like so:

```cmake
project(myProj C CXX)
```

本章源码：

```cmake
#This should be the first line of the CMakeLists.txt

cmake_minimum_required(VERSION 3.2)
project(MyApp VERSION 4.7.2 LANGUAGES C)

add_executable(myExe 
            main.c
            echo_demo.c)

add_executable(testExe 
            main.c
            echo_demo.c)
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



---

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



---

## `Variables`

为有用的参数命名

### `Variable Basics`

像其他编程语言一样，变量是`CMake`工作的基石。使用`set()`命令进行变量的命名，变量对大小写敏感。

```cmake
set(varName value... [PARENT_SCOPE])
```

In `CMake`, a variable has a particular scope, much like how variables in other languages have scope limited to a particular function, file, etc. A variable cannot be read or modified outside of its scope.

`CMake` treats all variables as strings.

```cmake
set(myVar a b c)  # myVar = "a;b;c"
set(myVar a;b;c)  # myVar = "a;b;c"
set(myVar "a b c")  # myVar = "a b c"
set(myVar a b;c)  # myVar = "a;b;c"
set(myVar a "b c")  # myVar = "a;b c"
```

In addition, `CMake` doesn’t require variables to be defined before using them. Use of an undefined variable simply results in an empty string being substituted with no error or warning, much like Unix shell scripts

```cmake
set(foo ab)  # foo = "ab"
set(bar ${foo}cd) # bar = "abcd"
set(baz ${foo} cd) # baz = "ab;cd"
set(myVar ba) # myVar = "ba"
set(big "${${myVar}r}ef") #big = "${bar}ef"="abcdef"
set(${foo} xyz) # ab = "xyz"
set(bar ${notSetVar}) # bar = ""
```

Strings are not restricted to being a single line, they can contain embedded newline characters. They can also contain quotes, which require escaping with backslashes.

```cmake
set(myVar "goes here")
set(multiLine "First line ${myVar}
Second line with a \"quoted\" word")
```



```cmake
# Simple multi-line content with bracket syntax,
# no = needed between the square bracket markers
# 没有等号的语法用于简单的多行文本
set(multiLine [[
First line
Second line
]])
# Bracket syntax prevents unwanted substitution
# 带等号括号语法能阻止不必要的替换
set(shellScript [=[
#!/bin/bash
[[ -n "${USER}" ]] && echo "Have USER"
]=])
# Equivalent code without bracket syntax
# 特殊字符需要转义
set(shellScript
"#!/bin/bash
[[ -n \"\${USER}\" ]] && echo \"Have USER\"
")
```

As the above example shows, bracket syntax is particularly well suited to defining content like Unix shell scripts. Such content uses the ${...} syntax for its own purpose and frequently contains quotes, but using bracket syntax means these things do not have to be escaped, unlike the traditional quoting style of defining `CMake` content.

A variable can be unset either by calling unset() or by calling set() with no value for the named variable.

```cmake
set(myVar)
unset(myVar)
```

### Environment Variables

`CMake`允许设置环境变量，环境变量通过特殊的形式`$ENV{varName}`的小姑娘是设置，`${varName}`可以单独的使用，环境变量设置和普通变量一样，除了要以`ENV{varName}`开头外。

```cmake
set(ENV{PATH} "$ENV{PATH}:/opt/myDir")
```

这样设置的环境变量仅仅是影响当前的`CMake`，当前`CMake`运行结束之后环境变量也就跟着消失了，环境变量也只是影响`Cmake`阶段，在`build`阶段将不会受到影响。

### Cache Variables

In addition to normal variables discussed above, `CMake` also supports cache variables. Unlike normal variables which have a lifetime limited to the processing of the `CMakeLists.txt` file, cache variables are stored in the special file called `CMakeCache.txt` in the build directory and they persist between `CMake runs.Once` set, cache variables remain set until something explicitly removes them from the cache. but the set() command is different when used to set a cache variable:

```cmake
set(varName value... CACHE type "docstring" [FORCE])
```

When the CACHE keyword is present, the set() command will apply to a cache variable named  `varName` instead of a normal variable. The type must be one of the following:

==最主要的用途是用于GUI用户可以查看具体信息，定位问题==

**`BOOL`**

ON/OFF, TRUE/FALSE, 1/0, etc.

**`FILEPATH`**

**`PATH`**

**`STRING`**

**`INTERNAL`**

The variable is not intended to be made available to the user. Internal cache variables are  sometimes used to persistently record internal information by the project, such as caching the result of an intensive query or computation. GUI tools do not show INTERNAL variables.

设置`boolean`很频繁，`CMake`中有更加简洁的专门的设置命令用于设置`boolean`类型的变量。

```cmake
option(optVar helpString [initialValue])
```

If `initialValue` is omitted, the default value OFF will be used

上述的命令等价于：

```cmake
set(optVar initialValue CACHE BOOL helpString)
```

An important difference between normal and cache variables is that the set() command will only overwrite a cache variable if the `FORCE` keyword is present, unlike normal variables where the set() command will always overwrite a `pre-existing` value.

option 命令没有`FORCE`选项，设置`cache`变量，会像set()命令设置普通变量一样，默认覆盖原有的设置。

临时变量和普通变量使用一样的命名会带来很多意料之外的结果。

```cmake
set(myVar foo)                         # Local myVar
set(result ${myVar})                   # result = foo
set(myVar bar CACHE STRING “”)         # Cache myVarm 第二次运行因为已经存在所有这里不会再设置，除非加上 FROCE

set(result ${myVar})                   # First run:
result = bar                           # Subsequent runs: result = foo

set(myVar fred)
set(result ${myVar})                   # result = fred
```

### Manipulating Cache Variables

Using set() and option(), a project can build up a useful set of customization points for its developers. Different parts of the build can be turned on or off, paths to external packages can be set, flags for compilers and linkers can be modified and so on.

==Manipulating 操纵==

#### Setting Cache Values On The Command Line

`CMake` allows cache variables to be manipulated directly via command line options passed to `cmake`.

```bash
cmake -D myVar:type=someValue ...
```

命令行设置的变量为`cache`变量，能被带有`CACHE` 和 `FORCE`选项的set()指令覆盖掉，多次使用`-D`能设置多个临时变量。

通过命令行设置临时变量，`socstring`是空的，`type`类型也是可以忽略的。

```bash
cmake -D foo:BOOL=ON ...
cmake -D "bar:STRING=This contains spaces" ...
cmake -D hideMe=mysteryValue ...
cmake -D helpers:FILEPATH=subdir/helpers.txt ...
cmake -D helpDir:PATH=/opt/helpThings ...
```

使用`-U`选项可以删除`cache`，支持同时删除多个`*`

```cmake
cmake -U 'help*' -U foo ...
```

#### `CMake` GUI Tools

In the first stage, the `CMakeLists.txt` file is read and a representation of the project is built up in memory.
This is called the configure stage. If the configure stage is successful, the generate stage can then be executed to create the build tool’s project files in the build directory. When running `cmake` from the command line, both stages are executed automatically, but in the GUI application, they are triggered separately with the Configure and Generate buttons.

![image-20200816124848930](/work/linux-sys/CMake/doc/picture/image-20200816124848930.png)

设置变量，并增加变量的可选项，经过`set_property(CACHE trafficLight PROPERTY STRINGS Red Orange Green)`设置，变量`trafficLight` GUI上进行编辑变量时就会出现设置的可选项。

```cmake
set(trafficLight Green CACHE STRING "Status of something")
set_property(CACHE trafficLight PROPERTY STRINGS Red Orange Green)
```

In the above, the `trafficLight` cache variable will initially have the value Green. When the user attempts to modify `trafficLight` in `cmake-gui,` they will be given a `combobox` containing the three values Red, Orange and Green instead of a simple line edit widget which would otherwise have allowed them to enter any arbitrary text.



Cache variables can also have a property marking them as advanced or not. This too only affects the way the variable is displayed in `cmake-gui`, it does not in any way affect how `CMake` uses the variable during processing. By default, `cmake-gui` only shows non-advanced variables, which typically presents just the main variables a developer would be interested in viewing or modifying.

```cmake
mark_as_advanced([CLEAR|FORCE] var1 [var2...])
```

The CLEAR keyword ensures the variables are not marked as advanced, while the FORCE keyword ensures the variables are marked advanced. Without either keyword, the variables will only be marked as advanced if they don’t already have an advanced/non-advanced state set.

一旦标记为`advanced`变量，就只能通过界面上勾选`Advanced`选项进行查看。

![image-20200816130523511](/work/linux-sys/CMake/doc/picture/image-20200816130523511.png)



### Debugging Variables And Diagnostics

使用`message()`命令，可以打印变量的值，可以解决当编译出现意想不到的情况时使用。

```cmake
message([mode] msg1 [msg2]...)
```

```cmake
set(myVar HiThere)
message("The value of myVar = ${myVar}")：
```

This will give the following output :

```bash
andrew@ubuntu:/work/linux-sys/CMake/variables/build$ cmake ./../source/
The value of myVar = HiThere
```

`message`中的`mode`选项，可以影响打印如何输出，甚至可以使编译时抛出错误。

**`STATUS`**

附加信息，打印信息会使用两个连字符的方式显示

**`WARNING`**

通常会按照高亮输出，实测没有效果

**`AUTHOR_WARNING`**

Like WARNING, but only shown if developer warnings are enabled (requires the `-Wdev` option on the `cmake` command line). Projects do not often use this particular type of message.

**`SEND_ERROR`**

触发个错误，并停止`cmake`的运行

```bash
CMake Error at CMakeLists.txt:30 (message):
  The value of myVar = HiThere


-- Configuring incomplete, errors occurred!
```

**`FATAL_ERROR`**

硬件异常，立刻停止`cmake`，并将产生的日志放到`CMakeOutput.log`中

```bash
CMake Error at CMakeLists.txt:32 (message):
  The value of myVar = HiThere


-- Configuring incomplete, errors occurred!
See also "/work/linux-sys/CMake/variables/build/CMakeFiles/CMakeOutput.log".
```

**`DEPRECATION`**

Special category used to log a deprecation message. If the `CMAKE_ERROR_DEPRECATED` variable is defined to a boolean true value, the message will be treated as an error. If `CMAKE_WARN_DEPRECATED` is defined to a boolean true, the message will be treated as a warning. If neither variable is defined, the message will not be shown.

If no mode keyword is provided, then the message is considered to be important information and is logged without any modification.

`cmake`支持变量监控，被监控的变量任何时候被修改都会通过消息的方式打印出来。

```cmake
variable_watch(myVar [command])
```



#### String Handling

随着项目的复杂度增加，命令处理也会越来越复杂，`cmake`提供了一个强大的字符串处理工具`string()`命令，支持查找、替换、匹配、大小写转换、替换空格等等，

The first argument to string() defines the operation to be performed and subsequent arguments depend on the operation being requested. These arguments will generally require at least one input string and since `CMake` commands cannot return a value, an output variable for the result of the operation. In the material below, this output variable will generally be named `outVar`.

```cmake
string(FIND inputString subString outVar [REVERSE])
```

FIND searches for `subString` in `inputString` and stores the index of the found `subString` in `outVar` (the first character is index 0). The first occurrence is found unless REVERSE is specified, in which case the last occurrence will be found instead. If `subString` does not appear in `inputString`, then `outVar` will be given the value -1.

```cmake
set(longStr abcdefabcdef)
set(shortBit def)
string(FIND ${longStr} ${shortBit} fwdIndex)
# 反方向查找
string(FIND ${longStr} ${shortBit} revIndex REVERSE)
message("fwdIndex = ${fwdIndex}, revIndex = ${revIndex}")
```

查找之后会给出首次出现的字符串下标，下表从0开始

```bash
fwdIndex = 3, revIndex = 9
```

替换字符串

```cmake
string(REPLACE matchString replaceWith outVar input [input...])
```

The REPLACE operation will replace every occurrence of `matchString` in the input strings with `replaceWith` and store the result in `outVar`.

```cmake
set(matchString abc)
set(replaceWith zzz)
string(REPLACE ${matchString} ${replaceWith} replaceOutVar abcdjdiuegnkajkjfajabcabcabcdskfjksdjkabc abc)
message("replace string = ${replaceOutVar}")
```

输出结果

```bash
replace test ============
replace string = zzzdjdiuegnkajkjfajzzzzzzzzzdskfjksdjkzzzzzz
```

字符串后面出现6个z可以看出，当给出多个input字符串的时候，会将多个字符串进行连接之后按照一个整体输出，因此实际使用的时候，尽量一次只替换一个字符串。

字符串处理支持正则，只需要在使用具体方法的时候在方法前面加上`REGEX`操作

```cmake
string(REGEX MATCH regex outVar input [input...])
string(REGEX MATCHALL regex outVar input [input...])
string(REGEX REPLACE regex replaceWith outVar input [input...])
```

The MATCH operation finds just the first match and stores it in `outVar`. `MATCHALL` finds all matches and stores them in `outVar` as a list.

```cmake
set(longStr abcdefabcdef)
string(REGEX MATCHALL "[ace]" matchVar ${longStr})
string(REGEX REPLACE "([de])" "X\\1Y" replVar ${longStr})
message("matchVar = ${matchVar}")
message("replVar = ${replVar}")
```

提取子串

```cmake
string(SUBSTRING input index length outVar)
```

input输入的字符串， index索引字符串下标，length子串长度。

==如果length的值为-1，代表的是从当前索引一直到字符串结尾==

```cmake
string(LENGTH input outVar)   # 获取字符串长度
string(TOLOWER input outVar)  # 将字符串转换为小写
string(TOUPPER input outVar)  # 将字符串转换为大写
string(STRIP input outVar)    # 将字符串空格剔除
```

### Lists

`Lists`在`cmake`中使用的非常普遍。

获取列表

```cmake
list(LENGTH listVar outVar)
list(GET listVar index [index...] outVar)
```

The output of the above example would be :

```cmake
length = 3
letters = c;b
```

向列表中追加和插入元素 

```cmake
list(APPEND listVar item [item...])
list(INSERT listVar index item [item...])
```

```cmake
set(myList a b c)
list(APPEND myList d e f)
message("myList (first) = ${myList}")
list(INSERT myList 2 X Y Z)
message("myList (second) = ${myList}")
```

```bash
myList (first) = a;b;c;d;e;f
myList (second) = a;b;X;Y;Z;c;d;e;f
```

查询对应列表的索引，可以使用以下方法

```cmake
list(FIND myList value outVar)
```

```cmake
message("list test +++++++++++++++++++++")
# Example
set(testList a b c d e)
list(FIND testList d bIndex)
message("index = ${bIndex}")
```

```cmake
list test +++++++++++++++++++++
index = 3
```

需要注意的是在`FIND`函数中，变量不需要在使用`${}`解引用

三种可以直接`移除`列表元素的操作，这三种操作都是直接操作列表进行的

```cmake
list(REMOVE_ITEM myList value [value...])
list(REMOVE_AT myList index [index...])
list(REMOVE_DUPLICATES myList)
```

`REMOVE_ITEM`移除一个或多个指定的元素，指定的元素不存在也不会报错

`REMOVE_AT`移除指定索引的元素，元素不存在会报错

`REMOVE_DUPLICATES`确保列表中只包含独一无二的元素

**重新排序**

List items can also be reordered with REVERSE or SORT operations (sorting is alphabetical):

```cmake
list(REVERSE myList)
list(SORT myList)
```

### Math

```cmake
math(EXPR outVar mathExpr)
```

第一个参数为固定`EXPR`，`mathExpr`定义计算过程，结果最终存储在`outVar`中。支持`+ - * / % | & ^ ~ << >> * / %.`等运算符，具体使用和C语言中的完全一样。`mathExpr`支持使用变量`${myVar}`

```cmake
set(x 3)
set(y 7)
math(EXPR z "(${x}+${y}) / 2")
message("result = ${z}")
```

Expected output:

```bash
result = 5
```

---

## Flow Controls

The ubiquitous if() command provides the expected if-then-else behavior and looping is provided through the foreach() and while() commands.



### The if() Command



```cmake
if(expression1)
# commands ...
elseif(expression2)
# commands ...
else()
# commands ...
endif()
```

### Basic Expressions

最简单的`if`语句是如下：

```cmake
if(value)
```

- 当`value`是数值1、ON、YES、TRUE、Y或者一个非空的数值都被认为是真，`test`对大小写不敏感。
- 当`value`是数值0、NO、OFF、FALSE、N、IGNORE、`NOTFPOUND`、空字符串或者以`-NOTFOUND`结尾的字符串的时候，被认为是假，判别假的时候`value`同样大小写不敏感
- 如果不是上述两种情况，将会被认为是一个变量名，或者后面会说明的过程

忽略`endif()`的示例：

```cmake
# Examples of unquoted constants
if(YES)
if(0)
if(TRUE)
# These are also treated as unquoted constants because the
# variable evaluation occurs before if() sees the values
set(A YES)
set(B 0)
if(${A}) # Evaluates to true
if(${B}) # Evaluates to false
# Does not match any of the true or false constants, so proceed
# to testing as a variable name in the fall through case below
if(someLetters)
# Quoted value, so bypass the true/false constant matching
# and fall through to testing as a variable name or string
if("someLetters")
```

```cmake
# Common pattern, often used with variables defined
# by commands such as option(enableSomething "...")
if(enableSomething)
# ...
endif()
```

### Logic Operators

`CMake` supports the usual AND, OR and NOT logical operators, as well as parentheses to control order of precedence.

```cmake
# Logical operators
if(NOT expression)
if(expression1 AND expression2)
if(expression1 OR expression2)
# Example with parentheses
if(NOT (expression1 AND (expression2 OR expression3)))
```

按照通常的约定，首先计算括号内的表达式，从最里面的括号开始。

### Comparison Tests

`CMake`将比较测试分为三种不同的类型：数字、字符串和版本号，但是语法形式都遵循相同的模式。

```cmake
if(value1 OPERATOR value2)
```

`value1`和`value2`可以是变量名或值。如果一个值与一个变量名一样，将会被视为一个变量，否则将会被视为字符串或者值。

`OPERATOR`总结：

| `Numeric`       | `String`           | `Version numbers`       |
| --------------- | ------------------ | ----------------------- |
| `LESS`          | `STRLESS`          | `VERSION_LESS`          |
| `GREATER`       | `STRGREATER`       | `VERSION_GREATER`       |
| `EQUAL`         | `STREQUAL`         | `VERSION_EQUAL`         |
| `LESS_EQUAL`    | `STRLESS_EQUAL`    | `VERSION_LESS_EQUAL`    |
| `GREATER_EQUAL` | `STRGREATER_EQUAL` | `VERSION_GREATER_EQUAL` |

当比对的是含有字符和数字的混合情况，比对结果是未定义的，根据具体的`CMake`版本

```cmake
# Valid numeric expressions, all evaluating as true
if(2 GREATER 1)
if("23" EQUAL 23)
set(val 42)
if(${val} EQUAL 42)
if("${val}" EQUAL 42)
# Invalid expression that evaluates as true with at
# least some CMake versions. Do not rely on this behavior.
if("23a" EQUAL 23)
```

版本号对比，次版本号没有给出就默认为0

```cmake
if(1.2  VERSION_EQUAL 1.2.0)
if(1.2  VERSION_LESS 1.2.3)
if(1.2.3  VERSION_GREATER 1.2)
if(2.0.1  VERSION_GREATER 1.9.7)
if(1.8.2  VERSION_LESS 2)*
```

<u>字符串对比支持正则比对</u>，但是支持简单的正则比对

```cmake
if(value MATCHES regex)
```

```cmake
if("Hi from ${who}" MATCHES "Hi from (Fred|Barney).*")
	message("${CMAKE_MATCH_1} says hello")
endif()
```



### File System Tests

`CMake`中有一系列文件测试函数，`IS_NEWER_THAN`当两个文件时间戳一样或者一个文件丢失的时候都会返回`true`

```cmake
if(EXISTS pathToFileOrDir)
if(IS_DIRECTORY pathToDir)
if(IS_SYMLINK fileName)
if(IS_ABSOLUTE path)
if(file1 IS_NEWER_THAN file2)
```

### Existence Tests

大型和复杂工程中经常使用，用于决定哪些需要使用哪些不需要

```cmake
if(DEFINED name)
if(COMMAND name)
if(POLICY name)
if(TARGET name)
if(TEST name) # Available from CMake 3.4 onward
```

Each of the above will return true if an entity of the specified name exists at the point where the if command is issued.

**`DEFINED`**

如果对应的`name`定义了就返回`true`，用于测试变量或者环境变量是否被定义了

```cmake
if(DEFINED SOMEVAR)       # Checks for a CMake variable
if(DEFINED ENV{SOMEVAR})  # Checks for an environment variable
```

**`COMMAND`**

测试对应的`name`是否是`CMake`的命令，函数或者宏。

**`POLICY`**

测试特定的策略是否是已知，通常的形式是	`CMPxxxx`， `xxxx`部分通常是数字

**`TARGET`**

当一个目标被`add_executable(), add_library() or add_custom_target()`其中之一定义的时候，会返回`true`

**`TEST`**

被`add_test()`定义之后会返回`true`

`CMake`3.5以上支持以下语句

```cmake
if(value IN_LIST listVar)
```

### Common Examples

```cmake
if(WIN32)
    set(platformImpl source_win.cpp)
else()
    set(platformImpl source_generic.cpp)
endif()

message("platformImpl = ${platformImpl} WIN32 = ${WIN32}")
```

expect output:

```bash
platformImpl = source_generic.cpp WIN32 = 
```

```cmake
if(MSVC)
	set(platformImpl source_msvc.cpp)
else()
	set(platformImpl source_generic.cpp)
endif()
```

```cmake
if(APPLE)
# Some Xcode-specific settings here...
else()
# Things for other platforms here...
endif()
```



```cmake
if(CMAKE_GENERATOR STREQUAL "Xcode")
# Some Xcode-specific settings here...
else()
# Things for other CMake generators here...
endif()
```

设置变量作为一个库是否编译的开关

```cmake
option(BUILD_MYLIB "Enable building the myLib target" ON)
	if(BUILD_MYLIB)
	add_library(myLib src1.cpp src2.cpp)
endif()
```



### Looping

使用循环，持续进行检测，直到特定的环境发生

#### `foreach()`

```cmake
foreach(loopVar arg1 arg2 ...)
# ...
endforeach()
```

In the above form, for each `argN` value, `loopVar` is set to that argument and the loop body is executed.

Rather than listing out each item explicitly, the arguments can also be specified by one or more list variables using the more general form of the command:

```cmake
foreach(loopVar IN [LISTS listVar1 ...] [ITEMS item1 ...])
# ...
endforeach()
```

示例如下：

```cmake
set(list1 A B)
set(list2)
set(foo WillNotBeShown)
foreach(loopVar IN LISTS list1 list2 ITEMS foo bar)
	message("Iteration for: ${loopVar}")
endforeach()
```

output:

```cmake
Iteration for: A 
Iteration for: B
Iteration for: foo
Iteration for: bar
```

当在数值型中使用`foreach`时，可以使用类`C`风格

```cmake
foreach(loopVar RANGE start stop [step])
```

默认的`step`为1，也就是从`start`开始每次`+1`直到值大于`stop`停止循环。

```cmake
foreach(loopVar RANGE 1 10 6)
    message("echo loopVar = ${loopVar}")
endforeach()
```

output:

```bash
echo loopVar = 1
echo loopVar = 7
```

同时也支持单个`value`形式的，如下：

```cmake
foreach(loopVar RANGE value)
```

等价于`foreach(loopVar RANGE 0 value)`

#### `while()`

```cmake
while(condition)
# ...
endwhile()
```

执行到`condition`非`true`为止

#### Interrupting Loops



Both `while()` and `foreach()` loops support the ability to exit the loop early with break() or to skip to the start of the next iteration with continue().

```cmake
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
```

output:

```bash
Processing a-1
Processing a-2
Processing a-3
Accumulated list: a1;a2;a3
Accumulated list: b1;b2;b3
Processing c-1
Processing c-2
Processing c-3
Accumulated list: c1;c2;c3
```



































































































