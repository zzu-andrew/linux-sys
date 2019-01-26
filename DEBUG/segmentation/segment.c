//##########################################
//使用 dbg 调试段错误
//##########################################
#include <stdio.h>




int main(int argc, char * argv[])
{

    int a = 0;


    int b = 12;

    //< 除0 出现段错误
    int c = b/a;



    return 0;

}




