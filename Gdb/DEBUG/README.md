# GDB就应该这样使用

													- [x] Andrew

[TOC]

 # 代码调试记录
# 使用方法，在主目录下执行make

因为执行脚本的时候会自动新启用一个子 bash因此在脚本中设置的ulimit -c unlimited
并不能产生核心转存储文件，需要执行可执行文件之前手动设置一下

ulimit -c unlimited

-------
DEBUG 是在linux下使用dbg的记录，一下的文件是在UBUNTU 16.04上验证通过的



# 准备

1.通过gcc 的 -g 选项生成调试信息。

```bash
gcc -Wall -O2 -g 源文件
```
2.如果使用Makefile构建，一般要给CFLAGS中指定 -g 选项
```
CFLAGS = -Wall -O2 -g
CFLAGS = -Wall -Werror  -O2 -g
加上 -Werror会在警告发生时，将其当成错误处理
```
3.如果使用configure脚本生成Makefile文件，可以这样使用。
```
./configure CFLAGS = "-Wall -O2 -g"
```
------

启动
gdb 可执行文件名
可以在函数名和行号等上设置断点，程序运行后，达到断点就会自动暂停运行。此时可以查看时刻的变量值、显示栈帧、重新设置断点或重新运行等。断点命令(break),可以简写为b.
##格式：
break 断点

(gdb) b main
断点可以通过函数名、当前文件内的行号来设置，也可以先指定文件名在指定行号，还可以指定与暂停位置的偏移量，或者地址来设置。
#格式说明：
```
break 函数名
break 行号
break 文件名：行号
break 文件名：函数名
break +偏移量
break -偏移量
break *地址

```

例：
```
在函数处加断点
(gdb)b iseq_compile
在文件名和行号处加断点
(gdb)b compile.c:516
设置偏移量
(gdb)b +3
在某地址处加断点
(gdb)b *0x88116fd6
如果不指定位置，就是在下一行代码上设置断点
(gdb)b
设置好的断点可以通过 info break 查看

```
```
andrew@andrew-Thurley:/work/linux-sys/DEBUG/segmentation$ gdb segment 
GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from segment...done.
(gdb) b main
Breakpoint 1 at 0x4004e1: file segment.c, line 12.
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000004004e1 in main at segment.c:12
(gdb) b +2
Note: breakpoint 1 also set at pc 0x4004e1.
Breakpoint 2 at 0x4004e1: file segment.c, line 5.
(gdb) info break
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000004004e1 in main at segment.c:12
2       breakpoint     keep y   0x00000000004004e1 in main at segment.c:5
(gdb) 


```

-------

## 运行
使用run命令开始运行，不加参数直接执行run 就会执行到设置断点的位置后暂停运行。可以简写为 r

------------------------------------------------------------
## 格式

```
run 参数
run  后面跟的参数，也就是你执行可执行文件后面需要跟的参数
(gdb)run -a
start命令会达到同样的效果。
格式：
start

```

---------------

## 显示栈帧
backtrace 命令可以在遇到断点而停止执行时显示栈帧。该命令简写为 bt 。此外，backtrace的别名还有 
 where 和 info stack(info s)

## 格式：

```
显示所有栈帧
 backtrace 
 bt

只显示开头N个栈帧
backtrace N
bt N

只显示最后N个栈帧
backtrace -N
bt -N


不仅显示backtrace，还要显示局部变量。N与前述的意思相同，表示N个(或者最后N个)栈帧
backtrace full 
bt full

backtrace full N
bt full N

backtrace full -N
bt full -N


例：
显示所有栈帧
(gdb)bt 
只显示前三个栈帧
(gdb)bt 3

从外向内显示3个栈帧，及局部变量
(gdb)bt full -3

```
-----------------

# 显示变量
print命令可以显示变量。print可以简写为p

## 格式;

```
print 变量

(gdb)p argv


```



-----------------


# 显示寄存器
```
info registers 可以显示寄存器，简写info reg

(gdb) info reg
rax            0x0	0
rbx            0x0	0
rcx            0x0	0
rdx            0x7ffcab228958	140723179653464
rsi            0x7ffcab228948	140723179653448
rdi            0x1	1
rbp            0x7ffcab228860	0x7ffcab228860
rsp            0x7ffcab228860	0x7ffcab228860
r8             0x400570	4195696
r9             0x7f2203168ab0	139784057424560
r10            0x846	2118
r11            0x7f2202dae740	139784053516096
r12            0x4003e0	4195296
r13            0x7ffcab228940	140723179653440
r14            0x0	0
r15            0x0	0
rip            0x4004ed	0x4004ed <main+23>
eflags         0x10246	[ PF ZF IF RF ]
cs             0x33	51
ss             0x2b	43
ds             0x0	0
es             0x0	0
fs             0x0	0
gs             0x0	0

---------------------
在寄存器之前添加 $，即可以显示各个寄存器的内容
(gdb)p $eax
(gdb) p $rip
$1 = (void (*)()) 0x4004ed <main+23>
(gdb) p $eflags
$2 = [ PF ZF IF RF ]
(gdb) p $eax
$3 = 0
(gdb) p $r8
$4 = 4195696
(gdb) p $rax
$5 = 0
(gdb) p $rdx
$6 = 140723179653464

显示时可以使用一下格式：
p/格式 变量
显示寄存器可以使用的格式：
格式                说明
x                   显示为十六进制数
d                   显示为十进制数
u                   显示为无符号十进制数
o                   显示为八进制数
t                   显示为二进制数，t的由来是two
a                   地址
c                   显示为字符(ASCII)
f                   浮点小数
s                   显示为字符串
i                   显示为机器语言(仅在显示内存的X命令中可以使用)
------------------------------------------------------


使用x命令可以显示内存的内容，x这个名字的由来是eXamining。

格式：
x/格式 地址
(gdb) x $pc
0x4004ed <main+23>:	0x000100c7
(gdb) x /x 0x4004ed
0x4004ed <main+23>:	0x000100c7
(gdb) x/i $pc
=> 0x4004ed <main+23>:	movl   $0x1,(%rax)

##x/i  的意思是显示汇编指令
一般使用 x 命令时，格式为 x/NFU ADDR。此处ADDR为希望显示的地址，N为重复的次数，F为前面讲过的格式(x,d,u,,o,t,a,c,f,s,i),U为表示2-4中所示的单位。

----------------------------------------------
U代表的单位
单位                      说明
b                         字节
h                         半字(2字节)
w                         字(4字节)(默认值)
g                         双字(8字节)
----------------------------------------------

#--> 从pc处显示十条指令

(gdb) x/10i
   0x4004f3 <main+29>:	mov    $0x0,%eax
   0x4004f8 <main+34>:	pop    %rbp
   0x4004f9 <main+35>:	retq
   0x4004fa:	nopw   0x0(%rax,%rax,1)
   0x400500 <__libc_csu_init>:	push   %r15
   0x400502 <__libc_csu_init+2>:	push   %r14
   0x400504 <__libc_csu_init+4>:	mov    %edi,%r15d
   0x400507 <__libc_csu_init+7>:	push   %r13
   0x400509 <__libc_csu_init+9>:	push   %r12
   0x40050b <__libc_csu_init+11>:	
    lea    0x2008fe(%rip),%r12        # 0x600e10
--------------------------------------------------------

1.disassemble.
2.disassemble 程序计数器
3.disassemble 开始地址 结束地址

1 --> 反汇编当前整个函数
2 --> 反汇编程序计数器所在函数的整个函数
3 --> 反汇编从开始地址到结束地址之间的部分

(gdb) disassemble $pc $pc+50
 






```
------------------------

