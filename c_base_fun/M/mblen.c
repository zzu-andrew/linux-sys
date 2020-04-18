#include "c-base.h"
#include <stdlib.h>
#include <string.h>

int main()
{
   int len;
   char *pmb = (char *)malloc( MB_CUR_MAX );
   wchar_t *pwc = L"Hi";
   wchar_t *pwcs = (wchar_t *)malloc( sizeof( wchar_t ));

   printf("转换为多字节字符串\n");
   len = wcstombs( pmb, pwc, MB_CUR_MAX);
   printf("被转换的字符 %d\n", len);
   printf("第一个多字节字符的十六进制值：%#.4x\n", pmb);
   
   len = mblen( pmb, MB_CUR_MAX );
   printf( "多字节字符 %s 的字节长度：%u\n", pmb, len );
   
   pmb = NULL;
   
   len = mblen( pmb, MB_CUR_MAX );
   printf( "多字节字符 %x 的字节长度：%u\n", pmb, len );
   
   return(0);
}
