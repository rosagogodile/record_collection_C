/* Rosa Knowles
 * 9/5/2025
 * Definitions for functions contained in `record_release.h`
 */

#include "record_release.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h> // for `sprintf`

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
    // if the month is not in the range of accepted values, set the release month to january
    // otherwise, set the release month to the input
    temp.r_month = (temp.r_year > -1 && month >= JAN && month <= DEC) ? month : JAN;

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

void cleanup_release(const record_release * rr)
{
    // function to free the memory associated with the strings stored in a record release struct
    free(rr->title);
    free(rr->artist);
    free(rr->primary_genre);
}

int8_t compare_release(const record_release * a, const record_release * b)
{
    /* Function that compares where the position in a sorted list of releases a certain release should be.
    * Returns -1 if "less than"
    * Returns 0 if "equal"
    * Returns 1 if "greater than"
    */
 
    // by format
    // if the formats of a and b are different, check where they should be placed in comparison to each other.
    if (a->format != b->format)
        return (a->format < b->format) ? -1 : 1;
    

    int8_t temp_bool = 0;

    // by genre
    // strcmp tuide -> https://www.geeksforgeeks.org/c/strcmp-in-c/
    temp_bool = strcmp(a->primary_genre, b->primary_genre);
    if (temp_bool != 0)
        return (temp_bool < 0) ? -1 : 1;

    // by artist
    temp_bool = strcmp(a->artist, b->artist);
    if (temp_bool != 0)
        return (temp_bool < 0) ? -1 : 1;

    // compare dates
    // check year first, then month, then day
    // if the dates are the exact same, nothing is returned in this section
    if (a->release_date.r_year != b->release_date.r_year)
        return (a->release_date.r_year < b->release_date.r_year) ? -1 : 1;
    else if (a->release_date.r_month != b->release_date.r_month)
        return (a->release_date.r_month < b->release_date.r_month) ? -1 : 1;
    else if (a->release_date.r_day != b->release_date.r_day)
        return (a->release_date.r_day < b->release_date.r_day) ? -1 : 1;


    // by title
    temp_bool = strcmp(a->title, b->title);
    if (temp_bool != 0)
        return (temp_bool < 0) ? -1 : 1;

    // if the record releases are the exact same, return 0 :)
    return 0;
}


size_t get_safe_buff(const record_release * rr)
{
    // returns a safe size for the record release

    // check `record_release.h` for a comment explaining why this constant is used
    size_t safe_buff = SAFE_BUFF_BASE;

    // add on the lengths of the other strings we need to shove inside of the string
    safe_buff += strlen(rr->artist);
    safe_buff += strlen(rr->primary_genre);
    safe_buff += strlen(rr->title);

    return safe_buff;
}


void rr_string(const record_release * rr, char * buff, size_t buffer_size)
{
    // converts `rr` into a string representation of itself
    // copies the string into `buff` 

    /* In the form:

        "> {title}
         > {artist}
         > {primary_genre}
         > Released xx/xx/xxxx
         > {format converted to str}"

     */


    size_t safe_buff = get_safe_buff(rr);


    // if string can't be safely copied, exit function
    if (buffer_size < safe_buff)
        return;

    char * temp = (char *)malloc(safe_buff * sizeof(char));
    
    // formats the string up until the format, which will be handled by a switch case
    sprintf(temp, "> %s\n> %s\n> %s\n> Released %i/%i/%i\n> ", 
        rr->title, rr->artist, rr->primary_genre, rr->release_date.r_month, rr->release_date.r_day, rr->release_date.r_year);

    switch (rr->format)
    {
        case VINYL_LP:
            strcat(temp, "12\" Record");
            break;
        case VINYL_EP:
            strcat(temp, "7\" Record");
            break;
        case VINYL_10:
            strcat(temp, "10\" Record");
            break;
        case CD:
            strcat(temp, "CD");
            break;
        case CASSETTE:
            strcat(temp, "Cassette");
            break;
        case DIGITAL:
            strcat(temp, "Digital");
            break;
        case SHELLAC:
            strcat(temp, "Shellac");
            break;
        default:
            strcat(temp, "unknown");
    }

    strcpy(buff, temp);

    free(temp);
}


void insert_head(rr_node ** head, record_release data)
{
    // inserts a new node at the head of a list
    // uses a double pointer to prevent a segfault

    rr_node * new_head = (rr_node *)malloc(sizeof(rr_node));

    new_head->data = data;
    new_head->next = *head;

    *head = new_head;
}

record_release get_record_release(rr_node * head, size_t index)
{
    // returns the record release at a specified index of a linked list
    // not safe!!!!! making sure the index isn't out of range should be managed outside of this function

    rr_node * current = head;

    // list is 0-indexed
    // navigate to the node at the specified index
    for (size_t it = 0; it < index; ++it)
    {
        current = current->next;
    }

    return current->data;
}



/* MERGESORT FUNCTIONS */

/* Mergesort pseudocode:

    Split the list in half:
        Pass in the length of the list 
        Calculate midpoint 
        Use these indexes to split the list in half

    Call mergesort on both halves:
        - Recursion!

    Merge the two linked lists after everything:
        - Within this merge function, sort the elements of the linked list recursively.

 */

// https://www.geeksforgeeks.org/dsa/merge-sort-for-linked-list/

static rr_node * split_(rr_node ** head, size_t midpoint)
{
    // function to split a list in half

    // iterate to the midpoint
    rr_node * current = *head;
    for (size_t it = 0; it < midpoint - 1; ++it)
    {
        current = current->next;
    }

    rr_node * temp = current->next;
    current->next = NULL;
    return temp;
}

static rr_node * merge_(rr_node * a, rr_node * b)
{
    // return a or b if the other list is empty 
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    // recursively merges list while sorting the data using the `compare_release` function
    if (compare_release(&a->data, &b->data) <= 0) // release should be placed before
    {
        a->next = merge_(a->next, b);
        return a;
    }
    else // release should be placed after 
    {
        b->next = merge_(a, b->next);
        return b;
    }
}

rr_node * mergesort(rr_node ** head, size_t len)
{
    // if the list is empty or has one node, return the list b/c it's already sorted
    if (len <= 1)
        return *head;

    size_t midpoint = len / 2;

    rr_node * second_list = split_(head, midpoint);

    mergesort(head, midpoint);
    // if the list length is odd, adds one to the mergesort length
    mergesort(&second_list, midpoint + (len % 2));

    return merge_(head, second_list);
}