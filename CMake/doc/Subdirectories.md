## Using Subdirectories

一个简单的工程只是用一个文件夹是很方便的，但是现实中的工程往往有很多的文件夹，这时就需要引入`add_subdirectory()`与`include()`了。

### add_subdirectory()

使用`add_subdirectory()`添加的文件夹中必须要包含`CMakeLists.txt`文件，调用之后会在构建目录中创建对应的子文件夹

```cmake
add_subdirectory(sourceDir [ binaryDir ] [ EXCLUDE_FROM_ALL ])
```

虽然添加的`sourceDir`一般都是源码目录下的一个子文件夹，但是并不一定非得是工程文件下的子文件夹，任何文件夹都是可以被添加的。

`binaryDir`不指定的时候，会在构建目录中创建一个和源码同名的子目录

`EXCLUDE_FROM_ALL` 并包含在内，一般添加了之后该指令下子目录下的文件就不会执行但是该指令通常不会像预期那样执行，因此最好不要使用或者依赖该指令的返回。

在`UBUNTU`实测，当添加该指令的时候执行`cmake`之后再`make`会发现没有编译子目录下的代码，当没有添加该指令的时候会编译子目录下的源码。

[subdir源码路径]: https://github.com/zzu-andrew/linux-sys/blob/ee6b5d5f509b8e2900e8fa0d12a04d28623e960a/CMake/subdir/source/CMakeLists.txt#L10	"subdir"













