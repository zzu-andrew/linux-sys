[TOC]





# AUTOMAKE



## 管理单个可执行文件

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
# 定义 configure应该根据 *.in等临时文件，生成的文件
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])
# 结束命令，实际生成，AC_CONFIG_HEADERS  AC_CONFIG_FILES 中注册的文件
AC_OUTPUT
```

**Makefile.am**

```bash
# SUBDIRS 指定需要构建的文件夹
# make dist时，会自动的将README发布，这里的dist_doc_DATA 是留给make install使用的
# The line dist_doc_DATA = README causes README to be distributed and installed in
# docdir.
andrew@andrew-Thurley:~/work/hello$ cat Makefile.am 
SUBDIRS = src
dist_doc_DATA = README
andrew@andrew-Thurley:~/work/hello$ 

# 包含automake指令，用于构建和安装hello
# bin_PROGRAMS 是需要安装的可执行文件，如果文件不需要安装可以使用 noinst_PROGRAMS
# _PROGRAMS构建文件
# _SCRIPTS 生成脚本
# _DATA 生成数据文件
# _LIBRARIES 生成库文件
# make dist 发布文件时，source文件也会打到发布的文件中
andrew@andrew-Thurley:~/work/hello$ cat src/Makefile.am 
bin_PROGRAMS = hello
hello_SOURCES = main.c
```

说明：

`The line dist_doc_DATA = README causes README to be distributed and installed in
docdir. Files listed with the _DATA primary are not automatically part of the tarball built
with make dist, so we add the dist_ prefix so they get distributed. However, for README it
would not have been necessary: automake automatically distributes any README file it en-
counters (the list of other files automatically distributed is presented by automake --help).
The only important effect of this second line is therefore to install README during make
install.`

### 发布程序

`make dist`

```bash
andrew@andrew-Thurley:~/work/hello$ make dist
make  dist-gzip am__post_remove_distdir='@:'
make[1]: Entering directory '/home/andrew/work/hello'
if test -d "hello-1.0"; then find "hello-1.0" -type d ! -perm -200 -exec chmod u+w {} ';' && rm -rf "hello-1.0" || { sleep 5 && rm -rf "hello-1.0"; }; else :; fi
test -d "hello-1.0" || mkdir "hello-1.0"
 (cd src && make  top_distdir=../hello-1.0 distdir=../hello-1.0/src \
     am__remove_distdir=: am__skip_length_check=: am__skip_mode_fix=: distdir)
make[2]: Entering directory '/home/andrew/work/hello/src'
make[2]: Leaving directory '/home/andrew/work/hello/src'
test -n "" \
|| find "hello-1.0" -type d ! -perm -755 \
	-exec chmod u+rwx,go+rx {} \; -o \
  ! -type d ! -perm -444 -links 1 -exec chmod a+r {} \; -o \
  ! -type d ! -perm -400 -exec chmod a+r {} \; -o \
  ! -type d ! -perm -444 -exec /bin/bash /home/andrew/work/hello/install-sh -c -m a+r {} {} \; \
|| chmod -R a+r "hello-1.0"
tardir=hello-1.0 && ${TAR-tar} chof - "$tardir" | GZIP=--best gzip -c >hello-1.0.tar.gz
make[1]: Leaving directory '/home/andrew/work/hello'
if test -d "hello-1.0"; then find "hello-1.0" -type d ! -perm -200 -exec chmod u+w {} ';' && rm -rf "hello-1.0" || { sleep 5 && rm -rf "hello-1.0"; }; else :; fi
```



### 扩展

**多个文件编译**

```bash
andrew@andrew-Thurley:/work/linux-sys/automake/zardoz$ cat configure.ac 
AC_INIT([zardoz], [1.0], [564631192@qq.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])
AC_OUTPUT

andrew@andrew-Thurley:/work/linux-sys/automake/zardoz$ cat src/Makefile.am 
bin_PROGRAMS = zardoz
zardoz_SOURCES = main.c head.c float.c vortex9.c  gun.c
zardoz_LDADD =  $(LIBOBJS)
AM_CFLAGS = -lm -I./../inc

```

### build true and false

**使用不同的编译参数，构建多个文件**

当需要构建不同的文件时，可以通过下面的方式实现构建多个文件，使用不同的编译选项

```bash
andrew@andrew-Thurley:/work/linux-sys/automake/mulexec$ cat src/Makefile.am 
bin_PROGRAMS = true false
true_SOURCES = main.c
true_CPPFLAGS = -lm -DTRUE

false_SOURCES = main.c
false_CPPFLAGS =  -DFALSE

```





## example

**编译可执行文件**

```bash
#Makefile.am文件
bin_PROGRAMS = xxx
#bin_PROGRAMS 表示指定要生成的可执行应用程序文件，这表示可执行文件在安装时需要被安装到系统
#中；如果只是想编译，不想被安装到系统中，可以用noinst_PROGRAMS来代替

xxx_SOURCES = a.c b.c c.c main.c d.c xxx.c
#xxx_SOURCES表示生成可执行应用程序所用的源文件，这里注意，xxx_是由前面的bin_PROGRAMS
#指定的，如果前面是生成example,那么这里就是example_SOURCES，其它的类似标识也是一样

xxx_CPPFLAGS = -DCONFIG_DIR=\"$(sysconfdir)\" -DLIBRARY_DIR=\"$(pkglibdir)\"
#xxx_CPPFLAGS 这和Makefile文件中一样，表示C语言预处理参数，这里指定了DCONFIG_DIR，以后
#在程序中，就可以直接使用CONFIG_DIR。不要把这个和另一个CFLAGS混淆，后者表示编译器参数

xxx_LDFLAGS = -export-dynamic -lmemcached
#xxx_LDFLAGS 连接的时候所需库文件的标识，这个也就是对应一些如-l,-shared等选项

noinst_HEADERS = xxx.h
#这个表示该头文件只是参加可执行文件的编译，而不用安装到安装目录下。如果需要安装到系统中，
#可以用include_HEADERS来代替

INCLUDES = -I/usr/local/libmemcached/include/
#INCLUDES  链接时所需要的头文件

xxx_LDADD = $(top_builddir)/sx/libsession.a \
                $(top_builddir)/util/libutil.a
#xxx_LDADD 链接时所需要的库文件，这里表示需要两个库文件的支持
```

**编译动态库**

```bash
#Makefile.am文件
xxxlibdir=$(libdir)//新建一个目录，该目录就是lib目录，运行后xxx.so将安装在该目录下 
xxxlib_PROGRAMS=xxx.so  
xxx_so_SOURCES=xxx.c
xxx_so_LDFLAGS=-shared -fpic //GCC编译动态库的选项
```

**编译静态库**

```bash
#Makefile.am文件 noinst 说明该库不需要安装
noinst_LTLIBRARIES = xxx.a
noinst_HEADERS = a.h b.h
xxx_a_SOURCES = a.c b.c xxx.c
```



[完整代码地址链接](https://github.com/zzu-andrew/linux-sys/tree/dfew/automake)