## 单步执行
单步执行的意思是根据源代码一行一行执行。

执行源代码中的一行的命令为next(简写为 n)。执行时如果遇到函数调用，可能想执行到函数内部，此时可以使用step(简写为p) 命令。
也就是说当有子函数调用的时候，使用n命令直接执行子函数获得返回值，但是 step命令会进入子函数中执行；

next命令和step命令都是执行源代码中的一行，若果要逐条执行汇编指令，可以分别使用nexti命令和stepi命令

------------------------


## 继续执行
调试时，可以使用continue(简写为c)命令继续运行程序，程序会在遇到断点后再次暂停运行，
如果 没有遇到断点就会一直运行到结束。


```
格式：
continue 
continue 次数
指定次数可以忽略断点，例如，continue 5则5次遇断点不停止，第六次遇到断点才停止执行



```
------------------------------------------------------------------
## 监视点

大型软件或大量使用指针的程序中，很难男女感情变量在什么地方被改变。想要找到变量在何处被改变，可以使用watch命令(监视点，watchpoint)。

格式：
 watch <表达式>
<表达式>发生变化时暂停运行。
此处表达式的意识是常量或变量等。

格式：
awatch <表达式>
<表达式>被访问，改变时暂停运行。

格式：
rwatch <表达式>
<表达式>被访问时暂停运行。

------------------------------------------------------------------

## 删除断点和监视点
用delete(简写为 d)命令删除断点和监视点。
格式：

```
delete <编号>
删除编号指示的断点或监视点
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x0000000000400450 in main at watch.c:10
	breakpoint already hit 1 time
4       breakpoint     keep y   0x0000000000400450 in main at watch.c:10
	breakpoint already hit 1 time

-->删除1号断点
(gdb) d 1
(gdb) info b
Num     Type           Disp Enb Address            What
4       breakpoint     keep y   0x0000000000400450 in main at watch.c:10
	breakpoint already hit 1 time
  

```
------------------------------------------------------------------

## 其他断点

硬件断点(hbreak)，适用于ROM空间等无法修改的内存区域中的程序。在有些框架中无法使
用，临时断点(tbreak)和临时硬件断点(thbreak),与断点(硬件断点)相同，都会运行到该
处时暂停，不同之处就是临时断点(临时硬件断点)会在此时被删除，所以在只需要停止一次
时使用起来很方便。

------------------------------------------------------------------

## 改变变量的值
该功能可以在运行时，随意修改变量的值，因此无须修改源代码就能确认各种值的情况
格式：
```
set variable <变量> = <表达式>
例：
(gdb)p options
$7 =1
(gdb)set varaable options = 0
(gdb)p options 
$8 = 0

```
------------------------------------------------------------------

## 生成核心转存储文件
使用generate-core-file可将调试中的进程生成核心转存储文件
功能，将正在调试的文件生成核心转存储文件
有了内核转存储文件和调试对象，以后就能查看生成转存储文件时的运行历史(寄存器值，内存值等)。
例：
```
(gdb) generate-core-file 
Saved corefile core.16579


```
此外，gcore命令可以从命令行直接生成内核转存储文件。
```
gcore 'pidof emacs'
该命令无须停止正在运行的程序以获得内核转存储文件，当需要在其他机器上单独分析问题原因，或者是分心客户现场发生的问题时，十分有用。


```
------------------------------------------------------------------

## attach 到进程
## detach 与进程分离
确认行为之后，需要在gdb和进程分离时使用detach命令，这样调试中的进程就被从gdb的控制下释放出来，进程被detach后会继续运行


进程信息可以使用info proc命令显示

```
(gdb) info proc
process 22440
cmdline = '/work/linux-sys/DEBUG/watch/watch'
cwd = '/work/linux-sys/DEBUG/watch'
exe = '/work/linux-sys/DEBUG/watch/watch'

```


要调试守护进程(daemon process)等已经启动的进程，或者调试陷入死循环而无法返回的控制台进程时，可以使用attach命令
格式：
```
attach pid

```
执行这一命令就可以attach到进程ID为pid的进程上。
下面使用sleep命令进行GDB调试
```
andrew@andrew-Thurley:/work/linux-sys/DEBUG/segmentation$ sudo gdb
[sudo] andrew 的密码： 
GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word".
(gdb) attach 21414
Attaching to process 21414
Reading symbols from /bin/sleep...(no debugging symbols found)...done.
Reading symbols from /lib/x86_64-linux-gnu/libc.so.6...Reading symbols from /usr/lib/debug//lib/x86_64-linux-gnu/libc-2.23.so...done.
done.
Reading symbols from /lib64/ld-linux-x86-64.so.2...Reading symbols from /usr/lib/debug//lib/x86_64-linux-gnu/ld-2.23.so...done.
done.
0x00007ff7d77732f0 in __nanosleep_nocancel () at ../sysdeps/unix/syscall-template.S:84
84	../sysdeps/unix/syscall-template.S: 没有那个文件或目录.
(gdb) frame
#0  0x00007ff7d77732f0 in __nanosleep_nocancel ()
    at ../sysdeps/unix/syscall-template.S:84
84	in ../sysdeps/unix/syscall-template.S
(gdb) list
79	in ../sysdeps/unix/syscall-template.S
(gdb) generate-core-file 
warning: target file /proc/21414/cmdline contained unexpected null characters
Saved corefile core.21414


---------------------------------------------------------------------
andrew@andrew-Thurley:/work/linux-sys/DEBUG/watch$ sudo gdb
[sudo] andrew 的密码： 
GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word".
(gdb) attach 21531
Attaching to process 21531
Reading symbols from /bin/sleep...(no debugging symbols found)...done.
Reading symbols from /lib/x86_64-linux-gnu/libc.so.6...Reading symbols from /usr/lib/debug//lib/x86_64-linux-gnu/libc-2.23.so...done.
done.
Reading symbols from /lib64/ld-linux-x86-64.so.2...Reading symbols from /usr/lib/debug//lib/x86_64-linux-gnu/ld-2.23.so...done.
done.
0x00007f5e7b00e2f0 in __nanosleep_nocancel ()
    at ../sysdeps/unix/syscall-template.S:84
84	../sysdeps/unix/syscall-template.S: 没有那个文件或目录.
(gdb) bt
#0  0x00007f5e7b00e2f0 in __nanosleep_nocancel ()
    at ../sysdeps/unix/syscall-template.S:84
#1  0x00000000004040bf in ?? ()
#2  0x0000000000403f18 in ?? ()
#3  0x000000000040169a in ?? ()
#4  0x00007f5e7af62830 in __libc_start_main (main=0x4014e0, argc=2, 
    argv=0x7ffe79e6e518, init=<optimized out>, fini=<optimized out>, 
    rtld_fini=<optimized out>, stack_end=0x7ffe79e6e508)
    at ../csu/libc-start.c:291
#5  0x0000000000401789 in ?? ()

```
-------------------------
# 条件断点
在特定条件下执行中断

格式:
```bash
  break 断点 if 条件
```
这条命令将测试给定的条件，如果条件为真暂停运行。
例：
```bash
(gdb) b iseq_compile if node == 0

```

格式:
```bash
删除指定断点的出发条件
  condition 断点编号
添加指定断点的出发条件
  condition 断点编号 条件

```
该命令可以给指定的断点添加或者删除触发条件
----------------------------------------------
# 反复执行
```bash
ignore 断点编号  次数
```
在指定的断点、监视点(watchpoint)或捕获点(catchpoint)忽略指定的次数。
continue命令与ignore命令一样，可以指定次数，达到指定次数前执行到断点时不暂停，
二者意义相同。

