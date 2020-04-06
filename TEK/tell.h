#ifndef __TELL_H__
#define __TELL_H__


//管道初始化
extern void init();

//利用管道进行等待
extern void wait_pipe();
//利用管道进行通知
extern void notify_pipe();
//销毁管道
extern void destroy_pipe();





#endif //TELL


