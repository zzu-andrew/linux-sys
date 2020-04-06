#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>


int main(int argc, char *argv[])
{

    off_t offset;
    int fd;
    ssize_t numWritten;


    fd = open(argv[1], O_RDWR | O_CREAT,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH);                     /* rw-rw-rw- */
    if (fd == -1)
        perror("open");

        
    offset = 10000;
    if (lseek(fd, offset, SEEK_SET) == -1)
            perror("lseek");
    printf("%s: seek succeeded\n", "10000");
    numWritten = write(fd, "abc", strlen("abc"));
    printf("write  = %ld\n", (long int)numWritten);




    if (close(fd) == -1)
        perror("close");

    exit(0);
}
