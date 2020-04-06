#!/bin/bash
# trap设置在函数中的tap也是全局有效的
foo()
{    
    trap "echo func is called" DEBUG 
}



# 输出　func is called
foo

# 调试触发
#trap -p DEBUG
# 输出trap -- 'echo func is called' SIGINT
exit 0