格式;
```
continue 次数
step 次数
stepi 次数
next  次数
nexti 次数
```
这些命分别执行指定次数的相应命令。
格式:
```
finish
until
until 地址

```
finish 命令执行完当前函数后暂停，until命令执行完当前函数等代码块后暂停，
若果是循环，则执行完循环后暂停，常用于跳出循环。

------------------------------------
# 删除断点和禁用断点
用clear 命令删除已定义的断点，如果要保留定义，只想临时禁用断点的话，可以使用disable命令；
将禁用的断点重新启用，可以使用enable命令；
格式：

```
clear 
clear 函数名
clear 行号
clear 文件名：行号
clear 文件名：函数名
delete [breakpoints] 断点编号
```

格式：

```
disable [breakpoints]
disable [breakpoints] 断点编号
disable display 显示编号
disable mem 内存区域


```
如果不指定断点编号，则禁用多有的断点，否则禁用指定断点
第3种命令禁用display命令定义的自动显示
第4中格式禁用mem命令定义的内存区域
可以省略breakpoints关键字

格式：
```
enable [breakpoints]
enable [breakpoints] 断点编号
enable [breakpoints] once 断点编号
enable [breakpoints] delete 断点编号
enable display 显示编号
enable mem 内存区域
```

这些格式用于显示断点，once指定的断点只启用一次，也就是说，程序运行到该断点并暂停后，该断点即被禁用。
这与delete命令助攻的once不同，后者在运行暂停后删除断点

------------------------------------------
# 断点命令
断点命令(commands)可以定义在断点中断后执行的命令
格式：
```
commands 断点编号
	命令
	...
	end

```
程序在执行到断点处暂停后，就会自动执行命令

```
(gdb)b main
(gdb)command 2
	>p *b
	>end
(gdb)c
```

与前面的条件断点组合使用，就可以在断点暂停时，执行复杂的显示动作等

```
break foo if x>0
  commands
    silent
    printf "x is %d\n", x
    cont
  end
```
---------------------------------
# 常用命令即省略形式 
--------------

```
命令               简写形式         说明
backtrace          bt、where       显示backtrace
break              b               设置断点
continue           c、cont         继续执行
delete             d               删除断点
finish                             运行到函数结束
info breakpoints                   显示断点信息
next               n               执行下一行
print              p               显示表达式
run                r               运行程序
step               s               一次执行一行，包括函数内部
x                                  显示内存内容
until              u               执行到指定行
其他命令
directory          dir             插入目录
disable            dis             禁用断点
down               do              在当前调用的栈帧中选择要显示的栈帧
edit               e               编辑文件或者函数
frame              f               选择要显示的栈帧
forward-search     fo              向前搜索
generate-core-file gcore           生成内核转存储
help                h              显示帮助一览
info                i              显示信息
list                l              显示函数或行
nexti               ni             执行下一行(以汇编代码为单位)
print-object        po             显示目标信息
sharelibrary        share          加载共享的符号
stepi               si             执行下一行
```

info命令能够显示调试对象的各种各样的信息，另外show命令能够显示GDB内部的功能、变量和选项等。

--------------


# 值的历史
通过print 命令显示过的值会记录在内部的值历史中，这些值可以在其他表达式中使用
```
(gdb)p argc
(gdb)p *argc

最后的值可以通过 p $ 访问
也就说在这种情况下， p $  == > p *argc 

```
用 show value 命令可以显示历史中的最后 10 个值
```
(gdb)show value
$1
$2
$3
$4
.
.
.


```

值历史的访问说明

```
变量                    说明
$                       值历史的最后一个值
$n                      值历史的第n个值
$$                      值历史的倒数第2个值
$$n                     值历史倒数第n个值
$_                      x命令显示过的最后的地址
$__                     x命令显示过的最后的地址的值
$_exitcode              调试中的程序的返回码
$bpnum                 最后设置的断点编号 
```
--------------------------------------------
# 变量
可以随意的定义变量，变量以$ 开头，由英文字母和数字组成
```
(gdb)set $i = 0
(gdb)p $i
$1 = 0
```

-------------------------------------------------
# 命令历史
可以将命令历史保存在文件中，保存命令历史后，就能在其它调试会话中重复利用这些命令(通过箭头键以查找以前的命令)、
十分方便，默认的历史文件位于 ./.gdb_history
显示历史命令
```
show history
```

格式：

```
set hitory expansion
show history expansion
```
可以使用csh风格的！字符

格式：

```
set hitory filename 文件名
show history filename
```
可将命令历史保存到文件中，可以通过环境变量GDBHISTFILE改变默认文件名

格式：

```
set history save
show history save
```
启用命令历史保存到文件和恢复的功能

格式：
```
set history size 数字
show history size
```
设置保存到命令历史中的命令数量，默认值是256
星期六, 23. 二月 2019 12:20下午 

----------------------------------------------------

# 初始化文件(.gdbinit)
linux环境下初始化文件为 .gdbinit。如果存在.gdbinit 文件，GDB就会在启动之前将其作为命令文件运行，初始化文件和命令文件的运行顺序如下：
1、$HOME/.gdbinit
2、运行命令选项
3、./.gdbinit
4、通过 -x 选项给出的命令文件

初始化文件的语法和命令文件的语法相同，都由gdb命令组成

------------------------------
# 命令定义
利用define命令可以定义命令，还可以使用document命令给自定义的命令添加说明，用help命令名，可以查看定义的命令名
格式：
```
define 命令名
    命令
    ...
    end
```

格式：
```
document 命令名
    说明
    end
```
格式：
```
help 命令名
```
例：
定义了一个 名为 li的命令，它能显示当前 $pc 所指的位置开始的10条指令。另外，用document命令给li命令定义了说明，使用help li可以查看说明；

```
define li
    x/10i $pc
end
document
     list machine instruction
end
```

----------------------------------------
除了使用初始化文件，还可以将各种设置文件写在文件中，，在运行调试器时读取这些文件
格式;
```
source 文件名

```

-------------------------------
# 调试必需的栈知识
栈是程序存放数据的内存区域之一，其特征是LIFO(last in first out,后进先出)式数据结构，即后放进的数据先被取出，向栈中存储数据的操作称为PUSH(压入)，从栈中取出数据称为POP(弹出)，保存动态分配的自动变量时要使用栈，此外在函数调用时，栈还用于传递函数参数，以及用于保存返回地址和返回值。

```bash
-mno-red-zone
           Do not use a so-called "red zone" for x86-64 code.  The red zone is
           mandated by the x86-64 ABI; it is a 128-byte area beyond the
           location of the stack pointer that is not modified by signal or
           interrupt handlers and therefore can be used for temporary data
           without adjusting the stack pointer.  The flag -mno-red-zone
           disables this red zone.
```


调试选择栈帧，除了使用frame n 指定，还可以使用up down up是选择上一层栈帧，dowm是选择下一层栈帧
使用 info 命令的 frame 选项可以查看到更详细的栈帧信息，可以用帧编号作为该命令的选项
```bash
(gdb) info frame 0
Stack frame at 0x7fffffffdd50:
 rip = 0x40060e in main (sum.c:34); saved rip = 0x7ffff7a2d830
 source language c.
 Arglist at 0x7fffffffdd28, args: argc=<optimized out>, argv=0x7fffffffde28
 Locals at 0x7fffffffdd28, Previous frame's sp is 0x7fffffffdd50
 Saved registers:
  rip at 0x7fffffffdd48

```
x/i $pc --> 以汇编的形式查看当前栈帧处的代码
```bash
(gdb) x/i $pc
=> 0x400590 <main>:	sub    $0x18,%rsp
```



