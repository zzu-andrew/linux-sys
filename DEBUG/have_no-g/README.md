1. ulimit -c

查看系统的核心转存储是否被限制为0 ，若是被限制为0使用

2. ulimit -c unlimited

将核心转存储设置为无限制

3. 编译程序加上-g 选项

4. 调试
要想使用GDB调试内核转存储文件，应当以以下方式启动GDB

gdb -c core文件 ./a.out

在使用大型文件系统时，会希望将内核转存储放在固定的位置。默认情况下会在当前目录下生成，但是可能很难弄清文件在哪在哪生成。这种情况下可以配置/etc/systl.conf文件，来决定文件的生成目录和文件的命名；

例如在/etc/systl.conf 文件中添加如下内容：
kernel.core_pattern = /var/core/%t-%e-%p-%c.core
kernel.core_uses_pid = 0
然后执行
# sysctl -p 
上述生成核心转存储文件的命名：
时刻-进程名-PID-内核转存储最大大小.core
kernel.core_pattern中可以设置的格式符：
```
格式符                    说明
%%		          %字符自身
%p                        被转存储进程的进程ID(PID)
%u                        被转存储进程的真实用户ID(real UID)
%g                        被转存储进程的真实组ID(real GID)
%s                        引发转存储的信号编号
%t                        转存储时刻(从1970年1月1日 0:00 开始的秒数)
%h                        主机名(同uname(2)返回的nodename)
%e                        可执行文件名
%c                        转存储文件的大小上限(内核版本2.6.24以后可以使用)

```
kernel.core_uses_pid = 0 设置为0是因为我们改变了文件名中的PID的位置，如果设置该值为1，文件名末尾就会添加.PID



# ===================================
-------------------------------------------------------


(gdb) info proc mapping
process 13193
Mapped address spaces:

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

说明：
可以使用info proc mapping 查看进程的内存映射，要保证占空间的栈顶端的值小于$pc的，否则就是出现了栈溢出
进程的内存映射也就是  /proc/<PID>/maps信息

------------------------------------------------------
# 函数参数与调试
使用-g 参数编译的可执行文件调试很方便，但是有时候会遇到没有加-g选项但是需要调试的文件
在x86_64中，整形和指针型的参数会从左至右一次保存到rdi、rsi、rdx、rcx、r8、r9中，浮点型会保存到xmm0、xmm1、、、中，多于这些寄存器
的参数会被保存到栈上，因此，利用GDB在希望确认的函数开头中断之后，查看寄存器或栈即可获得参数内容
此外，以后应当在函数名前加上  * 号，因为、不加  * 号，断点就不会设置到汇编语言层次的函数开头，而是设置到地址偏后一点的源代码级别的
开头，大多数情况下，函数开头会进行一下栈操作。由于参数也可能保存在栈上，如果break命令中不加 * 号，直接使用函数名，就无法用于参数确认。







































