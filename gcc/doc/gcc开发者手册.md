







### 编译阶段技巧说明

- 放在头文件或者源文件中声明，编译该文件的时候会出现提示

```c
#error This file requires compiler and library support \
for the ISO C++ 2011 standard. This support must be enabled \
with the -std=c++11 or -std=gnu++11 compiler options.
```