--------------------------------------------------------
(gdb) info proc mapping   --> 查看该进程内存映射的命令
process 13193
Mapped address spaces:
```bash
          Start Addr           End Addr       Size     Offset objfile
            0x400000           0x401000     0x1000        0x0 /work/linux-sys/DEBUG/sum/sum
            0x600000           0x601000     0x1000        0x0 /work/linux-sys/DEBUG/sum/sum
            0x601000           0x602000     0x1000     0x1000 /work/linux-sys/DEBUG/sum/sum
      0x7ffff7a0d000     0x7ffff7bcd000   0x1c0000        0x0 /lib/x86_64-linux-gnu/libc-2.23.so
      0x7ffff7bcd000     0x7ffff7dcd000   0x200000   0x1c0000 /lib/x86_64-linux-gnu/libc-2.23.so
      0x7ffff7dcd000     0x7ffff7dd1000     0x4000   0x1c0000 /lib/x86_64-linux-gnu/libc-2.23.so
      0x7ffff7dd1000     0x7ffff7dd3000     0x2000   0x1c4000 /lib/x86_64-linux-gnu/libc-2.23.so
      0x7ffff7dd3000     0x7ffff7dd7000     0x4000        0x0 
      0x7ffff7dd7000     0x7ffff7dfd000    0x26000        0x0 /lib/x86_64-linux-gnu/ld-2.23.so
      0x7ffff7fd0000     0x7ffff7fd3000     0x3000        0x0 
      0x7ffff7ff7000     0x7ffff7ffa000     0x3000        0x0 [vvar]
      0x7ffff7ffa000     0x7ffff7ffc000     0x2000        0x0 [vdso]
      0x7ffff7ffc000     0x7ffff7ffd000     0x1000    0x25000 /lib/x86_64-linux-gnu/ld-2.23.so
      0x7ffff7ffd000     0x7ffff7ffe000     0x1000    0x26000 /lib/x86_64-linux-gnu/ld-2.23.so
      0x7ffff7ffe000     0x7ffff7fff000     0x1000        0x0 
      0x7ffffffde000     0x7ffffffff000    0x21000        0x0 [stack] -->表示栈空间 ， 0x21000也就是栈空间的顶端
  0xffffffffff600000 0xffffffffff601000     0x1000        0x0 [vsyscall]
(gdb) p $pc
$1 = (void (*)()) 0x400590 <main>   pc的值为 0x400590 >  0x21000 说明还在栈内，没有栈溢出要是PC的值小于栈空间顶端的值，就是出现了栈溢出
(gdb) x/i $pc
=> 0x400590 <main>:	sub    $0x18,%rsp
```
说明：
可以使用info proc mapping 查看进程的内存映射，要保证占空间的栈顶端的值小于$pc的，否则就是出现了栈溢出
进程的内存映射也就是  /proc/<PID>/maps信息
注意后面显示的[stack] 。它表示栈空间，占空间的顶端的值要小于$pc的值，程序才能正常运行，说明栈没有溢出
但是使用该命令时，GDB文件会打开/proc/<PID>/maps，因此在分析coredump文件的时候无法使用，分析coredump文件的时候
可以使用下面的命令得到相同的信息。
(gdb)info files 
或者
(gdb)info target

星期六, 23. 二月 2019 12:20下午 

---------------------------

# 调试器的backtrace

GDB等调试器的backtrace功能是通过搜索栈中的保存信息来实现的。
栈信息对于调试器来说非常重要，关于栈破坏可以看HACK#27 backtrace无法正确显示和 HACK#28 数组非法访问导致内存破坏

编译时使用GCC指定  -formit-frame-pointer选项，即可生成不使用栈指针的二进制文件即使这样使用GDB依然能够正确理解帧，
因为GDB是根据记录在调试信息中的栈使用量来计算帧的位置的


## GDB提供了操作栈帧的命令
使用bt命令可以查栈的状态
使用frame可以查看现在选择的帧
```
(gdb) frame
#0  main (argc=1, argv=0x7fffffffde08) at segment.c:12
12	    int *a = NULL;
(gdb) bt
#0  main (argc=1, argv=0x7fffffffde08) at segment.c:12
(gdb) frame 1

查看上一层栈帧
同样使用
(gdb) up 意识查看上一层栈帧
(gdb) down是查看下一层栈帧

使用  i 命令的frame选项可以查看更加详细的栈信息，可以使用栈编号作为该命令的选项
(gdb) i frame 0====
Stack frame at 0x7fffffffdd30:
 rip = 0x4004e1 in main (segment.c:12); saved rip = 0x7ffff7a2d830
 source language c.
 Arglist at 0x7fffffffdd20, args: argc=1, argv=0x7fffffffde08
 Locals at 0x7fffffffdd20, Previous frame's sp is 0x7fffffffdd30
 Saved registers:
  rbp at 0x7fffffffdd20, rip at 0x7fffffffdd28

```
调试没有调试信息的程序，使用  b *func 即函数前面加上 * 因为不使用 *断点就不会设置到汇编语言层次的函数开头，
而是设置到地址偏后一点的源代码级别的开头，如果在break命令中不加* 直接使用函数名，就无法用于参数确认。

----------------------------------------------
 # #内核调试的准备
Oops信息的解读方法Oops信息是内核发生致命错误时输出的内核信息 

----
## 应用程序调试实践

## 发生SIGSEGV，应用程序异常停止

 - 由于栈溢出导致segmentation fault的调试
 应用程序执行了非法访问内存等操作之后，就会发生SIGSEGV异常而停止。SIGSEGV发生的情况包括：
  - NULL指针访问
  - 指针被破坏等原因导致的非法地址访问
  - 栈溢出导致访问超出了已分配的地址空间

## 栈溢出导致SIGSEGV的应对方法
## backtrace 无法正确显示

 - ==线程冲突导致的栈破坏为例讲述backtrace无法正确显示时的调试方法==
 栈破坏有事会导致问题难以分析，特别是，由于无法获取bcktrace信息，追溯到问题发生的路径非常难
 ~~为什么会产生这种信息不全的core文件~~
  - 什么是backtrace
    调试器的backtrace是根据栈里面保存的函数返回地址来显示的，根据栈空间上的返回地址和调试信息得出栈的使用量，以此求出调用者函数
    也就是说，调试器的backtrace的地址是来自进程的栈上，
    因此当backreace不正确的情况基本上就是因为栈被破坏了

  >说明栈被破坏的就不嗯给你信任调试器生成的backtrace信息，极端一点说，新来backtrace只有在栈没有被破坏的前提下才成立
  >认为调试器的信息绝对正确是十分危险的
  >
## 查看寄存器信息

利用GDB进行调试，寄存器信息是绝对不能忽视的

调查栈破坏的方法有很多种，但是最显示的方法就是根据被破坏的数据内容，判断执行写入的位置，看看又没哟对栈空间(也就是自动变量空间)的引用、指针传递处理。

## 数组非法访问导致内存破坏

==数组的错误操作==
错误的操作数组导致典型的bug之一就是缓存区溢出，也就是说向已分配的内存空间写入数据，特别是如果这类bug发生在栈上的缓存区中，就可能引发安全漏洞

