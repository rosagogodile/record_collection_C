/* Rosa Knowles
 * 9/22/2025
 * Definitions for functions contained in `savmgr.h`
 */

#include "savmgr.h"
#include <stdlib.h>
#include <string.h>

size_t get_bytearr_rep(uint8_t ** byte_array, const record_release * rr)
{
    // sets up an array of bytes that represent a record_release
    // returns the size of the array

    // store the length of the strings up until the null terminator
    // used to allocate memory and iterate through the strings
    size_t title_len = strlen(rr->title) + 1;
    size_t artist_len = strlen(rr->artist) + 1;
    size_t genre_len = strlen(rr->primary_genre) + 1;

    // allocates an exact number of bytes represented by the record release in memory
    // note: MONTH, uint8_t, and int16_t are all types used inside of the date struct
    // future size optimizations could reduce the size allocated for RFORMAT and MONTH
    size_t arr_size = ((title_len + artist_len + genre_len) * sizeof(uint8_t)) + (5 * sizeof(uint8_t));
    uint8_t * temp = (uint8_t *)malloc(arr_size);;


    /* Byte allocation guide:
     * 1st byte -> format
     * 2nd byte -> month
     * 3rd byte -> day
     * 4th and 5th byte -> year
     * The next 3 * `strbuffsize` bytes: title, artist, primary_genre
     */

    // format
    temp[0] =  (uint8_t)(0x000000FF & rr->format);
    // month
    temp[1] =  (uint8_t)(0x000000FF & rr->release_date.r_month);

    // day
    temp[2] = rr->release_date.r_day;

    // year
    temp[3] = (uint8_t)((0x0000FF00 & rr->release_date.r_year) >> 8);
    temp[4] =  (uint8_t)(0x000000FF & rr->release_date.r_year);
    

    // the first index of the first string
    size_t idx = 5;


    // title
    for (size_t i = 0; i < title_len; ++i)
    {
        temp[idx + i] = rr->title[i];
    }
    idx += title_len;

    // artist
    for (size_t i = 0; i < artist_len; ++i)
    {
        temp[idx + i] = rr->artist[i];
    }
    idx += artist_len;

    // genre
    for (size_t i = 0; i < genre_len; ++i)
    {
        temp[idx + i] = rr->primary_genre[i];
    }
    // idx += genre_len;

    *byte_array = temp;

    // return the size of the malloced array
    return arr_size;
}