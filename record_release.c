#include "record_release.h"

#include <stdlib.h>
#include <string.h>

rdate Create_Date(MONTH month, int8_t day, int16_t year)
{
    // function that initializes a date struct
    rdate temp;

    temp.r_year = (year > 0) ? year : -1;

    // validate day
    // if day is within valid range, set the day to the input. otherwise, set it to -1
    if (month == FEB)
    {
        // checks if the current year is a leap year using a ternary operator
        uint8_t is_leap_year = (year % 100 == 0 && year % 400 == 0) ? 1 : (year % 4 == 0);
        temp.r_day = (day <= 28 + is_leap_year && day > 0) ? day : -1;
    }
    else
    {
        // checks if the month has 30 days in it
        uint8_t is_30_days = (month == APR) || (month == JUN) || (month == SEP) || (month == NOV);
        temp.r_day = (day <= 31 - is_30_days && day > 0) ? day : -1;
    }

    // if the year is unknown, set the release month to january
    // otherwise, set the release month to the input
    temp.r_month = (temp.r_year > -1) ? month : JAN;

    return temp;
}


record_release Create_Release(RFORMAT format, const char * title, const char * artist, const char * primary_genre, rdate release_date, size_t buff)
{
    // function that initializes a release struct
    record_release temp;
    temp.release_date = release_date;
    temp.format = format;


    // allocate memory for the strings
    size_t malloc_size = sizeof(char) * buff;

    temp.title         = (char *)malloc(malloc_size);
    temp.artist        = (char *)malloc(malloc_size);
    temp.primary_genre = (char *)malloc(malloc_size);

    // copy inputs into the newly-allocated memory
    strcpy(temp.title, title);
    strcpy(temp.artist, artist);
    strcpy(temp.primary_genre, primary_genre);

    return temp;
}