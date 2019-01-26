1. ulimit -c

查看系统的核心转存储是否被限制为0 ，若是被限制为0使用

2. ulimit -c unlimited

将核心转存储设置为无限制

3. 编译程序加上-g 选项

4. 记性调试

gdb -c core文件 ./a.out







