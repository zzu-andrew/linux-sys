#include <stdio.h>
#include <string.h>

#include "../common/pcre-4.4/pcre.h"
#include "../common/util.h"

#include "oracle_date.h"

#define ORACLE_DATE_REGEX "[0-9]{1,2}-[a-zA-Z]{3,3}-[0-9]{2,2}";

static const char* get_date(const char* value);
static int month_num(const char* x);

/* Return month index from oracle name (3-digit uppcase abrev) */
int month_num(const char* x);

int is_valid_oracle_date(const char* value)
{
    const char* x;
    date d;

    x = get_date(value);

    if(x == NULL) {
        return 0;
    }

    oracle_date_str_to_struct(x, &d);

    if(d.month == -1) {
        return 0;
    }

    return 1;
}

const char* get_date(const char* value)
{
    pcre *re;
    const char *error, *pattern;
    int erroffset;
    int ovector[3];
    int value_length;
    int rc, substring_length;
    char* result, *substring_start;

    pattern = ORACLE_DATE_REGEX;

    re = pcre_compile(
        pattern,              /* the pattern */
        0,                    /* default options */
        &error,               /* for error message */
        &erroffset,           /* for error offset */
        NULL);                /* use default character tables */

    /* Compilation failed */
    if (re == NULL) {
        return NULL;
    }

    value_length = (int)strlen(value);

    rc = pcre_exec(
        re,           /* the compiled pattern */
        NULL,         /* no extra data - we didn't study the pattern */
        value,        /* the value string */
        value_length, /* the length of the value */
        0,            /* start at offset 0 in the value */
        0,            /* default options */
        ovector,      /* output vector for substring information */
        3);           /* number of elements in the output vector */

    if (rc < 0) {
        /* Match error */
        return NULL;
    }

    /* Match succeded */
    substring_start = (char*)value + ovector[0];
    substring_length = ovector[1] - ovector[0];

    //printf("%.*s\n", substring_length, substring_start);

    result = malloc(substring_length+1);
    strncpy(result, substring_start, substring_length);
    result[substring_length] = '\0';

    return result;
}

const char* iso_from_oracle_date(const char* value)
{
    const char* date, *tmp;
    char *start, *end, zDay[3], zMonth[4], zYear[3];
    char result[40];
    int day, month, year;

    date = get_date(value);

    if(date == NULL) {
        return NULL;
    }

    /* Find first - */
    start = strchr(date,'-');

    /* Find last - */
    end   = strchr(start+1,'-');

    /* Extract day part, convert to int*/
    strncpy(zDay, date,2);
    zDay[2] = '\0';
    day = atoi(zDay);

    /* Extract month part, convert to int*/
    strncpy(zMonth, start+1,3);
    zMonth[3] = 0;
    tmp = uppercase(zMonth);
    month = month_num(tmp);
    free((void*)tmp);

    /* Extract year part, convert to int*/
    strncpy(zYear, end+1,2);
    zYear[2] = '\0';
    year = atoi(zYear);

    free((void*)date);

    sprintf(result, "20%02i-%02i-%02i", year, month, day);

    return strdup(result);
}

int oracle_date_str_to_struct(const char* value, date* d)
{
    const char* date, *tmp;
    char *start, *end, zDay[3], zMonth[4], zYear[3];

    date = get_date(value);

    if(date == NULL) {
        fprintf(stderr, "Invalid date\n");
        return -1;
    }

    /* Find first '-' */
    start = strchr(date,'-');

    /* Find last '-' */
    end   = strchr(start+1,'-');

    /* Extract day part, convert to int*/
    strncpy(zDay, date,2);
    zDay[2] = '\0';
    d->day = atoi(zDay);

    /* Extract month part, convert to int*/
    strncpy(zMonth, start+1,3);
    zMonth[3] = 0;
    tmp = uppercase(zMonth);
    d->month = month_num(tmp);
    free((void*)tmp);

    /* Extract year part, convert to int*/
    strncpy(zYear, end+1,2);
    zYear[2] = '\0';
    d->year = atoi(zYear);

    free((void*)date);

    return 0;
}

int month_num(const char* x)
{
    if(strncmp(x, "JAN",3) == 0) {
        return 1;
    }

    if(strncmp(x, "FEB",3) == 0) {
        return 2;
    }

    if(strncmp(x, "MAR",3) == 0) {
        return 3;
    }

    if(strncmp(x, "APR",3) == 0) {
        return 4;
    }

    if(strncmp(x, "MAY",3) == 0) {
        return 5;
    }

    if(strncmp(x, "JUN",3) == 0) {
        return 6;
    }

    if(strncmp(x, "JUL",3) == 0) {
        return 7;
    }

    if(strncmp(x, "AUG",3) == 0) {
        return 8;
    }

    if(strncmp(x, "SEP",3) == 0) {
        return 9;
    }

    if(strncmp(x, "OCT",3) == 0) {
        return 10;
    }

    if(strncmp(x, "NOV",3) == 0) {
        return 11;
    }

    if(strncmp(x, "DEC",3) == 0) {
        return 12;
    }

    return -1;
}
