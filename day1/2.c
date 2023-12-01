#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

FILE *fileptr;
char *digits[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int is_digit(char* to_check){
	for(int i = 0; i < 9; i++){
		char *ptr = strstr(to_check, digits[i]);
		if(ptr != NULL){
			return i+1;
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	fileptr = fopen(argv[1], "rb");
	if(!fileptr){
		printf("File Could not be opened");
		return EXIT_FAILURE;
	
	}


	char line[100];
	int sum = 0;
	while(fgets(line, 100, fileptr)){
		char first[2];
		char second[2];
		int num_char = strlen(line) - 1;
		for(int i = 0; i < num_char; i++){
			if(isdigit(line[i])){
				first[0] = line[i];
				first[1] = '\0';
				break;
			}
			char *candidate_1 = (char*)calloc(i+1 * sizeof(char), sizeof(char));
			strncpy(candidate_1, line, i+1); 
			int digit_1 = is_digit(candidate_1);
			if(digit_1){
				sprintf(first, "%d", digit_1);
				free(candidate_1);
				break;
			}
			free(candidate_1);
		}
		for(int i = num_char-1; i >= 0; i--){
			if(isdigit(line[i])){
				second[0] = line[i];
				second[1] = '\0';
				break;
			}
			char *candidate_2 = (char*)calloc((num_char-i) * sizeof(char), sizeof(char));
			strncpy(candidate_2, line+i, num_char-i);
			int digit_2 = is_digit(candidate_2);
			if(digit_2){
				sprintf(second, "%d", digit_2);
				free(candidate_2);
				break;
			}
			free(candidate_2);
		}



		char str[] = {first[0], second[0], '\0'};
		int num = atoi(str);
		sum += num;


	}
	printf("%d\n", sum);
	return EXIT_SUCCESS;
}
