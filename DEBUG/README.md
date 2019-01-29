 # 代码调试记录
 # 使用方法，在主目录下执行make

因为执行脚本的时候会自动新启用一个子 bash因此在脚本中设置的ulimit -c unlimited
并不能产生核心转存储文件，需要执行可执行文件之前手动设置一下

ulimit -c unlimited
 
-------
DEBUG 是在linux下使用dbg的记录，一下的文件是在UBUNTU 16.04上验证通过的

# ============================


# 准备 
1.通过gcc 的 -g 选项生成调试信息。
```
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
#=============
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
# =================

##运行
使用run命令开始运行，不加参数直接执行run 就会执行到设置断点的位置后暂停运行。可以简写为 r

# -------------------------------------------------------------------
##格式
```
run 参数
run  后面跟的参数，也就是你执行可执行文件后面需要跟的参数
(gdb)run -a
start命令会达到同样的效果。
格式：
start

```

---------------
#-=============================
##显示栈帧
backtrace 命令可以在遇到断点而停止执行时显示栈帧。该命令简写为 bt 。此外，backtrace的别名还有 
 where 和 info stack(info s)

##格式：
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
#=======================================================

#显示变量
print命令可以显示变量。print可以简写为p

##格式;

```
print 变量

(gdb)p argv


```



-----------------
#=======================================================

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
# =========================================================

## 单步执行
单步执行的意思是根据源代码一行一行执行。

执行源代码中的一行的命令为next(简写为 n)。执行时如果遇到函数调用，可能想执行到函数内部，此时可以使用step(简写为p) 命令。
也就是说当有子函数调用的时候，使用n命令直接执行子函数获得返回值，但是 step命令会进入子函数中执行；

next命令和step命令都是执行源代码中的一行，若果要逐条执行汇编指令，可以分别使用nexti命令和stepi命令


------------------------
# =========================================================

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
# ===================================================
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
# ===================================================
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
# ===================================================
## 其他断点

硬件断点(hbreak)，适用于ROM空间等无法修改的内存区域中的程序。在有些框架中无法使
用，临时断点(tbreak)和临时硬件断点(thbreak),与断点(硬件断点)相同，都会运行到该
处时暂停，不同之处就是临时断点(临时硬件断点)会在此时被删除，所以在只需要停止一次
时使用起来很方便。

------------------------------------------------------------------
# ===================================================
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
# ===================================================
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
# ===================================================
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
```
  break 断点 if 条件
```
这条命令将测试给定的条件，如果条件为真暂停运行。
例：
```
(gdb) b iseq_compile if node == 0

```

格式:
```
删除指定断点的出发条件
  condition 断点编号
添加指定断点的出发条件
  condition 断点编号 条件

```
该命令可以给指定的断点添加或者删除触发条件
----------------------------------------------
# 反复执行
```
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
断点命令
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





















 















































































