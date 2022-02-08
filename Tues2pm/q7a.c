/* Question 7: [6 marks] Consider the following code and complete the 
 * implementation of join_strings. Read the comment for this function 
 * carefully as it describes the expected behaviour of the function.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* join_strings concatenates the "n" strings in "strs", separating the
 * strings with the character "separator" 
 * The joined string is allocated on the heap and returned to the caller.
 * Parameters:
 *          strs - an array of C strings to be joined together
 *            n - the number of strings in the array
 *    separator - the character that separates each input string in the output
 * Returns NULL when n <= 0.
*/

char* join_strings(char** strs, int n, char separator)
{
    char *result = malloc(sizeof(char) *n);
    for (int i = 0; i<n;i++){
        strcat(result, (*strs)[i]);
    }
    return result;
}

// This small main function shows you how the function will be called
int main()
{   
    char* input[3] = { "rain", "snow", "wind" };
    char* joined = join_strings(input, 3, ',');
    printf("%s\n", joined); // prints rain,snow,wind
    free(joined);
    return 0;
}
