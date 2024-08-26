#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>


/**
 * Function to check each and every value in char array is a numeric character from 0 to 9 excluding
 * the null terminator.
 * 
 * \param value[] - array of chars
 * \return true iff every char belongs to set of numeric chars {'0', '1', '2'...'9'} else false
 */
int isNumber(char values[]) {
    int i;   
    for (i=0; values[i]!='\0';i++) {
        if (isdigit(values[i])==0) {
            return false;
        }
    }
    return true;
}