## Target Types

**本章概括**

`CMake`支持的类型有很多种，可以是可执行文件或者库文件，也可以在不构建的情况下作为其它实体的引用。

使用这种引用作用：可以在不将对象构建成自己的二进制文件的情况下，为这些被引用的文件属性和依赖项。你也可以将这些被引用的文件称为一种新型<font size=4 color=red>`库`</font>，这种库不是传统意义上的静态库或者动态库，而是一种对象文件的集合。

很多事物都可以抽象为一个对象来隐藏复杂的平台的差异、文件在系统中的位置、文件名等，本章会介绍所有对象类型，并介绍他们的用途。

除了上述提到的静态库、动态库以及`引用库`，还有另外一种对象，这种对象实用的程序或者用户自定义对象。有了这些对象，用户就可以执行任意的命令和自定义生成规则，允许项目实现几乎任何类型需要的行为(深入讲解在第17章中)。



### 可执行程序

`add_executable()`命令，不仅有第四章中给出的构建简单对象的形式，还有另外两种形式，如下：

**第四章-构建简单对象**

```cmake
add_executable(targetName [WIN32] [MACOSX_BUNDLE]
    [EXCLUDE_FROM_ALL]
    source1 [source2 ...]
)
```

**本章新增**

```cmake
add_executable(targetName IMPORTED [GLOBAL])
add_executable(aliasName ALIAS targetName)
```

**字段说明**

`IMPORTED`选项，可以通过已有的可执行程序创建一个`CMake`对象而不是在项目中构建。虽然这种对象只是可执行程序在项目中的表现方式，但是项目的其他部分可像对待项目中自己构建的对象一样对待这个对象。这样使用的好处就是，当该对象可以用在`CMake`的上下文中时，`CMake`会自动将对象名替换为其在磁盘上的位置。例如可以执行测试命令或者用户自定义命令，这些将在后面的章节讲到。和普通对象不同的是该对象不能进行安装。

当使用`IMPORTED`选项定义一个可执行导入对象时，在正式使用之前需要对对象的一些属性进行设置。大多数与导入对象相关的属性都已`IMPORTED`开头，对于可执行目标其中两个需要特别注意的就是`IMPORTED_LOCATION`和`IMPORTED_LOCATION_<CONFIG>`。当需要可执行导入对象的位置时，`CMake`会首先检查给对象的特定配置属性(详情看属性章节)，只有特定配置没有设置的时候才会查找更加普遍的`IMPORTED_LOCATION`属性。通常来说位置不需要特定的配置，所以只设置`IMPORTED_LOCATION`属性是非常常见的。

`test1`将`git`导入到当前工程中

```cmake
set(GIT_EXECUTABLE "/usr/bin/git")
add_executable(AAAAA IMPORTED)
# 设置 IMPORTED_LOCATION 属性
set_property(TARGET AAAAA PROPERTY IMPORTED_LOCATION "${GIT_EXECUTABLE}")
#获取属性并打印出来
get_target_property(git_location AAAAA IMPORTED_LOCATION)
get_target_property(git_imported AAAAA IMPORTED)
message(">>> git location: ${git_location}, ${git_imported}")
```

输出结果：

```bash
>>> git location: /usr/bin/git, TRUE
```

==说明==：`IMPORTED`定义的可执行对象称为可执行导入对象

`GLOBAL`关键字可选，当没有指定`GLOBAL`时，导入对象只是在文件创建目录以及子目录可见，当指定`GLOBAL`关键字的时候，导入对象在整个目录可见。与你想象中不一样，实际使用中通常将导入目标定义成全局的，其中的缘由以及一些减少可目标可见度的实例将在第三小节中进行说明。

`ALIAS`和名字一样，就是为目标在`CMake`工程中建立个别名，不过这个别名是只读的。创建别名并不是真的为别名构建一个和别名一样的对象，而只是创建一个指向真实对象的别名，别名同样不能被安装和导出，并且别名的别名是不被允许的。

