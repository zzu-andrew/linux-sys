#! /bin/bash
echo "cat cleanup example2"

# 确保输入文件名，否则退出
if test $# != 1 ; then
    echo "请输入要清除文件内容的文件名"
    # 脚本退出返回的值，可通过 echo $? 查看
    exit 1
fi

FILE_NAME=$1
cat /dev/null > ${FILE_NAME}

echo "file is cleanup"
exit #这是一个退出命令