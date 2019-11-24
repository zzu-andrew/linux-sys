echo "这是一个命令"; ls ; pwd

touch testfile

FILENAME=testfile

if [ -x "$FILENAME" ]; then
    echo "$FILENAME 可执行"
else 
    echo "$FILENAME 不可执行"
fi

