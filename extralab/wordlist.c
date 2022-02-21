
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordlist.h"


/* Read the words from a filename and return a linked list of the words.
 *   - The newline character at the end of the line must be removed from
 *     the word stored in the node.
 *   - You an assume you are working with Linux line endings ("\n").  You are
 *     welcome to also handle Window line endings ("\r\n"), but you are not
 *     required to, and we will test your code on files with Linux line endings.
 *   - The time complexity of adding one word to this list must be O(1)
 *     which means the linked list will have the words in reverse order
 *     compared to the order of the words in the file.
 *   - Do proper error checking of fopen, fclose, fgets
 */

struct node *read_list(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    struct node *head = malloc(sizeof(struct node));
    if (head == NULL){
        printf("unable to allocate memory");
        exit(1);
    }
    char word[6];
    struct node *temp;

    temp = head; //create linked list and link to head

    while (fscanf(fp, "%s", word) == 1){
        struct node *newNode = malloc(sizeof(struct node));

        /* If memory is not allocated for newNode */
        if(newNode == NULL)
        {
            printf("Unable to allocate memory.");
            break;
        }

	strncpy(newNode->word, word, 6);
        newNode->word[6] = '\0';; // Link data field of newNode
        newNode->next = NULL; // Make sure new node points to NULL 

        temp->next = newNode; // Link previous node with newNode
        temp = temp->next;    // Make current node as previous node
    }
    fclose(fp);
    return head;
}

/* Print the words in the linked-list list one per line
 */
void print_dictionary(struct node *list) {
        if (list == NULL){
        printf("List is empty.\n");
        return;
    }
    struct node *temp;
    temp = list;
    while (temp != NULL){
        printf("%s\n", temp->word);
        temp = temp->next;
    }
}
/* Free all of the dynamically allocated memory in the dictionary list 
 */
void free_dictionary(struct node *list) {
    if (list == NULL){
        printf("List is empty.\n");
        return;
    }

    struct node *temp;
    struct node *nextNode;
    temp = list;
    while (temp != NULL){
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
}

