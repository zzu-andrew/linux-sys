#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <string.h>

#if 0
struct tm
{
  int tm_sec;			/* Seconds.	[0-60] (1 leap second) */
  int tm_min;			/* Minutes.	[0-59] */
  int tm_hour;			/* Hours.	[0-23] */
  int tm_mday;			/* Day.		[1-31] */
  int tm_mon;			/* Month.	[0-11] */
  int tm_year;			/* Year	- 1900.  */
  int tm_wday;			/* Day of week.	[0-6] */
  int tm_yday;			/* Days in year.[0-365]	*/
  int tm_isdst;			/* DST.		[-1/0/1]*/


  long int __tm_gmtoff;		
  const char *__tm_zone;	
};
#endif


int main(int argc, char const *argv[])
{
    //定义时间结构体指针,结构体值见注释
    struct tm *pTm = NULL;
    time_t nowTime;
    char *pSzAscTime = NULL;

    memset(&nowTime, 0 , sizeof(nowTime));

    nowTime = time(NULL);
    pTm = localtime(&nowTime);

    pSzAscTime = asctime(pTm);

    printf("Asc time = %s", pSzAscTime);

    return 0;
}
