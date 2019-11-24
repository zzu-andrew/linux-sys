#! /bin/bash

# 使用trap实现在每个函数开始之前打印以便打印，这样就能准确的定位到函数的位置
# 从而实现对脚本的调试
trap "echo before a func is called" DEBUG

# 当. 或者 source 调用结束的时候出发
trap "echo . or source is called "  RETURN

func()
{

    echo "不管你信不信，这是一个函数"
    exit 0
}

# 测试
echo "call ."
. traptest

# 函数的调用
func


# DEBUG 调试信号的有效性
#trap -p RETURN
# trap -p DEBUG


exit 0
