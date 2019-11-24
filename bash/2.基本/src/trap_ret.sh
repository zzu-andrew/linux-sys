#!/bin/bash
# 使用trap来捕捉变量值.

＃　EXIT代表在函数退出前，执行trap
trap 'echo Variable Listing --- ret=${ret}' EXIT

ps -A
if [ $? == 0 ];then
    echo "commond exec OK!"
    ret=0
else
    ret=1
fi

echo "注意这里，还没有调用trap"

# trap是在退出的时候清理程序时调用的
exit 0