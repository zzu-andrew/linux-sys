#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char * argv[])
{

    FILE *fp = NULL;
    //命令执行的结果放到fp指向的结构体缓存中
    //读取命令结果
    fp = popen("cat /etc/passwd", "r");
    char buf[512];
    memset(buf, 0, sizeof(buf));
    while(fgets(buf,sizeof(buf), fp) != NULL)
    {
        printf("%s", buf);
    }
    pclose(fp);
printf("------------------------------------------------------------\n");
//向命令写入，将1 2 3 写入管道经过  wc -l 统计出文件有多少行
    fp = popen("wc -l", "w");
    fprintf(fp, "1\n2\n3\n");
    pclose(fp);

    exit(0);
}













