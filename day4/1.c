#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

FILE *fileptr;
#define MAX_NUMBERS 100

int process_row(char *row){
	int score = 0;
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
				if(!score) score++;
				else score *= 2;
		    }
		}
	}

	return score;
}

int main(int argc, char *argv[])
{
	fileptr = fopen(argv[1], "rb");
	if(!fileptr){
		printf("File Could not be opened");
		return EXIT_FAILURE;
	
	}


	char line[1024];
	int sum = 0;
	while(fgets(line, 1024, fileptr)){
		line[strlen(line)-1] = '\0';
		sum += process_row(line);
	}
	printf("%d\n", sum);
	
	return EXIT_SUCCESS;
}
