/* Rosa Knowles
 * 9/16/2025
 * Definitions for functions contained in `savmgr.h`
 */

#include "savmgr.h"
#include <stdlib.h>

size_t get_bytearr_rep(uint8_t ** byte_array, const record_release * rr, size_t strbuffsize)
{
    // sets up an array of bytes that represent a record_release
    // returns the size of the array

    // allocates an exact number of bytes represented by the record release in memory
    // note: MONTH, uint8_t, and int16_t are all types used inside of the date struct
    // future size optimizations could reduce the size allocated for RFORMAT and MONTH
    size_t arr_size = (3 * strbuffsize * sizeof(char)) + sizeof(RFORMAT) + sizeof(MONTH) + sizeof(int8_t) + sizeof(int16_t);
    uint8_t * temp = (uint8_t *)malloc(arr_size);;


    /* Byte allocation guide:
     * First 4 bytes: month
     * 5th byte: day
     * 6th and 7th byte: year
     * 8th - 10th byte: format
     * The next 3 * `strbuffsize` bytes: title, artist, primary_genre
     */

    // month
    temp[0] =  (uint8_t)(0x000000FF & rr->format);
    temp[1] =  (uint8_t)(0x000000FF & rr->release_date.r_month);

    // day
    temp[2] = rr->release_date.r_day;

    // year
    temp[3] = (uint8_t)((0x0000FF00 & rr->release_date.r_year) >> 8);
    temp[4] =  (uint8_t)(0x000000FF & rr->release_date.r_year);

    // format
    temp[5] = (uint8_t)((0xFF000000 & rr->format) >> 24);
    temp[6] = (uint8_t)((0x00FF0000 & rr->format) >> 16);
    temp[7] = (uint8_t)((0x0000FF00 & rr->format) >> 8);
    

    // the first index of the first string
    size_t idx = 11;


    // title
    for (size_t i = 0; i < strbuffsize; ++i)
    {
        temp[idx + i] = rr->title[i];
    }
    idx += strbuffsize;

    // artist
    for (size_t i = 0; i < strbuffsize; ++i)
    {
        temp[idx + i] = rr->artist[i];
    }
    idx += strbuffsize;

    // genre
    for (size_t i = 0; i < strbuffsize; ++i)
    {
        temp[idx + i] = rr->primary_genre[i];
    }
    // idx += strbuffsize;

    *byte_array = temp;

    // return the size of the malloced array
    return arr_size;
}