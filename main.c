/* Rosa Knowles
 * 9/22/2025
 * Main!
 * Contains a handful of useful functions, and the actual program itself.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record_release.h"
#include "savmgr.h"

#define BUFFERSIZE 75



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


void cl_in(char * buff, size_t buff_size)
{
    // handles command line input

    fgets(buff, buff_size, stdin);

    // if input buffer overflowed, flush it
    // else, remove trailing newline

    // https://stackoverflow.com/questions/38767967/clear-input-buffer-after-fgets-in-c

    // get pointer to position of the first instance of the newline character in `buff`
    // since `buff` will only be updated from `fgets`, it will either have 1 newline character, or no newline characters
    // in the case of no newline characters, the buffer overflowed, and `strchr` will return `NULL`
    // otherwise, we can use pointer arithmetic to replace the trailing newline with a null terminating character
    char * newline_pos = strchr(buff, '\n');
    if (newline_pos == NULL)
    {
        int c;
        // flushes the input buffer
        // magic!
        while ((c = getchar()) != EOF && c != '\n');
    }
    else 
    {
        // use pointer arithmetic to replace the newline character with a null terminating character
        buff[newline_pos - buff] = '\0';
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
    char * user_input = (char *)malloc(sizeof(char) * BUFFERSIZE);

    // print welcome message 
    printf("> Welcome to Rosa's Record Organizer!\n");

    while (prog_loop == 1)
    {
        printf("> ");


        // GET USER INPUT

        cl_in(user_input, BUFFERSIZE);


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
            printf("> `add`: add a release to the collection\n");
            printf("> `echo []`:\n");
            printf(">\t`n`: print the \"n\"th element in the record collection\n");
            printf(">\t`*`: print all elements in the record collection\n");
            printf(">\t`len`: print the number of elements in the record collection\n");
            printf("> `sort`: organize the record collection\n");
            printf("> `save`: save a byte-representation of the record collection to a file\n");
        }
        // command to add a release to the record collection
        else if (strcmp(user_input, "add") == 0)
        {
            // initialize temporary variables to store user input
            record_release temp_release;

            char temp_title[BUFFERSIZE];
            char temp_artist[BUFFERSIZE];
            char temp_genre[BUFFERSIZE];

            int8_t temp_month = ERR;
            int8_t temp_day = 0;
            int16_t temp_year = 0;

            rdate temp_date;

            RFORMAT temp_format = ERR_F;

            printf(">\n> Title: ");
            cl_in(temp_title, BUFFERSIZE);

            printf("> Artist: ");
            cl_in(temp_artist, BUFFERSIZE);

            // might eventually change this to a list of pre-picked genres
            // will probably want a way to figure out how to not have to hardcode this list
            printf("> Genre: ");
            cl_in(temp_genre, BUFFERSIZE);

            // prompt user for release date, and parse their input
            printf("> Release Date: ");

            int8_t input_loop = 1;
            do
            {
                cl_in(user_input, BUFFERSIZE);

                // check user input
                // handle the parsed input by jumping to a seperate section of code
                if (sscanf(user_input, "%d/%d/%d", &temp_month, &temp_day, &temp_year) == 3)
                {
                    temp_date = Create_Date(temp_month, temp_day, temp_year);
                    printf("> %d/%d/%d\n", temp_month, temp_day, temp_year);

                    // checks if input is valid
                    if (!(temp_date.r_day < 0 || temp_date.r_year < 0 || temp_date.r_month == ERR))
                    {
                        input_loop = 0;
                        continue;
                    }
                }

                printf("> ");
            }
            while (input_loop);


            // tell user what the possible formats are, and their corresponding codes
            printf("> Enter a format code: \n");
            printf("> [1] %s\n", VINYL_LP_STR);
            printf("> [2] %s\n", VINYL_EP_STR);
            printf("> [3] %s\n", VINYL_10_STR);
            printf("> [4] %s\n", CD_STR);
            printf("> [5] %s\n", CASSETTE_STR);
            printf("> [6] %s\n", DIGITAL_STR);
            printf("> [7] %s\n", SHELLAC_STR);

            // get user input until it's valid
            input_loop = 1;
            do
            {
                printf("> ");
                cl_in(user_input, BUFFERSIZE);

                // check if input is valid, and copy the input into `temp_format`
                // if the input is valid, end the loop
                if (sscanf(user_input, "%d", &temp_format) == 1)
                {
                    if (temp_format >= VINYL_LP && temp_format <= SHELLAC)
                    {
                        input_loop = 0;
                    }
                    else
                    {
                        // ensures the loop continues... juuuust in case
                        input_loop = 1;
                    }
                }
            }
            while (input_loop);

            temp_release = Create_Release(temp_format, temp_title, temp_artist, temp_genre, temp_date, BUFFERSIZE);

            // if size is 0, insert the release at the head
            // else, call the insert head function to insert the element into the list 
            if (len == 0)
            {
                rr_list->data = temp_release;
            }
            else
            {
                insert_head(&rr_list, temp_release);
            }

            // increase list length!!!
            len++;

            // make sure the loop doesn't exit, because it really likes to for some reason
            prog_loop = 1;
        }
        // sort command 
        // self-explanatory
        else if (strcmp(user_input, "sort") == 0)
        {
            rr_list = mergesort(rr_list);
            if (rr_list != NULL)
                printf("> Record collection successfully organized!\n");
            // if `rr_list` is null, crash the program
            else
                return 1;
        }
        // save command
        // saves the record collection to a file in a byte representation
        else if (strcmp(user_input, "save") == 0)
        {
            // open file, handle errors with opening the file
            // opened in binary mode
            FILE * save_file = fopen(".sav", "wb");
            if (save_file == NULL)
            {
                fprintf(stderr, "Error opening file!\n");
                return 1;
            }

            for (size_t i = 0; i < len; ++i)
            {
                uint8_t * byte_arr = NULL;

                // get byte representation of record release at index `i`
                record_release temp_rr = get_record_release(rr_list, i);
                size_t byte_arr_len = get_bytearr_rep(&byte_arr, &temp_rr);

                // write each byte in the array to a file
                for (size_t j = 0; j < byte_arr_len; ++j)
                {
                    fwrite(&byte_arr[j], sizeof(uint8_t), 1, save_file);
                }

                // `get_bytearr_rep` calls malloc, must free!!!
                free(byte_arr);
            }

            // close the save file
            fclose(save_file);
        }
        // echo command
        // prints out contents relating to the list
        // the help command explains each of the cases, as well as the comments in this if statement
        // use pointer math to determine if "echo" is at the front of the user's input string
        else if (user_input - strstr(user_input, "echo") == 0)
        {
            // print nth element in list
            size_t index = 0;

            // use pointer arithmetic to create a substring that ends after echo
            char * temp_str = user_input;
            temp_str += (strlen(user_input) >= 5) ? 5 : strlen(user_input);

            // second argument is a number 
            if (sscanf(temp_str, "%d", &index) == 1)
            {
                // index in range
                if (index >= 1 && index <= len)
                {
                    record_release temp = get_record_release(rr_list, index - 1);
                    printf(">\n> [%d]\n", index);
                    print_record_release(buff, &temp);
                }
                // index out of range
                else
                {
                    printf("> %d out of range.\n", index);
                }
            }
            // second argument is a string
            else
            {
                // arg: "*"
                // prints all elements in the list
                if (strcmp(temp_str, "*") == 0)
                {
                    if (len > 0)
                        print_list(buff, rr_list);
                    else
                        printf("> 0 out of range.\n");
                }
                // arg: "len"
                // prints the length of the release list
                else if (strcmp(temp_str, "len") == 0)
                {
                    printf("> %d\n", len);
                }
                // second argument is invalid!
                // print a short error message
                else
                {
                    printf("> \"%s\" not recognized as a valid argument\n", temp_str);
                }
            }

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
    free(user_input);

    // program ended with no errors
    return 0;
}