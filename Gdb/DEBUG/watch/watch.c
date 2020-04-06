//##########################################
//使用 dbg 调试段错误
//##########################################
#include <stdio.h>




int main(int argc, char * argv[])
{

    int a = 0;
    int *b = NULL;

    b = &a;
     (*b) = 12; 

    printf("a = %d",a);

    return 0;

}




