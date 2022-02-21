#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "constraints.h"

/* Create and initialize a constraints struct.
 * Sets the fields to 0 or empty string.
 * Return a pointer to the newly created constraints struct.
 */
struct constraints *init_constraints() {
    struct constraints *c = malloc(sizeof(struct constraints));
    for (int i =0; i < WORDLEN; i++){
        strcat((c->must_be)[i], "");
    }
    for(int i=0; i<ALPHABET_SIZE; i++){
        (c->cannot_be)[i] = 0;
    }
    return c;
}

/* Update the "must_be" field at "index" to be a string
 * The tile at this index is green, therefore the letter at "index"
 * must be "letter"
 */
void set_green(char letter, int index, struct constraints *con) {
    assert(islower(letter));
    assert(index >= 0 && index < SIZE);
    char str[2];
    str[1]= "\0";
    str[0] = letter;
    strcat((con->must_be)[index], str);
}

/* Update "con" by adding the possible letters to the string at the must_be
 * field for "index".
 * - index is the index of the yellow tile in the current row to be updated
 * - cur_tiles is the tiles of this row
 * - next_tiles is the tiles of the row that is one closer to the solution row
 * - word is the word in the next row (assume word is all lower case letters)
 * Assume cur_tiles and next_tiles contain valid characters ('-', 'y', 'g')
 *
 * Add to the must_be list for this index the letters that are green in the
 * next_tiles, but not {(green in the cur_tiles) or [(green or yellow) in the
 * next_tiles at index]}.
 * Also add letters in yellow tiles in next_tiles.
 */
void set_yellow(int index, char *cur_tiles, char *next_tiles,
                char *word, struct constraints *con) {

    assert(index >=0 && index < SIZE);
    assert(strlen(cur_tiles) == WORDLEN);
    assert(strlen(next_tiles) == WORDLEN);
    assert(strlen(word) == WORDLEN);

    char str[2];
    str[1]= "\0";
    str[0] = letter;
    strcat((con->must_be)[index], str);

    for(int i=0; i < WORDLEN; i++){
        int asmp = 1;
        if(i != index && ((next_tiles)[i] == 'g' || next_tiles[i] == 'y') && cur_tiles[i] != 'g'){
            for (int j=0; j<WORDLEN; j++){
                if (word[i] == word[j]){
                         asmp =0;           
                }

            }
            if (asmp){
                str[0] = word[i];
                strcat((con->must_be)[index], str);
            }
        }
    }


}


/* Add the letters from cur_word to the cannot_be field.
 * See the comments in constraints.h for how cannot_be is structured.
 */
void add_to_cannot_be(char *cur_word, struct constraints *con) {
    assert(strlen(cur_word) <= WORDLEN);

    for (int i=; i<strlen(cur_word); i++){
        char curr_c = cur_word[i];
        (con->cannot_be)[ c - 'a'] = 1;
    }
    
}

void print_constraints(struct constraints *c) {
    printf("cannot_be: ");

    for (int i=0; i<ALPHABET_SIZE; i++){
        if ((c->cannot_be)[i] == 1){
            printf("%c", i + 'a');
        }
    }

    printf("\nmust_be\n");

    for (int j=0; j<WORDLEN; j++){
        printf("%d: ", j);
        char cc[] = c->must_be)[j];
        for (int k=0; k<strlen(cc); k++){
            printf("%c", cc[k]);
        }
        printf("\n");
    }

    printf("\n");
}

