[TOC]





# AUTOMAKE



## 小试牛刀

### 所需文件

**使用automake管理单个可执行程序**

- 所需文件

1. hello--文件夹
2. hello/Makefile.am
3. hello/configure.ac
4. hello/inc--文件夹
5. hello/src--文件夹
6. hello/src/main.c
7. hello/src/Makefile.am
8. hello/README

**文件内容如下：**

```bash
andrew@andrew-Thurley:~/work/hello$ cat configure.ac 
AC_INIT([hello], [1.0], [564631192@qq.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])
AC_OUTPUT
andrew@andrew-Thurley:~/work/hello$ 

andrew@andrew-Thurley:~/work/hello$ cat Makefile.am 
SUBDIRS = src
dist_doc_DATA = README
andrew@andrew-Thurley:~/work/hello$ 

andrew@andrew-Thurley:~/work/hello$ cat README 
This is a test for automakeandrew@andrew-Thurley:~/work/hello$ 


andrew@andrew-Thurley:~/work/hello$ cat src/Makefile.am 
bin_PROGRAMS = hello
hello_SOURCES = main.c


andrew@andrew-Thurley:~/work/hello$ cat src/main.c 
#include <stdio.h>
#include "config.h"

int main(int argc, char* argv[])
{
    puts("Hello world!\n");
    puts("This is " PACKAGE_STRING ".");
    return 0;
}

```



### 执行步骤

**执行autoreconf --install**

```bash
andrew@andrew-Thurley:~/work/hello$ autoreconf --install 
configure.ac:3: installing './compile'
configure.ac:2: installing './install-sh'
configure.ac:2: installing './missing'
src/Makefile.am: installing './depcomp'

```

除了生成上述三个文件之外，执行 `autoreconf --install`之后还会生成，`configure config.h.in Makefile.in and src/Makefile.in`，带有后缀`in`的是临时文件，执行`configure`之后会生成对应的`config.h Makefile src/Makeifle`. 

`autoreconf`其实是一个脚本，会按照正确的顺序调用`autoconf automake`等， 所以仅需调用`autoreconf`就不用担心自己调用脚本的顺序是否正缺正确了，`autoreconf`会按照正确的顺序执行对应的命令。

**执行./configure**

执行`./configure`用于生成对应`Makeifle`脚本和`config.h`头文件。

```bash
andrew@andrew-Thurley:~/work/hello$ ./configure 
checking for a BSD-compatible install... /usr/bin/install -c
checking whether build environment is sane... yes
checking for a thread-safe mkdir -p... /bin/mkdir -p
checking for gawk... no
checking for mawk... mawk
checking whether make sets $(MAKE)... yes
checking whether make supports nested variables... yes
checking for gcc... gcc
checking whether the C compiler works... yes
checking for C compiler default output file name... a.out
checking for suffix of executables... 
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether we are using the GNU C compiler... yes
checking whether gcc accepts -g... yes
checking for gcc option to accept ISO C89... none needed
checking whether gcc understands -c and -o together... yes
checking for style of include used by make... GNU
checking dependency style of gcc... gcc3
checking that generated files are newer than configure... done
configure: creating ./config.status
config.status: creating Makefile
config.status: creating src/Makefile
config.status: creating config.h
config.status: executing depfiles commands

```

**执行make**

执行`make`生成可执行文件

```bash
andrew@andrew-Thurley:~/work/hello$ make
make  all-recursive
make[1]: Entering directory '/home/andrew/work/hello'
Making all in src
make[2]: Entering directory '/home/andrew/work/hello/src'
gcc -DHAVE_CONFIG_H -I. -I..     -g -O2 -MT main.o -MD -MP -MF .deps/main.Tpo -c -o main.o main.c
mv -f .deps/main.Tpo .deps/main.Po
gcc  -g -O2   -o hello main.o  
make[2]: Leaving directory '/home/andrew/work/hello/src'
make[2]: Entering directory '/home/andrew/work/hello'
make[2]: Leaving directory '/home/andrew/work/hello'
make[1]: Leaving directory '/home/andrew/work/hello'

```

### 文件含义

**configure.ac**

`configure.ac`会用于`autoconf`和`automake`用于生成`makefile.ins`

```bash
andrew@andrew-Thurley:~/work/hello$ cat configure.ac 
# AC_ autoconf 宏，初始化autoconf
# AC_INIT 中的参数列表，代表的意思，文件夹名，版本号，bug报告地址
AC_INIT([hello], [1.0], [564631192@qq.com])
# AM_ automake 宏 初始化automake
# AM_INIT_AUTOMAKE 中的参数列表是，传递给automake的，
# foreign 告诉automake这个工程不是标准的GNU项目，有些文件GNU中的必要的文件可以缺失
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
# 告诉configure去寻找C编译器，并使用CC编译hello,configure将CC定义成对应编译工具
AC_PROG_CC
# autoconf会将上述定义的变量，生成对应的宏定义放到对应的config.h中
AC_CONFIG_HEADERS([config.h])
p17
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])
AC_OUTPUT


andrew@andrew-Thurley:~/work/hello$ 

andrew@andrew-Thurley:~/work/hello$ cat Makefile.am 
SUBDIRS = src
dist_doc_DATA = README
andrew@andrew-Thurley:~/work/hello$ 

andrew@andrew-Thurley:~/work/hello$ cat README 
This is a test for automakeandrew@andrew-Thurley:~/work/hello$ 


andrew@andrew-Thurley:~/work/hello$ cat src/Makefile.am 
bin_PROGRAMS = hello
hello_SOURCES = main.c


andrew@andrew-Thurley:~/work/hello$ cat src/main.c 
#include <stdio.h>
#include "config.h"

int main(int argc, char* argv[])
{
    puts("Hello world!\n");
    puts("This is " PACKAGE_STRING ".");
    return 0;
}

```

















[完整代码地址链接](https://github.com/zzu-andrew/linux-sys/tree/dfew/automake)