==说明==：`CMake`3.11之前，导入对象不能有别名，但是在3.11之后将这一限制放宽了一些，但是只有全局的导入对象能有别名

### 库文件

`add_library() `同样也有多种形式。第四章中介绍的构建简单对象中使用`add_library() `是我们常见的形式，该命令同样支持定义目标库，目标库仅仅是目标文件的集合，并不是真正意义上的构建出一个静态或者动态库，扩展之后的命令如下：

```cmake
add_library(targetName [STATIC | SHARED | MODULE | OBJECT]
    [EXCLUDE_FROM_ALL]
    source1 [source2 ...]
)
```

第四章中没有进行扩展的命令：

```cmake
add_library(targetName [STATIC | SHARED | MODULE]
    [EXCLUDE_FROM_ALL]
    source1 [source2 ...]
)
```

`CMake`3.12版本之前：

- 目标库不能像其他库一样被链接(例如：不能使用`target_link_libraries()`)
- 要求使用生成器表达式作为其他可执行或者库对象的源码部分
- 因为不能被链接，所以不能透传依赖关系给链接它的对象
- 不方便，头文件路径，编译定义等信息都必须手动管理

`CMake`3.12以及之后的版本：

`CMake3.12`引入了一些特性，这些特性使目标库的表现更加像其他普通库，但是有一些需要注意的地方。

- 3.12之后可以使用`target_link_libraries()`
- 因为添加的是目标文件而不是真实的对象，传递当前库性质是更加严格的，目的是为了防止目标文件被多次添加到其他对象上

造成上述原因是因为，目标库是作为源码直接添加到连接对象上的，而不是通过连接对象传递给其他对象。然而实际使用中目标库文件通常会向其他对象库一样通过连接的方式进行传播，因此，因此需要更加严格的限制。

许多开发者可能会发现，几乎没有`CMake`工程中使用目标库，因为相比于目标库，静态库是一个更加方便，更优的选择。

就像可执行文件一样，库文件同样可以定义为导入的对象，他们被大量的用于打包过程或者`Find module`的执行过程，除了这些作用在其他地方使用导入对象库是有限制的。导入的对象库不是定一个库在项目中构建出来，而是引用一个已经在外部已经存在的库。

```cmake
add_library(targetName (STATIC | SHARED | MODULE | OBJECT | UNKNOWN)
    IMPORTED [GLOBAL]
)
```

库的类型要紧随`targetName`之后，如果库的被引用类型是已知的，那么这个库应该按照这种类型声明，这样讲允许`CMake`对待导入对象库(`IMPORED` 声明的)像普通工的库一样。

`OBJECT`类型只有`CMake`3.9之后的版本才能设置，之前的版本不支持这个类型，如果库的类型未知，应该设置成`UNKNOWN`类型，这样`CMake`就会使用库的全路径，而不是将来连接的时候检查复杂的链接器指令。

除了`OBJECT libraries`的上述类型，`IMPORTED`声明的库 在系统中的位置信息需要使用`IMPORTED_LOCATION`和/或`IMPORTED_LOCATION_<CONFIG>`进行属性设置<font  face="黑体" color = MediumVioletRed>(例如：在`windows`系统上两个属性应该设置`IMPORTED_LOCATION` 与`DLL`的关联，`IMPORTED_IMPLIB`与导入库关联通常有`.lib`的扩展名)</font>，而对于`OBJECT libraries`更重要的是使用`IMPORTED_OBJECTS`为导入目标库（`imported target `）其代表的一系列目标文件设置属性

导入库也支持许多其他的目标属性，这些属性大多数可以不管或者使用`CMake`的默认配置。需要编写配置包的开发者，应该通过`CMake`参考手册去了解`IMPORTED_`开头的目标属性。大多数`CMake`工程依赖`CMake`生成这些配置包，因此、需要手动去编写配置包的情况应该相当罕见。

默认情况下，导入库通常被定义为本地目标，这就意味者其仅在当前目录和子目录中可见。给出`GLOBAL`关键字时可以使导入库全局可见。一个库可能创建的时候不是全局的，但是随着使用的需要，后期需要变成全局可见的，这些问题将在第三小节的提升导入对象小节进行详细说明。

