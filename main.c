/* Rosa Knowles
 * 9/9/2025
 * Main!
 * Contains a handful of useful functions, and the actual program itself.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record_release.h"

#define BUFFERSIZE 50

#define TESTING 1

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

void print_list(char * buff, rr_node * list)
{
    // iterates through the list and prints each element

    // print that the list is empty, and return, if it is empty
    if (list == NULL)
    {
        printf(">\n> No elements in list!\n>\n");
        return;
    }

    size_t index = 0;
    // iterate through the linked list using a pointer rather than direct access from an index
    // reduces number of operations needed to print the list
    // code execution ends when the pointer is null, aka when it reaches the end of the list 
    for (rr_node * it = list; it != NULL; it = it->next)
    {
        printf(">\n> [%lld]\n>\n", index + 1);
        print_record_release(buff, &it->data);
        index++;
    }
}

int test_fun()
{
    // function use for testing

    // initialize hardcoded list of record releases 
    rr_node * rr_list = (rr_node *)malloc(sizeof(rr_node));
    rr_list->next = NULL;
    rr_list->data = Create_Release(VINYL_LP, "Selected Ambient Works 85-92", "Aphex Twin", "Electronic", Create_Date(NOV, 9, 1992), BUFFERSIZE);
    insert_head(&rr_list, Create_Release(VINYL_LP, "Untrue", "Burial", "Electronic", Create_Date(NOV, 5, 2007), BUFFERSIZE));
    insert_head(&rr_list, Create_Release(VINYL_LP, "Brat", "Charli XCX", "Electronic", Create_Date(JUN, 7, 2024), BUFFERSIZE));
    insert_head(&rr_list, Create_Release(VINYL_LP, "Fossora", "Bjork", "Electronic", Create_Date(SEP, 30, 2022), BUFFERSIZE));
    insert_head(&rr_list, Create_Release(VINYL_LP, "Cheetah EP", "Aphex Twin", "Electronic", Create_Date(JUL, 8, 2016), BUFFERSIZE));
    insert_head(&rr_list, Create_Release(VINYL_LP, "Crystal Castles", "Crystal Castles", "Electronic", Create_Date(MAR, 18, 2008), BUFFERSIZE));

    char * str_rep = NULL;

    print_list(str_rep, rr_list);

    rr_list = mergesort(rr_list);
    print_list(str_rep, rr_list);

    rm_element(&rr_list, 0);
    rm_element(&rr_list, 3);
    print_list(str_rep, rr_list);

    cleanup_list(&rr_list);
    print_list(str_rep, rr_list);

    return 0;
}


int main(int argc, char ** argv)
{
    // only runs the test code if the program is in testing mode
    if (TESTING)
        return test_fun();


    // initialize list and list size
    rr_node * rr_list = (rr_node *)malloc(sizeof(rr_node));
    size_t len = 0;

    free(rr_list);

    printf("test\n");

    return 0;
}