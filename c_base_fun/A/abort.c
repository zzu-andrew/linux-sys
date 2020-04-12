#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void signalHandler(int sig);

// 信号处理函数
void signalHandler(int sig)
{
  if(sig == SIGABRT)    //对应ctrl+c
  {
    printf("abort 函数被调用，触发SIGABRT信号量 。\n");
  }
}
//以下是主函数
int main(int argc,char *argv[])
{
  signal(SIGABRT, signalHandler);   //注册SIGINT对应的处理函数

  abort();
 
  printf("程序走不到这里。\n");
  return 0;
}
