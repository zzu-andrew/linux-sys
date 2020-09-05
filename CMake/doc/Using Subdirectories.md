## Using Subdirectories

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



































