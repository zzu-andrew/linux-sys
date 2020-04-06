#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


char *cmd1[3] = {"/bin/cat", "/etc/passwd", NULL};
char *cmd2[3] = {"/bin/grep", "root", NULL};


int main(int argc,char* argv[])
{
    int fd[2];
    if (pipe(fd) < 0)
    {
        perror("pipe error!");
        exit(1);
    }

    int i = 0;
    pid_t pid;
    for (; i < 2; i++)
    {
        pid = fork();
        if(pid < 0)
        {
            perror("fork error!");
            exit(1);
        }
        else if (pid == 0)
        {
            if(i == 0)
            {//关闭读端，保留写端
                close(fd[0]);
                if (execvp(cmd1[0], cmd1) < 0)
                {
                    perror("excevp() error!");
                    exit(1);
                }
                break;
            }

            if( i == 1)
            {
                close(fd[1]);
                if (execvp(cmd2[0], cmd2) < 0)
                {
                    perror("Error !!!!!!!");
                    exit(1);
                }
                break;
            }
        }
        else
        {
            if(i == 1)
            {

                close(fd[0]);
                close(fd[1]);
                wait(0);
                wait(0);
            }
        }
        
    }





   exit(0); 
}









