#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "seqbot_helpers.h"

/* Return the melting temperature of sequence, or -1 if the sequence is invalid.
 * The melting temperature formula is given in the handout.
 * An invalid sequence is a sequence of length 0, or a sequence that contains
 * characters other than 'A', 'C', 'G', 'T'.
 */
int calculate_melting_temperature(char *sequence, int sequence_length)
{
    int n_A = 0, n_C = 0, n_G = 0, n_T = 0;
    for(int i=0; i < sequence_length; i++){
        char seq = sequence[i];
        if (seq == 'A'){
            n_A += 1;
        } else if (seq == 'C'){
            n_C += 1;
        } else if (seq == 'T'){
            n_T += 1;
        } else if (seq == 'G'){
            n_G += 1;
        } else {
            return -1;
        }
    }
    int melt_temp = (n_A + n_T)*2 + (n_C + n_G)*4;

    if(melt_temp != 0){
        return melt_temp;
    } else {
        return -1;
    }
}

/* Prints the instructions to make a molecule from sequence.
 * If an invalid character is found in sequence print
 * "INVALID SEQUENCE" and return immediately
 */
void print_instructions(char *sequence, int sequence_length)
{
    printf("START\n");//START

    int count = 0;
    char letter = 'a';
    for(int i = 0; i < sequence_length; i++){//WRITE
        char seq = sequence[i];
        if (seq == 'A'){
            letter = 'A';
            count += 1;
            if (sequence[i+1] != 'A'){  //if the next letter is still A, go to the next loop and count + 1, else printf
                printf("WRITE %c %d\n", letter, count);
		count = 0;
            }
        } else if (seq == 'C'){
            letter = 'C';
            count += 1;
            if (sequence[i+1] != 'C'){  //if the next letter is still C, go to the next loop and count + 1, else printf
                printf("WRITE %c %d\n", letter, count);
		count = 0;
            }
        } else if (seq == 'T'){
            letter = 'T';
            count += 1;
            if (sequence[i+1] != 'T'){  //if the next letter is still T, go to the next loop and count + 1, else printf
                printf("WRITE %c %d\n", letter, count);
		count = 0;
            }
        } else if (seq == 'G'){
            letter = 'G';
            count += 1;
            if (sequence[i+1] != 'G'){  //if the next letter is still G, go to the next loop and count + 1, else printf
                printf("WRITE %c %d\n", letter, count);
		count = 0;
            }
        } else {
            printf("INVALID SEQUENCE\n");
            return;
        }
    }

    int temp = calculate_melting_temperature(sequence, sequence_length);
    printf("SET_TEMPERATURE %d\n", temp);//SET_TEMPERATURE

    printf("END\n");//END
}



/* Print to standard output all of the sequences of length k.
 * The format of the output is "<length> <sequence> 0" to 
 * correspond to the input format required by generate_molecules_from_file()
 * 
 * Reminder: you are not allowed to use string functions in these files.
 */
void helper(char set[], char prefix[], int n, int pos, int k){
    if (pos == -1){//basecase
        printf("%d %s %d\n", k, prefix, 0);
        return;
    } else {
        for(int i = 0; i < n; i++){
            //char[] newPrefix = strcat(prefix, set[i]);
            prefix[pos] = set[i];
            helper(set, prefix, n, pos-1, k);
        }
    }
}

void generate_all_molecules(int k)
{
    char set[4] = {'A', 'C', 'G', 'T'};
    int n = 4;
    char prefix[k+1];
    prefix[k] = '\0';
    int pos = k-1;
    helper(set, prefix, n, pos, k);
}



/* Print the instructions for each of the sequences found in filename according
 * to the mode provided.
 * filename contains one sequence per line, and the format of each line is
 * "<length> <sequence> <mode>" where 
 *     - <length> is the number of characters in the sequence 
 *     - <sequence> is the array of DNA characters
 *     - <mode> is either 0, 1, 2, or 3 indicating how the <sequence> should 
 *              be modified before printing the instrutions. The modes have the 
 *              following meanings:
 *         - 0  - print instructions for sequence (unmodified)
 *         - 1  - print instructions for the the complement of sequence
 *         - 2  - print instructions for the reverse of sequence
 *         - 3  - print instructions for sequence where it is complemented 
 *                and reversed.
 * 
 * Error checking: If any of the following error conditions occur, the function
 * immediately prints "INVALID SEQUENCE" to standard output and exits the 
 * program with a exit code of 1.
 *  - length does not match the number of characters in sequence
 *  - length is not a positive number
 *  - sequence contains at least one invalid character
 *  - mode is not a number between 0 and 3 inclusive
 * 
 * You do not need to verify that length or mode are actually integer numbers,
 * only that they are in the correct range. It is recommended that you use a 
 * fscanf to read the numbers and fgetc to read the sequence characters.
 */
char *complement(char *sequence, int sequence_length){
    for(int i = 0; i < sequence_length; i++){
        if (sequence[i] == 'A'){
            sequence[i] = (char)'T';
        } else if (sequence[i] == 'C'){
            sequence[i] = (char)'G';
        } else if (sequence[i] == 'G'){
            sequence[i] = (char)'C';
        } else if (sequence[i] == 'T'){
            sequence[i] = (char)'A';
        } else {//invalid character
            printf("INVALID SEQUENCE\n");
            exit(1);
        }
    }
    return sequence;
}
char *reverse(char *sequence, int sequence_length){
    int size = sizeof(char)*(sequence_length+1);
    char *seq = malloc(size);
    int j = 0;
    for(int i = sequence_length-1; i >= 0; i--) {
        seq[j] = (char)sequence[i];
        j++;
    }
    seq[size-1] = '\0';
    return seq;
}

void generate_molecules_from_file(char* filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    int length;
    while(fscanf(file, "%d", &length) == 1){
        if (length < 0){//length is not a positive number
            printf("INVALID SEQUENCE\n");
            exit(1);
        }
	int size = sizeof(char)*(length+1);
        char *sequence = malloc(size);
        sequence[size-1] = '\0';
        fgetc(file);//move the cursor over the space between <length> and <sequence>
        for (int i=0; i < length; i++){
            char c = fgetc(file);
            if (c == 'A' || c == 'C' || c == 'G' || c == 'T'){
                sequence[i] = c;
            } else {//invalid character
            printf("INVALID SEQUENCE\n");
            exit(1);
            }
        }

        int mode;
        fgetc(file);//move the cursor over the space between <sequence> and <mode>
        fscanf(file, "%d", &mode);
        if (mode == 0){//unmodified
            print_instructions(sequence, length);
        } else if (mode == 1){//complement
            sequence = complement(sequence, length);
            print_instructions(sequence, length);
        } else if (mode == 2){//reverse
            sequence = reverse(sequence, length);
            print_instructions(sequence, length);
        } else if (mode == 3){//complement and reverse
            sequence = complement(sequence, length);
            sequence = reverse(sequence, length);
            print_instructions(sequence, length);
        } else {//mode is not a number between 0 and 3 inclusive
            printf("INVALID SEQUENCE\n");
            exit(1);
        }
	free(sequence);
    }

    fclose(file);
}
