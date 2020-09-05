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



















