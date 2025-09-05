/* Rosa Knowles
 * 9/5/2025
 * Header for the record release struct
 * Contains function declarations and the record release struct declaration
 */

#ifndef RECORD_RELEASE_H
#define RECORD_RELEASE_H

#include <stdint.h>
#include <stddef.h> // `size_t`

// safe size for "released xx/xx/xxxx" is 19 + 10 for the format specifier + 15 for the linebreaks and line starters + 1 for the null terminating character
// used when calling `rr_string`
#define SAFE_BUFF_BASE 45


/*ENUM DEFINITIONS*/


typedef enum RFORMAT
{
    // enum that stores the format the record was released on 
    VINYL_LP,
    VINYL_EP,
    VINYL_10,
    CD,
    CASSETTE,
    DIGITAL,
    SHELLAC,
    ERR
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


typedef struct rr_node
{
    // struct that stores a node for a doubly linked list of record releases
    record_release data;
    struct rr_node * next;
} rr_node;


/*FUNCTION DECLARATIONS*/

// pseudo-constructors

rdate Create_Date(MONTH month, int8_t day, int16_t year);
record_release Create_Release(RFORMAT format, const char * title, const char * artist, const char * primary_genre, rdate release_date, size_t buff);

// cleanup functions 

void cleanup_release(const record_release * rr);

// functions that work on `record_release`

/* Function that compares where the position in a sorted list of releases a certain release should be.
 * Returns -1 if "less than"
 * Returns 0 if "equal"
 * Returns 1 if "greater than"
 */
int8_t compare_release(const record_release * a, const record_release * b);

// returns a safe size for the string representation of a record release
size_t get_safe_buff(const record_release * rr);
// converts a record release to a string
void rr_string(const record_release * rr, char * buff, size_t buffer_size);

// functions for the linked list of record releases 

void insert_head(rr_node * head, record_release data);
// TODO: Define this function: 
record_release get_record_release(rr_node * head, size_t index);

#endif