`test2`-工程外部库的使用

```cmake
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

```

另外一种形式的`add_library()`命令允许定义接口库。接口库通常不是一个真实存在的库，而是用于收集需求以及依赖关系传递给任何连接他们的东西。通常见到的地方是为头文件建立一个库，这个库不能真实生成一个库，但是可以将头文件路径，编译配置等信息转发给任何使用这些头文件的东西。

具体形式如下：

```cmake
add_library(targetName INTERFACE [IMPORTED [GLOBAL]])
```

所有需要传递的信息都可以通过`target_…()`开头使用`INTERFACE`关键字的命令转发。当然你也可以使用`set_property() or set_target_properties()`但是使用`target_…()`更加安全。

```cmake
add_library(myHeaderOnlyToolkit INTERFACE)
target_include_directories(myHeaderOnlyToolkit
	INTERFACE /some/path/include
)
target_compile_definitions(myHeaderOnlyToolkit
	INTERFACE COOL_FEATURE=1
	$<$<COMPILE_FEATURES:cxx_std_11>:HAVE_CXX11>
)
add_executable(myApp ...)
target_link_libraries(myApp PRIVATE myHeaderOnlyToolkit)
```

上述的示例中`myApp`目标链接了`myHeaderOnlyToolkit`那么通过`INTERFACE`定义的头文件路径`/some/path/include`以及`COOL_FEATURE=1`将传递给`myApp`.如果支持`cxx_std_11` `HAVE_CXX11`也将传递过去

`demo` -- `test4`

```cmake
#This should be the first line of the CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

# Poor practice, but very common
set(projectName MyProject)
project(${projectName} VERSION 4.7.2 LANGUAGES C)
#---------------------------------------------------------------------------------
# test 4 markdown
message("================================test4========================")

add_library(echo_demo echo_demo.c)

add_library(myHeaderOnlyToolkit INTERFACE)
target_include_directories(myHeaderOnlyToolkit
    INTERFACE ./inc
)
target_compile_definitions(myHeaderOnlyToolkit
    INTERFACE COOL_FEATURE=1
)

add_executable(myApp main.c)
target_link_libraries(myApp PRIVATE myHeaderOnlyToolkit)
target_link_libraries(echo_demo PRIVATE myHeaderOnlyToolkit)
target_link_libraries(myApp PRIVATE echo_demo)


#================================================
```

另外一种接口库的使用方式就是，通过接口库来方便的连接一系列库，如：

```cmake
# Regular library targets
add_library(algo_fast ...)
add_library(algo_accurate ...)
add_library(algo_beta ...)
# Convenience interface library
add_library(algo_all INTERFACE)
target_link_libraries(algo_all INTERFACE
algo_fast
algo_accurate
# 只有ENABLE_ALGO_BETA为true的时候才会链接algo_beta
$<$<BOOL:${ENABLE_ALGO_BETA}>:algo_beta>
)
# Other targets link to the interface library
# instead of each of the real libraries
add_executable(myApp ...)
target_link_libraries(myApp PRIVATE algo_all)
```

这种将不同的库抽象出来再实际中是非常有用的，经过抽象可以实现不同平台使用同样的库名，实际使用中只需要按照某些平台相关变量，将不同平台上库名不同但是实际作用相同的库抽象成同样的库名。实现屏蔽平台差异

接口库的原理很好理解，但是添加上`IMPORTED`之后的导入接口库会引起一些混淆。当`INTERFACE`库需要在工程外部使用的时候，常需要使用这种组合之后的导入接口库。当接口库被另外一个库使用时仍然是起到接口库的作用的，添加`IMPORTED`关键字是为了表明接口库来至其他地方，这样做的效果就是将库的可见性限制在当前目录范围内，而不是全局可见。有一个例外就是，当导入接口库声明`GLOBAL`的时候，几乎与接口库的作用一致，可见性也会变成全局的。导入接口库不需要设置(实际上是禁止)设置`IMPORTED_LOCATION`属性

