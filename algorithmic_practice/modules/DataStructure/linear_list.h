#ifndef __LINEAR_LIST__
#define __LINEAR_LIST__
#include <stdio.h>
#include <stdarg.h>				//提供宏va_list、va_start、va_arg、va_end	
#include <ctype.h> 				//提供isprint原型

#if 0
int Scanf(FILE *fp, char *format, ...);

#endif

/* 宏定义 */
#define LIST_INIT_SIZE 100				//顺序表存储空间的初始分配量 
#define LISTINCREMENT  10				//顺序表存储空间的分配增量

/* 顺序表类型定义 */
#ifndef LELEMTYPE_SQ
#define LELEMTYPE_SQ
typedef int LElemType_Sq;  //定义成类型方便后期的更改
#endif

typedef struct 
{
    /* data */
    LElemType_Sq *elem;    //< 存储空间基地址
    int length;            //< 当前输出表长度
    int listsize;          //< 当前分配的存储容量
}SqList;





#endif ///< __LINEAR_LIST__
