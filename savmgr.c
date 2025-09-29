/* Rosa Knowles
 * 9/29/2025
 * Definitions for functions contained in `savmgr.h`
 */

#include "savmgr.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
    temp[3] =  (uint8_t)(0x000000FF & rr->release_date.r_year);
    temp[4] = (uint8_t)((0x0000FF00 & rr->release_date.r_year) >> 8);
    
    

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

// #define READ_FORMAT 1
// #define READ_MONTH 2
// #define READ_DAY 3
// #define READ_YEAR 4
// #define READ_TITLE 5
// #define READ_ARTIST 6
// #define READ_GENRE 7 


static void read_str(FILE * fileptr, char ** str_arr, size_t str_idx)
{
    // reads a single null-terminated string from a file
    uint8_t c = 1;

    size_t idx = 0;

    // get byte from file, and move the file pointer by one byte
    while ((c = getc(fileptr)) != EOF)
    {
        // store the byte in the string 
        str_arr[str_idx][idx] = c;
        idx++;

        // if the end of string has been reached, end the loop
        if (c == 0)
            break;
    }
}


int64_t read_bytearr_file(rr_node ** head, char * filepath, size_t strbuffsize)
{
    // reads a file filled with bytes and converts it to a linked list of record releases 
    // returns `FILE_READ_FAILURE` when there is an error, and the number of elements when file is successfully read

    // TODO: implement a version of `fread` that returns an error if the file isn't the proper size

    FILE * save_file = fopen(filepath, "rb");

    // return an error code if the file fails to open
    if (save_file == NULL)
    {
        return FILE_READ_FAILURE;
    }

    // find the length of the file and store it 
    // fseek(save_file, 0L, SEEK_END);
    // size_t file_len = ftell(save_file);
    // rewind(save_file);

    // the number of elements in the linked list of record releases
    size_t num_elements = 0;
    // the size of the variable of the number of elements
    uint8_t num_elements_size = 0;
    fread(&num_elements_size, sizeof(uint8_t), 1, save_file);
    fread(&num_elements, num_elements_size, 1, save_file);

    for (size_t i = 0; i < num_elements; ++i)
    {   
        record_release temp;

        char temp_title[strbuffsize];
        char temp_artist[strbuffsize];
        char temp_genre[strbuffsize];

        int8_t temp_format;

        int8_t temp_month;
        int8_t temp_day;
        int16_t temp_year;

        // read and store format, month, day, and year
        fread(&temp_format, sizeof(int8_t), 1, save_file);
        fread(&temp_month, sizeof(int8_t), 1, save_file);
        fread(&temp_day, sizeof(int8_t), 1, save_file);
        fread(&temp_year, sizeof(int16_t), 1, save_file);

        char * temp_str_arr[] = {temp_title, temp_artist, temp_genre};

        for (int j = 0; j < 3; ++j)
        {
            read_str(save_file, temp_str_arr, j);
        }

        // create a new record release from each of the temporary variables
        temp = Create_Release(temp_format, temp_title, temp_artist, temp_genre, Create_Date(temp_month, temp_day, temp_year), strbuffsize);

        // add element to the linked list :)
        if (i == 0)
        {
            rr_node * temp_ptr = *head;
            temp_ptr->data = temp;
        }
        else 
        {
            insert_head(head, temp);
        }
    }

    fclose(save_file);

    // return the number of elements in the list
    return num_elements;
}