在`CMake`3.11之前的版本，`target_…()`命令不能在导入库上设置`INTERFACE_....`属性，但是可以使用`set_property() or
set_target_properties()`设置。在3.11去除这个限制之后，`INTERFACE IMPORTED`声明和库的使用就和`INTERFACE IMPORTED`声明的库的使用非常接近了。

具体的关系总结如下表：

| `Keywords`                  | `Visibility` | `Imported LOacation` | `Set Interface Properties` | `Installable` |
| --------------------------- | ------------ | -------------------- | -------------------------- | ------------- |
| `INTERFACE`                 | `Global`     | `Prohibited`         | `Any method`               | `Yes`         |
| `IMPORTED`                  | `Local`      | `Required`           | `Restricted`               | `NO`          |
| `IMPORTED GLOBAL`           | `Global`     | `Required`           | `Restricted`               | `NO`          |
| `INTERFACE IMPORTED`        | `Local`      | `Prohibited`         | `Restricted`               | `NO`          |
| `INTERFACE IMPORTED GLOBAL` | `Global`     | `Prohibited`         | `Restricted`               | `NO`          |

接口和导入库结合过于复杂和混乱，对于大多数开发者来说，上述表格中很多都是不需要关注的，只有纯`INTERFACE`声明的接口库开发中会自己创建，剩下的工具自动完成的，不需要开发者实际参与。除了`INTERFACE`剩余的组合声明将在25章中进一步说明。

`add_library()`的最后一种使用方式是为库定义别名：

```cmake
add_library(aliasName ALIAS otherTarget)
```

库别名和可执行程序别名是一样的，也是一种只读方式的别名。库别名同样不能安装，不能再次定义别名，也就是不能定义库别名的别名。

==说明==：3.11之前库别名不能声明`IMPORTED`，3.11之后放开了这个限制

库别名的使用和`CMake`3.0引入的一项新特性相关，对于将要安装的库，一种常见模式是为库创建一个别名，别名以工程名开头作为自己的域名，所有该工程中的库的别名都共享这个域名：

`test5`

```cmake
# Any sort of real library (SHARED, STATIC, MODULE
# or possibly OBJECT)
add_library(myRealThings SHARED src1.cpp ...)
add_library(otherThings STATIC srcA.cpp ...)
# Aliases to the above with special names
add_library(BagOfBeans::myRealThings ALIAS myRealThings)
add_library(BagOfBeans::otherThings ALIAS otherThings)
```

在当前项目中链接原库或者链接域名库效果是一样的，使用别名的动机来至于---项目的安装和一些来至`installed/packaged`的配置文件中创建的导入目标(`imported targets`)，这些配置文件将导入库定义成带有域名的方式，工程也需要使用域名的方式引用这些库，例如：

```cmake
# Pull in imported targets from an installed package.
# See details in Chapter 23: Finding Things
find_package(BagOfBeans REQUIRED)
    # Define an executable that links to the imported
    # library from the installed package
    add_executable(eatLunch main.cpp ...)
    target_link_libraries(eatLunch PRIVATE
    BagOfBeans::myRealThings
)
```

如果将整个`BagOfBeans`工程直接合并到自己的项目中，而不是通过`find_package`来查找一个已安装的包，可以使用下面的方式，添加该实现。

```cmake
# Add BagOfBeans directly to this project, making
# all of its targets directly available
add_subdirectory(BagOfBeans)
    # Same definition of linking relationship still works
    add_executable(eatLunch main.cpp ...)
    target_link_libraries(eatLunch PRIVATE
    BagOfBeans::myRealThings
)
```

另外一个重要的点是，`CMake`会总是认为具有双冒号`::`的名字是别名或者导入目标。除了这两种情况，任何目标以其他方式使用`::`将会被当成错误处理。

