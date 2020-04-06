/*********************
 *                   *
 * �1�7�0�4�1�7�1�7�1�7: �1�7�1�701 �1�7�1�7�1�7�1�7 *
 *                   *
 * �1�7�0�4�1�7�1�7�1�7: Scanf.c   *
 *                   *
 *********************/

#ifndef SCANF_C
#define SCANF_C

#include <stdio.h>
#include <string.h>
#include <stdarg.h>				//�1�7�5�9�1�7�1�7va_list�1�7�1�7va_start�1�7�1�7va_arg�1�7�1�7va_end	
#include <ctype.h> 				//�1�7�5�9isprint�0�9�1�7�1�7 

/*
    �1�7�0�8�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�4�1�7�1�8�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�0�1�7�1�7�0�4�1�7fp
�1�7�؄1�7�0�0�1�7�1�7�0�4�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�6

    �1�7�1�7fscanf�1�7�1�7�0�4�0�8�1�7�1�7�1�7�1�7�1�7�1�0�0�0�1�7�1�7�1�7�0�1�1�7�1�7�1�7�0�0
�1�7�1�7�1�7�1�7�1�7�0�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7 
*/

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
		while((tmp=getc(fp))!=EOF)			//�1�7�1�7�1�7�1�7�1�7�1�7�1�7�ل1�7�1�7�1�7�1�7�1�7�1�7�0�7�1�7 
		{
			if((tmp>=0 && tmp<=127))
			{
				ungetc(tmp, fp);			//�1�7�1�7�1�7�1�7�1�7�0�2�1�7�1�7�1�7�1�7�1�7�1�7�0�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7 
				break;
			}
		}
		
		if(tmp==EOF)
			break;
		
		if(format[k-1]=='c')				//�1�7�1�7�0�0�1�7�0�7�1�7		 
		{
			ch = va_arg(ap, char*);
						
			if(tmp!=EOF)
				count += fscanf(fp, "%c", ch);					
		}	
		
		if(format[k-1]=='d')				//�1�7�1�7�0�0�1�7�1�7�1�7�1�7 
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

		if(format[k-1]=='f')				//�1�7�1�7�0�0�1�7�1�7�1�7�1�7�1�7�1�7 
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
		
		if(format[k-1]=='s')				//�1�7�1�7�0�0�1�7�0�7�1�7�1�7�1�7 
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
