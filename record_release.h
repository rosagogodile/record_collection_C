/* Rosa Knowles
 * 9/2/2025
 * Header for the record release struct
 * Contains function declarations and the record release struct declaration
 */

#ifndef RECORD_RELEASE_H
#define RECORD_RELEASE_H

#include <stdint.h>


/*ENUM DEFINITIONS*/


typedef enum RFORMAT
{
    // enum that stores the format the record was released on 
    VINYL_LP,
    VINYL_EP,
    CD,
    CASSETTE,
    DIGITAL,
    SHELLAC
} RFORMAT;


typedef enum MONTH
{
    // enum that stores the month
    // used for date struct
    JAN = 1,
    FEB,
    MAR,
    APR,
    MAY,
    JUN,
    JUL,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC
} MONTH;


/*STRUCT DEFINITIONS*/


typedef struct rdate
{
    // struct that stores a date
    MONTH r_month;
    int8_t r_day;
    int16_t r_year;
} rdate;


typedef struct record_release
{
    // struct that stores information about a record release

    /* `format` stores the format of the release
     * `title` stores the title of the release
     * `artist` stores the artist(s) of the release
     * `primary_genre` stores the primary genre of the release
     * `release_date` stores the release date of the release
     */

    RFORMAT format;

    char * title;
    char * artist;
    char * primary_genre;

    rdate release_date;
} record_release;


/*FUNCTION DECLARATIONS*/

// pseudo-constructors

rdate Create_Date(MONTH month, int8_t day, int16_t year);
record_release Create_Release(RFORMAT format, const char * title, const char * artist, const char * primary_genre, rdate release_date, size_t buff);

#endif