1. ulimit -c

查看系统的核心转存储是否被限制为0 ，若是被限制为0使用

2. ulimit -c unlimited

将核心转存储设置为无限制

3. 编译程序加上-g 选项

4. 调试


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



# ==========================================================================
# watch.c文件示例

awatch short_output
结合命令  c continue使用，一旦short_output发生变化就会停止
short_output
