当使用-g编译选项之后利用GDB读入core并显示backtrace之后栈中的还是没有显示符号名，可以怀疑是缓冲区溢出的情况

这时使用 x/i +地址显示查看栈中地址的汇编语言，再根据程序在该架构中常放置的地址和共享内存常放置的地址判断是否是数组越界

### 调查栈的方法

```bash
(gdb) x/30c $esp-15
p (char *) $esp-20
```



##  确定破坏跳转地址值的位置(GOT破坏)

访问互数据空间中静态分配的数组时，如果出现bug也会出现类似的现象

# 利用监视点检查非法内存访问

- 监视点能在指定的变量或地址的数据被访问时展厅程序运行

- [x] 具体使用见上文

调试时程序在手头并且可以立即复现bug使用监视点调试 能够高效的确定bug所在。

- 监视点设置

`(gdb) watch *0x80459a8`

直接指定地址而不是变量或者函数需要加上`*`

# malloc() 和 free()发生故障

## 错误的使用内存相关函数引起的Bug

```bash
gdb ./membug -c core
```

不正常的使用*malloc*和*free*可能造成内存破坏，程序继续运行，此时、可能产生以下后果

- 会在完全没关系的地方产生**SIGSEGV**
- 使用被破坏的数据进行计算，产生错误的结果

##　利用**MALLOC_CHECK_**进行调试

现在glibc中有个方便的调试标志，可以利用环境变量进行调试

例如：

```c
env MALLOC_CHECK_=1 ./membug
```

可以进行检查

但是该方法只是检查出有问题，并没有检查出问题出在哪里，也没有说明应用程序有bug





## 使用nuttcp 测量吞吐量

《Debug Hacks中文版--深入调试的技术和工具》本书是Miracle Linux的创始人吉冈弘隆和几位工程师们多年从事内核开发的经验积累。从调试器的基本使用方法、汇编的基础知识开始，到内核错误信息捕捉、应用程序调试、内核调试，本书深入浅出地讲解了Linux下应用程序和内核的调试技巧。本节为大家介绍使用nuttcp 测量吞吐量。

**使用nuttcp 测量吞吐量**

下面测量普通的网络设备和VLAN 设备的吞吐量，这里使用nuttcp。nuttcp 是个TCP/UDP 网络测试工具，可以测量吞吐量。

```bash
# wget -t0 -c http://www.lcp.nrl.navy.
mil/nuttcp/nuttcp-5.5.5.tar.bz2  
# tar jxvf nuttcp-5.5.5.tar.bz2  
# cd nuttcp-5.5.5  
# gcc -O2 -o nuttcp nuttcp-5.5.5.c  
在receiver 上通过以下选项启动nuttcp 服务器。  
[receiver]# ./nuttcp -S 
```

同样在sender 上执行nuttcp 发包，用-n 选项设置发送的总数据量为1GB。为使数据包分段，可以通过-l 选项设置数据写入长度为1500 字节。

```bash
[sender]# ./nuttcp -n1G -l1500 192.168.1.100 /* 一般网络 */  
1023.9987 MB / 9.12 sec = 941.3975 Mbps 12 %TX 18 %RX  
[sender]# ./nuttcp -n1G -l1500 192.168.0.100 /* VLAN 网络 */  
1023.9987 MB / 9.15 sec = 938.5309 Mbps 22 %TX 19 %RX 
```

开头的数据为发送的数据大小，通过选项设置成发送1GB。下一个值是发送数据所需的时间，接下来是吞吐量（Mbps）。VLAN 网络的吞吐量稍稍低一些。此外，%TX和%RX 为发送进程（sender）和接收进程（receiver）的CPU 使用率。ps 等命令中的CPU 使用率是进程生存期间使用的CPU 时间百分比，但nuttcp 是根据发送接收信息之前到发送接收信息完成之后的时间段中，所用的CPU 时间（用户时间+内核时间）计算的百分比。可见，一般网络中发送进程的CPU 使用率（%TX）为12%，而VLAN网络中该值为22%。尽管吞吐量没有太大差异，但CPU使用率却增加了10%。

# strace寻找问题故障

使用`strace`定位问题，可以使用命令

```c
 strace -t -p `pidof`
```

- -t的意识是加上时间戳

-  strace能够跟踪进程使用的系统调用，并显示其内容。因此，调试内容不明的故障时，首先使用strace找出系统调用出错的地方，通常能够得出故障发生的线索，特别是与文件有关的错误、参数错误等

  > 该方法能够有效的发现系统调用失败有关的故障，但无法发现用户写出的程序或共享库中发生的错误。

  

## strace 使用的范例

找不到要访问的文件或无权限访问文件等情况下，系统调用通常会原样返回错误内容。下面用程序st1.c确认下实际情况。

```c
//##########################################
//使用 dbg 调试段错误
//##########################################
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{

    FILE *fp;
    fp = fopen("/etc/shadow", "r");
    if (fp == NULL)
    {
        printf("Error !\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


```

```bash
$ ./segment 
Error !
```

- 执行失败的原因是试图打开一般用户没有读权限的`/etc/shadow`文件

- 输出错误但是错误的消息不明显，这时使用GDB也很难设置断点进行调试

```c
andrew@andrew-Thurley:/work/linux-sys/DEBUG/str$ strace ./segment 
execve("./segment", ["./segment"], [/* 63 vars */]) = 0
brk(NULL)                               = 0x1cc6000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=144422, ...}) = 0
mmap(NULL, 144422, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fe166260000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\t\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1868984, ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe16625f000
mmap(NULL, 3971488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fe165c95000
mprotect(0x7fe165e55000, 2097152, PROT_NONE) = 0
mmap(0x7fe166055000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c0000) = 0x7fe166055000
mmap(0x7fe16605b000, 14752, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fe16605b000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe16625e000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe16625d000
arch_prctl(ARCH_SET_FS, 0x7fe16625e700) = 0
mprotect(0x7fe166055000, 16384, PROT_READ) = 0
mprotect(0x600000, 4096, PROT_READ)     = 0
mprotect(0x7fe166284000, 4096, PROT_READ) = 0
munmap(0x7fe166260000, 144422)          = 0
brk(NULL)                               = 0x1cc6000
brk(0x1ce7000)                          = 0x1ce7000
open("/etc/shadow", O_RDONLY)           = -1 EACCES (Permission denied)
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 19), ...}) = 0
write(1, "Error !\n", 8Error !
)                = 8
exit_group(1)                           = ?
+++ exited with 1 +++

```



##  使用strace + GDB对程序进行详细调查

- 使用`strace -i`可以显示程序在哪个地址进行了系统调用，可以将该地址作为断点使用。 

