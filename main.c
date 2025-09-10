/* Rosa Knowles
 * 9/10/2025
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




#define TESTING_LIST 0
#define TESTING_SUBSTRING 0

/*-----TEST FUNCTIONS-----*/
// these functions entirely exist for me to experiment with/test other functions :)
// they are only run if the corresponding define is set to 1

int test_fun()
{
    // corresponding define: `TESTING_LIST`
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

int test_substring()
{
    // corresponding define: `TESTING_SUBSTRING`
    // tests pointer math with the `strstr` function for finding substrings
    char a[] = "this is a test";

    char * c = strstr(a, "a");

    printf("%d\n%s\n%d\n%d\n%d", c == NULL, c, c, a, c-a);
    return 0;
}

/*--------------------------------------------------------------------------------*/





int main(int argc, char ** argv)
{
    // only runs the test code if any of the test definitions are set to 1
    if (TESTING_LIST)
        return test_fun();
    else if (TESTING_SUBSTRING)
        return test_substring();


    // initialize list and list size
    rr_node * rr_list = (rr_node *)malloc(sizeof(rr_node));
    size_t len = 0;

    // initialize a character buffer that will be used to print list contents
    char * buff = NULL;

    // setup loop variables 
    int8_t prog_loop = 1;
    // string that will store user input
    char user_input[BUFFERSIZE];

    // print welcome message 
    printf("> Welcome to Rosa's Record Organizer!\n");

    while (prog_loop)
    {
        printf("> ");


        // GET USER INPUT

        // note: `sizeof(user_input)` SHOULD equal `BUFFERSIZE`
        fgets(user_input, sizeof(user_input), stdin);

        // if input buffer overflowed, flush it
        // else, remove trailing newline

        // https://stackoverflow.com/questions/38767967/clear-input-buffer-after-fgets-in-c

        // get pointer to position of the first instance of the newline character in `user_input`
        // since `user_input` will only be updated from `fgets`, it will either have 1 newline character, or no newline characters
        // in the case of no newline characters, the buffer overflowed, and `strchr` will return `NULL`
        // otherwise, we can use pointer arithmetic to replace the trailing newline with a null terminating character
        char * newline_pos = strchr(user_input, '\n');
        if (newline_pos == NULL)
        {
            int c;
            while ((c = getchar()) != EOF && c != '\n');
        }
        else 
        {
            // use pointer arithmetic to replace the newline character with a null terminating character
            user_input[newline_pos - user_input] = '\0';
        }



        // EXECUTE USER'S COMMAND   

        // case where user inputs nothing
        if (user_input[0] == '\0')
        {
            printf("> No command entered.\n");
        }
        // exit program
        else if (user_input[0] == 'q')
        {
            prog_loop = 0;
        }
        // help command
        else if (user_input[0] == 'h')
        {
            printf("> `q`: exit program\n");
        }
        // command not recognized, tell user how to access the help command
        else
        {
            printf("> Command not recognized\n");
            printf("> Type `h` for help.\n");
        }
    }

    printf("> Exiting program...\n");

    // free memory
    cleanup_list(&rr_list);

    // program ended with no errors
    return 0;
}