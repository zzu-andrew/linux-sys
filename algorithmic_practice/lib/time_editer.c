#include "time_editer.h"
#include <time.h>
#include <locale.h>
#include <sys/time.h>



/***
 * 宏定义区域 
 */
#define BUFF_SIZE 200

/***
 * @brief 时间函数测试接口
 * @input void
 * @return SUCESS OK
 *         FAIL ERROR
 */

int show_time(void)
{
    int ret = OK;
    printf("----------------------line of time show---------------------------------\n");
    ret |= gmtime_show();
    ret |= localtime_show();
    ret |= strftime_show();
    ret |= ctime_show();
    ret |= asctime_show();



    printf("----------------------line of time show---------------------------------\n");


    return ret;

}


/*
 * 获取UTC时间
+------+      time_t-->struct tm        +--------+
| time | -----------------------------> | gmtime |
+------+                                +--------+
 */

int gmtime_show(void)
{
    time_t t;
    struct tm *gmp, gm;


    t = time(NULL);
    gmp = gmtime(&t);

    gm = *gmp;

    UNIX_DEBUG("gmtime UTC hour  = [%d], min = [%d], sec = [%d]\n"\
               "year = [%d], mon = [%d], day = [%d]\n", 
                gm.tm_hour, gm.tm_min, gm.tm_sec, gm.tm_year, gm.tm_mon, gm.tm_mday);
    return OK; 
}

/*** get local time
+------+      time_t-->struct tm        +-----------+
| time | -----------------------------> | localtime |
+------+                                +-----------+
*/
int localtime_show(void)
{
    time_t t;
    struct tm *lmp, lm;


    t = time(NULL);
    lmp = localtime(&t);
    if (NULL == lmp)
    {
        UNIX_DEBUG("local time is NULL.\n");
    }

    //< 防止获取出的全局时间变量被更改，
    lm = *lmp;

    UNIX_DEBUG("local time hour = [%d], min = [%d], sec = [%d]\n"\
               "year = [%d], mon = [%d], day = [%d]\n", 
                lm.tm_hour, lm.tm_min, lm.tm_sec, lm.tm_year, lm.tm_mon, lm.tm_mday);
    return OK; 
}



/*
       %a     The abbreviated name of the day of the week according to the current locale.

       %A     The full name of the day of the week according to the current locale.

       %b     The abbreviated month name according to the current locale.

       %B     The full month name according to the current locale.

       %c     The preferred date and time representation for the current locale.

       %C     The century number (year/100) as a 2-digit integer. (SU)

       %d     The day of the month as a decimal number (range 01 to 31).

       %D     Equivalent to %m/%d/%y.  (Yecch—for Americans only.  Americans should note that  in  other
              countries %d/%m/%y is rather common.  This means that in international context this format
              is ambiguous and should not be used.) (SU)

       %e     Like %d, the day of the month as a decimal number, but a leading zero  is  replaced  by  a
              space. (SU)

       %E     Modifier: use alternative format, see below. (SU)

       %F     Equivalent to %Y-%m-%d (the ISO 8601 date format). (C99)

       %G     The  ISO 8601  week-based  year (see NOTES) with century as a decimal number.  The 4-digit
              year corresponding to the ISO week number (see %V).  This has the same format and value as
              %Y,  except that if the ISO week number belongs to the previous or next year, that year is
              used instead. (TZ)

       %g     Like %G, but without century, that is, with a 2-digit year (00-99). (TZ)

       %h     Equivalent to %b.  (SU)

       %H     The hour as a decimal number using a 24-hour clock (range 00 to 23).

       %I     The hour as a decimal number using a 12-hour clock (range 01 to 12).

       %j     The day of the year as a decimal number (range 001 to 366).

       %k     The hour (24-hour clock) as a decimal number (range 0 to 23); single digits  are  preceded
              by a blank.  (See also %H.)  (TZ)

       %l     The  hour  (12-hour clock) as a decimal number (range 1 to 12); single digits are preceded
              by a blank.  (See also %I.)  (TZ)

       %m     The month as a decimal number (range 01 to 12).

       %M     The minute as a decimal number (range 00 to 59).

       %n     A newline character. (SU)

       %O     Modifier: use alternative format, see below. (SU)

       %p     Either "AM" or "PM" according to the given time value, or the  corresponding  strings  for
              the current locale.  Noon is treated as "PM" and midnight as "AM".

       %P     Like  %p  but in lowercase: "am" or "pm" or a corresponding string for the current locale.
              (GNU)

       %r     The time in a.m. or p.m. notation.  In the POSIX locale this is equivalent to %I:%M:%S %p.
              (SU)

       %R     The  time  in  24-hour notation (%H:%M).  (SU) For a version including the seconds, see %T
              below.

       %s     The number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC). (TZ)

       %S     The second as a decimal number (range 00 to 60).  (The range is up  to  60  to  allow  for
              occasional leap seconds.)

        %t     A tab character. (SU)

       %T     The time in 24-hour notation (%H:%M:%S).  (SU)

       %u     The day of the week as a decimal, range 1 to 7, Monday being 1.  See also %w.  (SU)

       %U     The week number of the current year as a decimal number, range 00 to 53, starting with the
              first Sunday as the first day of week 01.  See also %V and %W.

       %V     The ISO 8601 week number (see NOTES) of the current year as a decimal number, range 01  to
              53,  where week 1 is the first week that has at least 4 days in the new year.  See also %U
              and %W.  (SU)

       %w     The day of the week as a decimal, range 0 to 6, Sunday being 0.  See also %u.

       %W     The week number of the current year as a decimal number, range 00 to 53, starting with the
              first Monday as the first day of week 01.

       %x     The preferred date representation for the current locale without the time.

       %X     The preferred time representation for the current locale without the date.

       %y     The year as a decimal number without a century (range 00 to 99).

       %Y     The year as a decimal number including the century.

       %z     The +hhmm or -hhmm numeric timezone (that is, the hour and minute offset from UTC). (SU)

       %Z     The timezone name or abbreviation.

       %+     The date and time in date(1) format. (TZ) (Not supported in glibc2.)
 */

/*
+------+      time_t-->struct tm        +-----------+      struct tm-->formit tm to string        +----------+
| time | -----------------------------> | localtime | ------------------------------------------> | strftime |
+------+                                +-----------+                                             +----------+
 */
 /**
  * @brief   strftime　根据不同的formit生成不同的时间格式的字符串
  * @note    
  * @retval SUCCESS:OK
  *         FAILED: ERROR
  */
int strftime_show(void)
{
    time_t t;
    struct tm *lmp;
    char buf[BUFF_SIZE];
    size_t s;

    t = time(NULL);
    lmp = localtime(&t);
    if (NULL == lmp)
    {
        UNIX_DEBUG("local time is NULL.\n");
    }
    //< %c     The preferred date and time representation for the current locale.
    memset(buf, 0, sizeof(buf));
    s = strftime(buf, BUFF_SIZE, "%c", lmp);
    if (0 == s)
    {   
        UNIX_DEBUG("strftime is failed.\n");
    }
    UNIX_DEBUG("strftime = %s\n", buf);

    return OK; 
}


int ctime_show(void)
{
    time_t t;

    t = time(NULL);

    UNIX_DEBUG("ctime = %s\n", ctime(&t));
    return OK; 
}


int asctime_show(void)
{
    time_t t;
    struct tm *loc;
   

    t = time(NULL);

    loc = localtime(&t);
    UNIX_DEBUG("asctime od local time is  %s\n", asctime(loc));
    return OK; 
}