```c
andrew@andrew-Thurley:/work/linux-sys/DEBUG/str$ strace -i ./segment 
[00007f5dace1d777] execve("./segment", ["./segment"], [/* 63 vars */]) = 0
[00007f851d2a04b9] brk(NULL)            = 0xf7a000
[00007f851d2a13c7] access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
[00007f851d2a13c7] access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
[00007f851d2a1367] open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
[00007f851d2a12f4] fstat(3, {st_mode=S_IFREG|0644, st_size=144422, ...}) = 0
[00007f851d2a14ba] mmap(NULL, 144422, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f851d487000
[00007f851d2a1467] close(3)             = 0
[00007f851d2a13c7] access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
[00007f851d2a1367] open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
[00007f851d2a1387] read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\t\2\0\0\0\0\0"..., 832) = 832
[00007f851d2a12f4] fstat(3, {st_mode=S_IFREG|0755, st_size=1868984, ...}) = 0
[00007f851d2a14ba] mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f851d486000
[00007f851d2a14ba] mmap(NULL, 3971488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f851cebc000
[00007f851d2a1557] mprotect(0x7f851d07c000, 2097152, PROT_NONE) = 0
[00007f851d2a14ba] mmap(0x7f851d27c000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c0000) = 0x7f851d27c000
[00007f851d2a14ba] mmap(0x7f851d282000, 14752, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f851d282000
[00007f851d2a1467] close(3)             = 0
[00007f851d2a14ba] mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f851d485000
[00007f851d2a14ba] mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f851d484000
[00007f851d286bd5] arch_prctl(ARCH_SET_FS, 0x7f851d485700) = 0
[00007f851d2a1557] mprotect(0x7f851d27c000, 16384, PROT_READ) = 0
[00007f851d2a1557] mprotect(0x600000, 4096, PROT_READ) = 0
[00007f851d2a1557] mprotect(0x7f851d4ab000, 4096, PROT_READ) = 0
[00007f851d2a1537] munmap(0x7f851d487000, 144422) = 0
[00007f851cfb8e19] brk(NULL)            = 0xf7a000
[00007f851cfb8e19] brk(0xf9b000)        = 0xf9b000
[00007f851cfb3040] open("/etc/shadow", O_RDONLY) = -1 EACCES (Permission denied)
[00007f851cfb2c34] fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 19), ...}) = 0
[00007f851cfb32c0] write(1, "Error !\n", 8Error !
) = 8
[00007f851cf88748] exit_group(1)        = ?
[????????????????] +++ exited with 1 +++
andrew@andrew-Thurley:/work/linux-sys/DEBUG/str$ 
```

- 在各行开头  `[]`中的数字就是执行系统的代码地址，子啊GDB中执行该地址并显示`backtrace`.





## strace attach 到进程上

- 刚才使用`strace`启动进程并检查了它的行为，接下来以下面的程序为例讲解一下如何使用`strace`查看运行中的进程(如守护进程)的行为。

- 改进从上述程序 增加循环，是程序一直循环去尝试打开没有权限的文件
- 函数如下:

```c

//##########################################
//##########################################
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    while(1)
    {
        FILE *fp;
        fp = fopen("/etc/shadow", "r");
        if (fp == NULL)
        {
            printf("Error !\n");
        }
        else
        {
            fclose(fp);
        }
        sleep(3);
    }
    return EXIT_SUCCESS;
}



```





- 首先执行

```bash
andrew@andrew-Thurley:/work/linux-sys/DEBUG/strace-demo$ ./segment &
```

**打开另外一个窗口**

- 使用`strace attach`上正在运行的进程 



```c
andrew@andrew-Thurley:/work/linux-sys/DEBUG/strace-demo$ sudo strace -p `pidof segment`
[sudo] andrew 的密码： 
strace: Process 7729 attached
restart_syscall(<... resuming interrupted nanosleep ...>) = 0
open("/etc/shadow", O_RDONLY)           = -1 EACCES (Permission denied)
write(1, "Error !\n", 8)                = 8
nanosleep({3, 0}, 0x7ffe0f047cb0)       = 0
open("/etc/shadow", O_RDONLY)           = -1 EACCES (Permission denied)
write(1, "Error !\n", 8)                = 8
nanosleep({3, 0}, 0x7ffe0f047cb0)       = 0
open("/etc/shadow", O_RDONLY)           = -1 EACCES (Permission denied)
write(1, "Error !\n", 8)                = 8
nanosleep({3, 0}, 0x7ffe0f047cb0)       = 0
open("/etc/shadow", O_RDONLY)           = -1 EACCES (Permission denied)

```





---

## 其它方便的用法

**如下加上 -o 选项可以将显示的内容输出到文件中**

==`$ strace -o output.log commad`==

`strace`的输出为标准错误输出，因此可以像下面这样将显示的内容输出到标准输出上在传给grep、less等

```bash
$strace command 2>$1 | grep map
$strace command 2>$1 | grep less

```

进程执行fork之后要跟踪fork()之后的进程，可以使用 ==-f==选项。

```bash
$strace -f command
```

系统调用执行时刻可以使用`-t`或`-tt`选项来显示。两者不同的地方是， -t 以秒为单位， `-tt`以毫秒为单位



```bash
$strace -t command
$strace -tt command
```



# objdump的方便选项



> objdump的选项 `-S、-l`十分方便。若果二进制文件中带有调试信息，可以像下面这样将源代码、文件名及行数与汇编代码对应系显示，

`$ objdump -Sl --no-show-raw-insn astall`

- **C 源文件**

```c
//##########################################
//使用 dbg 调试段错误
//##########################################
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int cnt = 0;

void cnt_reset(void)
{
    pthread_mutex_lock(&mutex);
    cnt = 0;
    pthread_mutex_unlock(&mutex);
}

void *thr(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(cnt > 2)
        {
            cnt_reset();
        }
        else
        {
            cnt ++;
        }
        pthread_mutex_unlock(&mutex);

        printf("%d\n\n", cnt);
        sleep(1);
    }
}

int main(int argc, char * argv[])
{

    pthread_t tid;
    
    pthread_create(&tid, NULL, thr , NULL);
    pthread_join(tid, NULL);
    return EXIT_SUCCESS;

}


```



