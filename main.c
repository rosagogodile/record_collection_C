/* Rosa Knowles
 * 9/5/2025
 * Main!
 * Contains a handful of useful functions, and the actual program itself.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record_release.h"

#define BUFFERSIZE 50

void print_record_release(char * buff, const record_release * rr)
{
    /* Get safe buffer size
     * Allocate memory for the string according to the safe memory size
     * Copy the string representation into newly allocated memory
     * Print the string rep with a linebreak at the end
     * Free the allocated memory
     */

    size_t safe_buff = get_safe_buff(rr);
    buff = (char *)malloc(sizeof(char) * safe_buff);
    rr_string(rr, buff, safe_buff);
    printf("%s\n", buff);
    free(buff);
}


int main(int argc, char ** argv)
{
    // initialize hardcoded list of record releases 
    rr_node * rr_list = (rr_node *)malloc(sizeof(rr_node));
    rr_list->next = NULL;
    rr_list->data = Create_Release(VINYL_LP, "Selected Ambient Works 85-92", "Aphex Twin", "Electronic", Create_Date(NOV, 9, 1992), BUFFERSIZE);
    insert_head(&rr_list, Create_Release(VINYL_LP, "Untrue", "Burial", "Electronic", Create_Date(NOV, 5, 2007), BUFFERSIZE));
    insert_head(&rr_list, Create_Release(VINYL_LP, "Brat", "Charli XCX", "Electronic", Create_Date(JUN, 7, 2024), BUFFERSIZE));
    insert_head(&rr_list, Create_Release(VINYL_LP, "Fossora", "Bjork", "Electronic", Create_Date(SEP, 30, 2022), BUFFERSIZE));
    insert_head(&rr_list, Create_Release(VINYL_LP, "Cheetah EP", "Aphex Twin", "Electronic", Create_Date(JUL, 8, 2016), BUFFERSIZE));
    insert_head(&rr_list, Create_Release(VINYL_LP, "Crystal Castles", "Crystal Castles", "Electronic", Create_Date(MAR, 18, 2008), BUFFERSIZE));

    // length is 6
    size_t list_len = 6;

    char * str_rep = NULL;

    for (size_t i = 0; i < list_len; ++i)
    {
        record_release temp = get_record_release(rr_list, i);
        print_record_release(str_rep, &temp);
        printf(">\n");
    }

    printf(">\n>\n>--------------\n");

    rr_list = mergesort(rr_list);

    for (size_t i = 0; i < list_len; ++i)
    {
        record_release temp = get_record_release(rr_list, i);
        print_record_release(str_rep, &temp);
        printf(">\n");
    }

    return 0;
}