#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>




#ifndef BUF_SIZE        /* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif


int main(int argc, char *argv[])
{
    int inputFd, outputFd, openFlags;
    //< 文件权限
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        printf("%s old-file new-file\n", argv[0]);

   
    //< 已只读方式打开文件第一个参数指定的已经存在的文件
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
        printf("opening file %s", argv[1]);

    //< 指定打开文件的方式
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;

    //< 指定打开文件后，文件描述符所具有的文件权限
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;      /* rw-rw-rw- */
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1)
        printf("opening file %s", argv[2]);

    /* Transfer data until we encounter end of input or an error */

    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)  //< 文件中有值就一直 进行读取知道文件读取返回文件结尾符号
        if (write(outputFd, buf, numRead) != numRead)
            printf("couldn't write whole buffer");
    if (numRead == -1)
        printf("read");

    if (close(inputFd) == -1)
        printf("close input");
    if (close(outputFd) == -1)
        printf("close output");

    exit(EXIT_SUCCESS);
}