```S

astall：     文件格式 elf64-x86-64


Disassembly of section .init:

0000000000400658 <_init>:
_init():
  400658:	sub    $0x8,%rsp
  40065c:	mov    0x200995(%rip),%rax        # 600ff8 <_DYNAMIC+0x1e0>
  400663:	test   %rax,%rax
  400666:	je     40066d <_init+0x15>
  400668:	callq  400710 <pthread_mutex_lock@plt+0x10>
  40066d:	add    $0x8,%rsp
  400671:	retq   

Disassembly of section .plt:

0000000000400680 <pthread_create@plt-0x10>:
  400680:	pushq  0x200982(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400686:	jmpq   *0x200984(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40068c:	nopl   0x0(%rax)

0000000000400690 <pthread_create@plt>:
  400690:	jmpq   *0x200982(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400696:	pushq  $0x0
  40069b:	jmpq   400680 <_init+0x28>

00000000004006a0 <__stack_chk_fail@plt>:
  4006a0:	jmpq   *0x20097a(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  4006a6:	pushq  $0x1
  4006ab:	jmpq   400680 <_init+0x28>

00000000004006b0 <__libc_start_main@plt>:
  4006b0:	jmpq   *0x200972(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  4006b6:	pushq  $0x2
  4006bb:	jmpq   400680 <_init+0x28>

00000000004006c0 <pthread_mutex_unlock@plt>:
  4006c0:	jmpq   *0x20096a(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  4006c6:	pushq  $0x3
  4006cb:	jmpq   400680 <_init+0x28>

00000000004006d0 <__printf_chk@plt>:
  4006d0:	jmpq   *0x200962(%rip)        # 601038 <_GLOBAL_OFFSET_TABLE_+0x38>
  4006d6:	pushq  $0x4
  4006db:	jmpq   400680 <_init+0x28>

00000000004006e0 <pthread_join@plt>:
  4006e0:	jmpq   *0x20095a(%rip)        # 601040 <_GLOBAL_OFFSET_TABLE_+0x40>
  4006e6:	pushq  $0x5
  4006eb:	jmpq   400680 <_init+0x28>

00000000004006f0 <sleep@plt>:
  4006f0:	jmpq   *0x200952(%rip)        # 601048 <_GLOBAL_OFFSET_TABLE_+0x48>
  4006f6:	pushq  $0x6
  4006fb:	jmpq   400680 <_init+0x28>

0000000000400700 <pthread_mutex_lock@plt>:
  400700:	jmpq   *0x20094a(%rip)        # 601050 <_GLOBAL_OFFSET_TABLE_+0x50>
  400706:	pushq  $0x7
  40070b:	jmpq   400680 <_init+0x28>

Disassembly of section .plt.got:

0000000000400710 <.plt.got>:
  400710:	jmpq   *0x2008e2(%rip)        # 600ff8 <_DYNAMIC+0x1e0>
  400716:	xchg   %ax,%ax

Disassembly of section .text:

0000000000400720 <main>:
main():
/work/linux-sys/DEBUG/astall/astall.c:41
        sleep(1);
    }
}

int main(int argc, char * argv[])
{
  400720:	sub    $0x18,%rsp
/work/linux-sys/DEBUG/astall/astall.c:45

    pthread_t tid;
    
    pthread_create(&tid, NULL, thr , NULL);
  400724:	xor    %ecx,%ecx
  400726:	mov    $0x400870,%edx
  40072b:	xor    %esi,%esi
  40072d:	mov    %rsp,%rdi
/work/linux-sys/DEBUG/astall/astall.c:41
        sleep(1);
    }
}

int main(int argc, char * argv[])
{
  400730:	mov    %fs:0x28,%rax
  400739:	mov    %rax,0x8(%rsp)
  40073e:	xor    %eax,%eax
/work/linux-sys/DEBUG/astall/astall.c:45

    pthread_t tid;
    
    pthread_create(&tid, NULL, thr , NULL);
  400740:	callq  400690 <pthread_create@plt>
/work/linux-sys/DEBUG/astall/astall.c:46
    pthread_join(tid, NULL);
  400745:	mov    (%rsp),%rdi
  400749:	xor    %esi,%esi
  40074b:	callq  4006e0 <pthread_join@plt>
/work/linux-sys/DEBUG/astall/astall.c:49
    return EXIT_SUCCESS;

}
  400750:	mov    0x8(%rsp),%rdx
  400755:	xor    %fs:0x28,%rdx
  40075e:	jne    400767 <main+0x47>
  400760:	xor    %eax,%eax
  400762:	add    $0x18,%rsp
  400766:	retq   
  400767:	callq  4006a0 <__stack_chk_fail@plt>
  40076c:	nopl   0x0(%rax)

0000000000400770 <_start>:
_start():
  400770:	xor    %ebp,%ebp
  400772:	mov    %rdx,%r9
  400775:	pop    %rsi
  400776:	mov    %rsp,%rdx
  400779:	and    $0xfffffffffffffff0,%rsp
  40077d:	push   %rax
  40077e:	push   %rsp
  40077f:	mov    $0x400990,%r8
  400786:	mov    $0x400920,%rcx
  40078d:	mov    $0x400720,%rdi
  400794:	callq  4006b0 <__libc_start_main@plt>
  400799:	hlt    
  40079a:	nopw   0x0(%rax,%rax,1)

00000000004007a0 <deregister_tm_clones>:
deregister_tm_clones():
  4007a0:	mov    $0x60106f,%eax
  4007a5:	push   %rbp
  4007a6:	sub    $0x601068,%rax
  4007ac:	cmp    $0xe,%rax
  4007b0:	mov    %rsp,%rbp
  4007b3:	jbe    4007d0 <deregister_tm_clones+0x30>
  4007b5:	mov    $0x0,%eax
  4007ba:	test   %rax,%rax
  4007bd:	je     4007d0 <deregister_tm_clones+0x30>
  4007bf:	pop    %rbp
  4007c0:	mov    $0x601068,%edi
  4007c5:	jmpq   *%rax
  4007c7:	nopw   0x0(%rax,%rax,1)
  4007d0:	pop    %rbp
  4007d1:	retq   
  4007d2:	nopl   0x0(%rax)
  4007d6:	nopw   %cs:0x0(%rax,%rax,1)

00000000004007e0 <register_tm_clones>:
register_tm_clones():
  4007e0:	mov    $0x601068,%esi
  4007e5:	push   %rbp
  4007e6:	sub    $0x601068,%rsi
  4007ed:	sar    $0x3,%rsi
  4007f1:	mov    %rsp,%rbp
  4007f4:	mov    %rsi,%rax
  4007f7:	shr    $0x3f,%rax
  4007fb:	add    %rax,%rsi
  4007fe:	sar    %rsi
  400801:	je     400818 <register_tm_clones+0x38>
  400803:	mov    $0x0,%eax
  400808:	test   %rax,%rax
  40080b:	je     400818 <register_tm_clones+0x38>
  40080d:	pop    %rbp
  40080e:	mov    $0x601068,%edi
  400813:	jmpq   *%rax
  400815:	nopl   (%rax)
  400818:	pop    %rbp
  400819:	retq   
  40081a:	nopw   0x0(%rax,%rax,1)

0000000000400820 <__do_global_dtors_aux>:
__do_global_dtors_aux():
  400820:	cmpb   $0x0,0x200859(%rip)        # 601080 <completed.7594>
  400827:	jne    40083a <__do_global_dtors_aux+0x1a>
  400829:	push   %rbp
  40082a:	mov    %rsp,%rbp
  40082d:	callq  4007a0 <deregister_tm_clones>
  400832:	pop    %rbp
  400833:	movb   $0x1,0x200846(%rip)        # 601080 <completed.7594>
  40083a:	repz retq 
  40083c:	nopl   0x0(%rax)

0000000000400840 <frame_dummy>:
frame_dummy():
  400840:	mov    $0x600e10,%edi
  400845:	cmpq   $0x0,(%rdi)
  400849:	jne    400850 <frame_dummy+0x10>
  40084b:	jmp    4007e0 <register_tm_clones>
  40084d:	nopl   (%rax)
  400850:	mov    $0x0,%eax
  400855:	test   %rax,%rax
  400858:	je     40084b <frame_dummy+0xb>
  40085a:	push   %rbp
  40085b:	mov    %rsp,%rbp
  40085e:	callq  *%rax
  400860:	pop    %rbp
  400861:	jmpq   4007e0 <register_tm_clones>
  400866:	nopw   %cs:0x0(%rax,%rax,1)

0000000000400870 <thr>:
thr():
/work/linux-sys/DEBUG/astall/astall.c:21
    cnt = 0;
    pthread_mutex_unlock(&mutex);
}

void *thr(void *arg)
{
  400870:	sub    $0x8,%rsp
  400874:	jmp    4008b4 <thr+0x44>
  400876:	nopw   %cs:0x0(%rax,%rax,1)
/work/linux-sys/DEBUG/astall/astall.c:31
        {
            cnt_reset();
        }
        else
        {
            cnt ++;
  400880:	add    $0x1,%eax
  400883:	mov    %eax,0x200817(%rip)        # 6010a0 <cnt>
/work/linux-sys/DEBUG/astall/astall.c:33
        }
        pthread_mutex_unlock(&mutex);
  400889:	mov    $0x6010c0,%edi
  40088e:	callq  4006c0 <pthread_mutex_unlock@plt>
printf():
/usr/include/x86_64-linux-gnu/bits/stdio2.h:104
}

__fortify_function int
printf (const char *__restrict __fmt, ...)
{
  return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
  400893:	mov    0x200807(%rip),%edx        # 6010a0 <cnt>
  400899:	mov    $0x1,%edi
  40089e:	mov    $0x4009a4,%esi
  4008a3:	xor    %eax,%eax
  4008a5:	callq  4006d0 <__printf_chk@plt>
thr():
/work/linux-sys/DEBUG/astall/astall.c:36

        printf("%d\n\n", cnt);
        sleep(1);
  4008aa:	mov    $0x1,%edi
  4008af:	callq  4006f0 <sleep@plt>
/work/linux-sys/DEBUG/astall/astall.c:24

void *thr(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
  4008b4:	mov    $0x6010c0,%edi
  4008b9:	callq  400700 <pthread_mutex_lock@plt>
/work/linux-sys/DEBUG/astall/astall.c:25
        if(cnt > 2)
  4008be:	mov    0x2007dc(%rip),%eax        # 6010a0 <cnt>
  4008c4:	cmp    $0x2,%eax
  4008c7:	jle    400880 <thr+0x10>
cnt_reset():
/work/linux-sys/DEBUG/astall/astall.c:15

int cnt = 0;

void cnt_reset(void)
{
    pthread_mutex_lock(&mutex);
  4008c9:	mov    $0x6010c0,%edi
  4008ce:	callq  400700 <pthread_mutex_lock@plt>
/work/linux-sys/DEBUG/astall/astall.c:17
    cnt = 0;
    pthread_mutex_unlock(&mutex);
  4008d3:	mov    $0x6010c0,%edi
/work/linux-sys/DEBUG/astall/astall.c:16
int cnt = 0;

void cnt_reset(void)
{
    pthread_mutex_lock(&mutex);
    cnt = 0;
  4008d8:	movl   $0x0,0x2007be(%rip)        # 6010a0 <cnt>
/work/linux-sys/DEBUG/astall/astall.c:17
    pthread_mutex_unlock(&mutex);
  4008e2:	callq  4006c0 <pthread_mutex_unlock@plt>
  4008e7:	jmp    400889 <thr+0x19>
thr():
  4008e9:	nopl   0x0(%rax)

00000000004008f0 <cnt_reset>:
cnt_reset():
/work/linux-sys/DEBUG/astall/astall.c:14
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int cnt = 0;

void cnt_reset(void)
{
  4008f0:	sub    $0x8,%rsp
/work/linux-sys/DEBUG/astall/astall.c:15
    pthread_mutex_lock(&mutex);
  4008f4:	mov    $0x6010c0,%edi
  4008f9:	callq  400700 <pthread_mutex_lock@plt>
/work/linux-sys/DEBUG/astall/astall.c:16
    cnt = 0;
  4008fe:	movl   $0x0,0x200798(%rip)        # 6010a0 <cnt>
/work/linux-sys/DEBUG/astall/astall.c:17
    pthread_mutex_unlock(&mutex);
  400908:	mov    $0x6010c0,%edi
/work/linux-sys/DEBUG/astall/astall.c:18
}
  40090d:	add    $0x8,%rsp
/work/linux-sys/DEBUG/astall/astall.c:17

void cnt_reset(void)
{
    pthread_mutex_lock(&mutex);
    cnt = 0;
    pthread_mutex_unlock(&mutex);
  400911:	jmpq   4006c0 <pthread_mutex_unlock@plt>
  400916:	nopw   %cs:0x0(%rax,%rax,1)

0000000000400920 <__libc_csu_init>:
__libc_csu_init():
  400920:	push   %r15
  400922:	push   %r14
  400924:	mov    %edi,%r15d
  400927:	push   %r13
  400929:	push   %r12
  40092b:	lea    0x2004ce(%rip),%r12        # 600e00 <__frame_dummy_init_array_entry>
  400932:	push   %rbp
  400933:	lea    0x2004ce(%rip),%rbp        # 600e08 <__init_array_end>
  40093a:	push   %rbx
  40093b:	mov    %rsi,%r14
  40093e:	mov    %rdx,%r13
  400941:	sub    %r12,%rbp
  400944:	sub    $0x8,%rsp
  400948:	sar    $0x3,%rbp
  40094c:	callq  400658 <_init>
  400951:	test   %rbp,%rbp
  400954:	je     400976 <__libc_csu_init+0x56>
  400956:	xor    %ebx,%ebx
  400958:	nopl   0x0(%rax,%rax,1)
  400960:	mov    %r13,%rdx
  400963:	mov    %r14,%rsi
  400966:	mov    %r15d,%edi
  400969:	callq  *(%r12,%rbx,8)
  40096d:	add    $0x1,%rbx
  400971:	cmp    %rbp,%rbx
  400974:	jne    400960 <__libc_csu_init+0x40>
  400976:	add    $0x8,%rsp
  40097a:	pop    %rbx
  40097b:	pop    %rbp
  40097c:	pop    %r12
  40097e:	pop    %r13
  400980:	pop    %r14
  400982:	pop    %r15
  400984:	retq   
  400985:	nop
  400986:	nopw   %cs:0x0(%rax,%rax,1)

0000000000400990 <__libc_csu_fini>:
__libc_csu_fini():
  400990:	repz retq 

Disassembly of section .fini:

0000000000400994 <_fini>:
_fini():
  400994:	sub    $0x8,%rsp
  400998:	add    $0x8,%rsp
  40099c:	retq   

```



