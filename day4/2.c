#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

FILE *fileptr;
#define MAX_NUMBERS 100


int process_row(char *row){
	int instances = 0;
	char *token;
	strtok(row, ":");
	char *leftSide = strtok(NULL, "|");
	char *rightSide = strtok(NULL, "|");

	if (leftSide != NULL && rightSide != NULL) {
		int leftNumbers[MAX_NUMBERS];
		int rightNumbers[MAX_NUMBERS];
		int leftCount = 0, rightCount = 0;

		// Tokenize left side
		token = strtok(leftSide, " ");
		while (token != NULL) {
		    leftNumbers[leftCount++] = atoi(token);
		    token = strtok(NULL, " ");
		}

		// Tokenize right side
		token = strtok(rightSide, " ");
		while (token != NULL) {
		    rightNumbers[rightCount++] = atoi(token);
		    token = strtok(NULL, " ");
		}
		for (int i = 0; i < rightCount; i++) {
		    int isInLeft = 0;
		    for (int j = 0; j < leftCount; j++) {
			if (rightNumbers[i] == leftNumbers[j]) {
			    isInLeft = 1;
			    break;
			}
		    }
		    if (isInLeft) {
			instances += 1;
		    }
		}
	}

	return instances;
}

void get_instances(int *nums_created, int *card_insts, int arr_len, int card_num){
	int num_created = nums_created[card_num];
	for(int i = 1; i <= num_created; i++){
		card_insts[card_num+i] += card_insts[card_num];
	}
	return;
}

int main(int argc, char *argv[])
{
	fileptr = fopen(argv[1], "rb");
	if(!fileptr){
		printf("File Could not be opened");
		return EXIT_FAILURE;
	
	}


	char line[1024];
	int x = 0;
	int numCards = 0;
	while(fgets(line, 1024, fileptr)){
		x = strlen(line)-1;
		numCards++;
	}
	rewind(fileptr);

	int nums_created[numCards];
	int card_insts[numCards];
	int card_index = 0;
	while(fgets(line, 1024, fileptr)){
		line[x] = '\0';
		nums_created[card_index] = process_row(line);
		card_insts[card_index] = 1;
		card_index++;
	}

	int sum = 0;
	for(int i = 0; i < numCards; i++){
		get_instances(nums_created, card_insts, numCards, i);
	}
	for(int i = 0; i < numCards; i++){
		sum += card_insts[i];
	}
	printf("Sum = %d\n", sum);
	
	return EXIT_SUCCESS;
}