突然来了这一句不知道是不是为了凑字数：<font face="微软雅黑" color=MediumVioletRed>在使用` target_link_library() `时，如果没法获取目标的名称，`CMake`会抛出错误。同样当库名没有提供的时候，`CMake`会默认为其为系统的库，将会在构建的过程中出现错误</font>如下：

`test6`

```cmake

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
```

书中给出能抛出异常的库：

```cmake
add_executable(main main.cpp)
add_library(bar STATIC ...)
add_library(foo::bar ALIAS bar)
# Typo in name being linked to, CMake will assume a
# library called "bart" will be provided by the
# system at link time and won't issue an error.
target_link_libraries(main PRIVATE bart)
# Typo in name being linked to, CMake flags an error
# at generation time because a namespaced name must
# be a CMake target.
# 因为域名不是工程的名字，所以同样也会报错
target_link_libraries(main PRIVATE foo::bart)
```

当域名存在时，连接带有域名的库更加的可靠和健壮，工程中鼓励使用域名，特别是为将要安装和打包的目标定义带有域名的别名。这种域名别名自己的工程也能使用，并不仅仅限于用在在子工程或者其他预先编译好的工程中

### 导入目标的提升

导入目标没有声明`GLOBAL`时，只能在当前目录或者子目录中可见。这种行为源于他们的主要用途，这种行为也是查找模块的特性，任何通过查找模块获取内容通常希望本地可见，所以导入目标通常不应该添加`GLOBAL`变成全局可见性，这样允许项目不同的模块使用相同的包和模块的同时使用不同的配置，并且保证相互之间互不干扰。

然而，有些时候需要导入目标的可见性是全局的，例如需要在这个项目中使用特定的包和指定的版本的时候，需要在创建导入包的时候添加`GLOBAL`关键字实现这一点，但是创建的过程在项目中可能是不可控的。为了解决这个问题`CMake`3.11版本引入了一个提升的导入目标控制属性字段`IMPORTED_GLOBAL`，将其设置为`ture`即可实现导入目标的全局可见性，需要注意的是这个属性是单向的，因此一旦提升为全局可见，就不可能在改为局部可见

```cmake
# Imported library created with local visibility.
# This could be in an external file brought in
# by an include() call rather than in the same
# file as the lines further below.
add_library(builtElsewhere STATIC IMPORTED)
set_target_properties(builtElsewhere PROPERTIES
	IMPORTED_LOCATION /path/to/libSomething.a
)
# Promote the imported target to global visibility
set_target_properties(builtElsewhere PROPERTIES
	IMPORTED_GLOBAL TRUE
)
```

重要的一点是，导入目标只能在与定义的地方相同的域中进行提升，不能提升父域中或者子域中定义的导入目标。`include()`命令不创建文件域同时也不调用`find_package()`命令，所以通过`include()`命令引入的导入目标是允许被提升的，这也是目标提升的主要实现方式。一旦一个目标被提升为全局可见，它同时也拥有了创建别名的能力。

### 建议实践

- `CMake`3.0版本对目标之间依赖和要求之间的管理进行了重大改变，解决了以前靠变量式的粗暴管理方式，是目标的管理更加精细化
- 一旦项目使用项目外部的包，就需要使用导入目标，开发人员应该熟练使用
- 一些久的项目使用变量的方式管理导入目标，应该尽量替换为新的导入目标管理方式
- 尽量使用静态库而不是对象库，对象库有实际用途，但是灵活性不如静态库
- 目标的命令不要过于简单，并且尽量为目标添加域名
- 当对库进行重构时，可能外部有依赖于这个老库的文件，这时使用别名的方式提供老库的连接方式

例如：

```cmake
# Old library previously defined like this:
add_library(deepCompute SHARED ...)
```

```cmake
# Now the library has been split in two, so define
# an interface library with the old name to effectively
# forward on the link dependency to the new libraries
add_library(computeAlgoA SHARED ...)
add_library(computeAlgoB SHARED ...)
add_library(deepCompute INTERFACE)
target_link_libraries(deepCompute INTERFACE
    computeAlgoA
    computeAlgoB
)
```