> 注：这种显示方式需要使用调试信息，因此可使用GCC编译时必须加上`-g`选项，而且汇编语言和源代码总会发生一些偏差；
>
> > 还有使用`addr2line`命令，能够输出与`objdump`的`-l`选项相同的信息





# Valgrind的使用方法(基本篇)

**`Valgrind是什么`**

`Valgrind`能够检出内存的非法使用，对缓存、堆进行测评(profile)，检测POSIX线程的冲突等。

- `Valgrind`的特征之一就是检测对象程序在编译时无须指定特定的选项，也不需要连接特别的函数库。

##  `Valgrind`用于检测内存非法使用

`$valgrind --tool=memcheck --leak-check=yes program`

- 此外：检测内存非法使用(memcheck)，为默认启用选项，因此可以只输入下面的命令。
- `$valgrind --leak-check=yes program`

使用：

`valgrind program`

##  `Valgrind`用于对非法内存地址的访问

##  `Valgrind`用于检测读取未初始化区域的错误

##  `Valgrind`用于检测访问已释放的区域

##  `Valgrind`用于检测内存双重释放

##  `Valgrind`用于检测非法栈操作

> 但是不能检测栈上生成内存区域的非法访问引起的错误





# Valgrind的使用方法(实践篇)

> 使用top命令长时间监视内存使用量，若是一个程序内存泄露的话，进程虚拟内存使用量(VIRT和RES)就会随着时间增长，VIRT和RES的区别是，VIRT中包含被交换(swap)出的空间，而RES不包含

## 很难发现的内存泄露

> 相反如果内存泄露量很小，用前面的说的方法就很难检测，但是如果几个月几年长时间执行程序，内存资源就会被慢慢消耗，某天就会发生OOM Killer

`dlopen`是在运行时加载库的函数，`dlclose`是关闭打开的共享库

`$valgrind --leak-check=full prog`





# 利用`kprobes`获取内核内部信息






















|      |      |      |      |      |
| ---- | ---- | ---- | ---- | ---- |
|      |      |      |      |      |
|      |      |      |      |      |
|      |      |      |      |      |
|      |      |      |      |      |
|      |      |      |      |      |























------------------------------------
魔法键 = CTRL+PgUp键 之后按键 h   p打印寄存器信息













































