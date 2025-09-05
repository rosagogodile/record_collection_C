#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record_release.h"

#define BUFFERSIZE 50

int main(int argc, char ** argv)
{
    record_release tester = Create_Release(VINYL_LP, "Selected Ambient Works 85-92", "Aphex Twin", "Electronic", Create_Date(NOV, 9, 1992), BUFFERSIZE);

    size_t safe_buff = get_safe_buff(&tester);
    char * str_rep = (char *)malloc(sizeof(char) * safe_buff);

    

    rr_string(&tester, str_rep, safe_buff);

    printf("%d\n", safe_buff - strlen(str_rep));

    printf("%s\n", str_rep);

    return 0;
}