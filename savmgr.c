#include "savmgr.h"

size_t get_bytearr_rep(int8_t ** byte_array, const record_release * rr, size_t strbuffsize)
{
    // sets up an array of bytes that represent a record_release
    // returns the size of the array

    // allocates an exact number of bytes represented by the record release in memory
    // note: MONTH, int8_t, and int16_t are all types used inside of the date struct
    // future size optimizations could reduce the size allocated for RFORMAT and MONTH
    size_t arr_size = (3 * strbuffsize) + sizeof(RFORMAT) + sizeof(MONTH) + sizeof(int8_t) + sizeof(int16_t);
    *byte_array = (int8_t *)malloc(arr_size);


    /* Byte allocation guide:
     * First 4 bytes: month
     * 5th byte: day
     * 6th and 7th byte: year
     * The next 3 * `strbuffsize` bytes: title, artist, primary_genre
     */

    // month
    byte_array[0] = (int8_t)((0xFF000000 & rr->release_date.r_month) >> 24);
    byte_array[1] = (int8_t)((0x00FF0000 & rr->release_date.r_month) >> 16);
    byte_array[2] = (int8_t)((0x0000FF00 & rr->release_date.r_month) >> 8);
    byte_array[3] =  (int8_t)(0x000000FF & rr->release_date.r_month);

    // day
    byte_array[4] = rr->release_date.r_day;

    // year
    byte_array[5] = (int8_t)((0x0000FF00 & rr->release_date.r_year) >> 8);
    byte_array[6] =  (int8_t)(0x000000FF & rr->release_date.r_year);

    return arr_size;
}