#include <stdarg.h>				//提供宏va_list、va_start、va_arg、va_end	
#include <ctype.h> 				//提供isprint原型
#include "sys_tem.h"
#include "ds_extern.h"
#include "linear_list.h"



#ifndef SCANF_C
#define SCANF_C



/*
    自定义的数据录入函数，用于从文件fp
中读取格式化的输入。

    与fscanf不同之处在于此函数只会读取
西文字符，对于中文字符，则会跳过。 
*/

/***
 * 自定以数据录入函数，用于从文件fp中读取格式化的输入
 * 与fscanf的区别是该函数只会读取西文字符，对于中文字符则会进行跳过 
 */
#if 0 
int Scanf(FILE *fp, char *format, ...)
{
	int *i;
	char *ch, *s;
	float *f;
	int count, k, len, n;		
	int tmp;
	va_list ap;
	
	len = strlen(format);
	
	va_start(ap, format);
	
	for(count=0,k=2; k<=len; k=k+2)
	{
		while((tmp=getc(fp))!=EOF)			//跳过所有非西文字符 
		{
			if((tmp>=0 && tmp<=127))
			{
				ungetc(tmp, fp);			//遇到首个西文字符，将此西文字符放入输入流 
				break;
			}
		}
		
		if(tmp==EOF)
			break;
		
		if(format[k-1]=='c')				//读取字符		 
		{
			ch = va_arg(ap, char*);
						
			if(tmp!=EOF)
				count += fscanf(fp, "%c", ch);					
		}	
		
		if(format[k-1]=='d')				//读取整型 
		{
			i = va_arg(ap, int*);
			
			while((tmp=getc(fp))!=EOF)
			{
				if((tmp>='0' && tmp<='9') || tmp=='-' || tmp=='+')
				{
					ungetc(tmp, fp);
					break;
				}
			}
			
			if(tmp!=EOF)
				count += fscanf(fp, "%d", i);
		}

		if(format[k-1]=='f')				//读取浮点型 
		{
			f = va_arg(ap, float*);
			
			while((tmp=getc(fp))!=EOF)
			{
				if((tmp>='0' && tmp<='9') || tmp=='-' || tmp=='+'|| tmp=='.' )
				{
					ungetc(tmp, fp);
					break;
				}
			}
			
			if(tmp!=EOF)
				count += fscanf(fp, "%f", f);
		}
		
		if(format[k-1]=='s')				//读取字符串 
		{
			s = va_arg(ap, char*);
			
			while((tmp=getc(fp))!=EOF && (!isprint(tmp) || tmp==' '))
				;
			
			n = 0;
			if(!feof(fp))
			{
				ungetc(tmp, fp);
				while((tmp=getc(fp))!=EOF)
				{
					if(isprint(tmp) && tmp!=' ')
						s[n++] = tmp;
					else
						break;	
				}
				ungetc(tmp, fp);			
			}
                                                                                
			s[n] = '\0';
					
			count++;		
		}		
	}
		
	va_end(ap);
	
	return count;
}
#endif

#endif 



/**
 * @InitList_Sq
 * @brief 初始化链表
 */
Status InitList_Sq(SqList *L)
{
    L->elem = (LElemType_Sq *)malloc(LIST_INIT_SIZE*sizeof(LElemType_Sq));
    if (! L->elem)
    {
        UNIX_DEBUG("malloc is OVERFLOW .\n");
        exit(OVERFLOW);
    }

    L->length = 0;       //<　初始化顺序链表　长度为０
    L->listsize = LIST_INIT_SIZE;   //< 初始化顺序链表内存分配量

    return OK;
}

/**
 * @ClearList_Sq
 * @brief 清空链表数据
 */
void ClearList_Sq(SqList *L)
{
    L->length = 0;
}

/**
 * @DestroyList_Sq
 * @brief 初始化链表
 */
void DestroyLIst_Sq(SqList *L)
{
    free(L->elem);

    L->elem = NULL;  //< 释放后将指针置为空指针
    L->length = 0;
    L->listsize = 0;
}

Status ListEmpty_Sq(SqList L)
{
    return L.length == 0 ? TRUE : FALSE;
}

int ListLength_Sq(SqList L)
{
    return L.length;
}

Status GetElem_Sq(SqList L, int i, LElemType_Sq *e)
{
    if (i < 1 || i > L.length)
    {
        return ERROR;      ///< i 值不合法
    }
    else
    {   
        *e = L.elem[i-1];
    }



    return OK;
}

