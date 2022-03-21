#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordle.h"
#include "constraints.h"

/* Read the wordle grid and solution from fp. 
 * Return a pointer to a wordle struct.
 * See sample files for the format. Assume the input file has the correct
 * format.  In other words, the word on each is the correct length, the 
 * words are lower-case letters, and the line ending is either '\n' (Linux,
 * Mac, WSL) or '\r\n' (Windows)
 */
struct wordle *create_wordle(FILE *fp) {
    struct wordle *w = malloc(sizeof(struct wordle));
    char line[MAXLINE];
    w->num_rows = 0;

    while (fgets(line, MAXLINE, fp) != NULL) {

        // remove the newline character(s) 
        char *ptr;
        if (((ptr = strchr(line, '\r')) != NULL) ||
            ((ptr = strchr(line, '\n')) != NULL)) {
            *ptr = '\0';
        }

        strncpy(w->grid[w->num_rows], line, SIZE);
        w->grid[w->num_rows][SIZE - 1] = '\0';
        w->num_rows++;
    }
    return w;
}


/* Create a solver_node and return it.
 * If con is not NULL, copy con into dynamically allocated space in the struct
 * If con is NULL set the new solver_node con field to NULL.
 * Tip: struct assignment makes copying con a one-line statements
 */
struct solver_node *create_solver_node(struct constraints *con, char *word) {

    struct solver_node *result = malloc(sizeof(struct solver_node));

    // copy word into the node
    for (int i = 0; i < WORDLEN; i++) {
        result->word[i] = word[i];
    }
    result->word[WORDLEN] = '\0';

    if (con == NULL) {
        result->con = NULL;
    } else {
        result->con = con;
    }

    result->next_sibling = NULL;
    result->child_list = NULL;

    return result;
}

/* Return 1 if "word" matches the constraints in "con" for the wordle "w".
 * Return 0 if it does not match
 */
int match_constraints(char *word, struct constraints *con,
                      struct wordle *w, int row) {

    // check for duplicate solution letter, under the new rules
    for (int i = 0; i < WORDLEN; i++) {
        int count = 0;
        char sol_letter = w->grid[0][i];
        for (int j = 0; j < WORDLEN; j++) {
            if (word[j] == sol_letter) {
                count++;
            }
        }

        if (count > 1) {
            return 0;
        }
    }

    for (int i = 0; i < WORDLEN; i++) {
        char color = w->grid[row][i];
        char letter = word[i];
        // if yellow or green, must be found in must_be
        if ((color == 'y' || color == 'g') && strchr(con->must_be[i], letter) == NULL) {
            return 0;
            // in case of yellow and matching solution letter due to duplicate
        } else if (color == 'y' && letter == w->grid[0][i]) {
            return 0;
            // in case of grey, not match if found in cannot_be
        } else if (color == '-' && con->cannot_be[letter - 'a'] == 1) {
            return 0;
        }
    }

    return 1;
}

// the following is not used
/* remove "letter" from "word"
 * "word" remains the same if "letter" is not in "word"
 */

/*
void remove_char(char *word, char letter) {
    char *ptr = strchr(word, letter);
    if (ptr != NULL) {
        *ptr = word[strlen(word) - 1];
        word[strlen(word) - 1] = '\0';
    }
}
 */

/* Build a tree starting at "row" in the wordle "w". 
 * Use the "parent" constraints to set up the constraints for this node
 * of the tree
 * For each word in "dict", 
 *    - if a word matches the constraints, then 
 *        - create a copy of the constraints for the child node and update
 *          the constraints with the new information.
 *        - add the word to the child_list of the current solver node
 *        - call solve_subtree on newly created subtree
 */
void solve_subtree(int row, struct wordle *w, struct node *dict,
                   struct solver_node *parent) {
    if (verbose) {
        printf("Running solve_subtree: %d, %s\n", row, parent->word);
    }

    if (row == 1) {
        add_to_cannot_be(parent->word, parent->con);
        // we set "ggggg" for color corresponding to the solution and use set_green accordingly
        for (int i = 0; i < WORDLEN; i++) {
            if (w->grid[row][i] == 'g') {
                set_green(w->grid[0][i], i, parent->con);
            } else if (w->grid[row][i] == 'y') {
                // since next_tiles represent the solution, giving color all 'g'
                set_yellow(i, w->grid[row], "ggggg", parent->word, parent->con);
            }
        }
    }

    if (row <= w->num_rows - 1) {
        Node *try = dict;
        while (try != NULL) {
            if (match_constraints(try->word, parent->con, w, row) == 1) {
                struct constraints *child_con = init_constraints();
                struct solver_node *child = create_solver_node(child_con, try->word);
                if (row <= w->num_rows - 2) {
                    // copy cannot_be
                    memcpy(child->con->cannot_be, parent->con->cannot_be, ALPHABET_SIZE);
                    // update cannot_be based on word
                    add_to_cannot_be(child->word, child->con);

                    // set constraints with respect to next_tiles and related constraints
                    for (int i = 0; i < WORDLEN; i++) {
                        if (w->grid[row + 1][i] == 'g') {
                            set_green(w->grid[0][i], i, child->con);
                        } else if (w->grid[row + 1][i] == 'y') {
                                set_yellow(i, w->grid[row + 1], w->grid[row], child->word, child->con);
                        }
                    }
                }
                solve_subtree(row + 1, w, dict, child);
                // update the linked list for recursion
                child->next_sibling = parent->child_list;
                parent->child_list = child;
            }
            try = try->next;
        }
    }
    // debugging suggestion, but you can choose how to use the verbose option
    /*if(verbose) {
        print_constraints(c);
    } */
}

/* Print to standard output all paths that are num_rows in length.
 * - node is the current node for processing
 * - path is used to hold the words on the path while traversing the tree.
 * - level is the current length of the path so far.
 * - num_rows is the full length of the paths to print
 */

void print_paths(struct solver_node *node, char **path,
                 int level, int num_rows) {
    // level is length, so index is level - 1
    path[level - 1] = node->word;

    // if the desired level is reached
    if (level == num_rows) {
        for (int l = 0; l < num_rows; l++) {
            if (l == num_rows - 1) {
                printf("%s ", path[l]);
                printf("\n");
            } else {
                printf("%s ", path[l]);
            }
        }
    } else if (node->child_list != NULL) {
        // go to child_list's head
        struct solver_node *next = node->child_list; // for vertical expansion
        while (next != NULL) {
            // increment corresponding level
            print_paths(next, path, level + 1, num_rows);
            next = next->next_sibling; // for horizontal expansion
        }
    }
}

/* Free all dynamically allocated memory pointed to from w.
 */
void free_wordle(struct wordle *w) {
    if (w != NULL) {
        free(w);
    }
}

/* Free all dynamically allocated pointed to from node
 */
void free_tree(struct solver_node *node) {
    if (node->con != NULL) {
        free_constraints(node->con);
    }

    if (node->next_sibling != NULL) {
        free_tree(node->next_sibling);
    }

    if (node->child_list != NULL) {
        free_tree(node->child_list);
    }

    free(node);
}
