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
    record_release testerA = Create_Release(VINYL_LP, "Selected Ambient Works 85-92", "Aphex Twin", "Electronic", Create_Date(NOV, 9, 1992), BUFFERSIZE);
    record_release testerB = Create_Release(VINYL_LP, "Untrue", "Burial", "Electronic", Create_Date(NOV, 5, 2007), BUFFERSIZE);

    char * str_rep = NULL;

    print_record_release(str_rep, &testerA);
    printf(">\n");
    print_record_release(str_rep, &testerB);

    return 0;
}