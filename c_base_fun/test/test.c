#include <stdio.h>
#include <stdio.h>
#include <math.h> //NAN
//#的作用是将关键字转换为对应的字符
#define Peval(cmd) printf(#cmd ": %g\n", cmd);

#define Setup_list(name, ...) \
    double *name ## _list = (double []){__VA_ARGS__, NAN}; \
    int name ## _len = 0; \
    for (name ## _len =0; \
    !isnan(name ## _list[name ## _len]); \
    ) name ## _len ++;

int main()
{
    //  测试单个#
    double *plist = (double[]){1, 2, 3};
    double list[] = {1, 2, 3};
    Peval(sizeof(plist)/(sizeof(double)+0.0));
    Peval(sizeof(list)/(sizeof(double)+0.0));

    // 测试双 ##
    Setup_list(items, 1, 2, 4, 8);
    double sum=0;
    for (double *ptr= items_list; !isnan(*ptr); ptr++)
    sum += *ptr;
    printf("total for items list: %g\n", sum);
    #define Length(in) in ## _len
    sum=0;
    Setup_list(next_set, -1, 2.2, 4.8, 0.1);
    for (int i=0; i < Length(next_set); i++)
    sum += next_set_list[i];
    printf("total for next set list: %g\n", sum);
    
}
