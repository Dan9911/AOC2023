#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

FILE *fileptr;

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
		char first = '\0';
		char last = '\0';
		int num_char = strlen(line) - 1;
		for(int i = 0; i < num_char; i++){
			if(isdigit(line[i])){
				first = line[i];
				break;
			}
		}
		for(int i = num_char - 1; i >= 0; i--){
			if(isdigit(line[i])){
				last = line[i];
				break;
			}
		}

		char str[] = {first, last, '\0'};
		int num = atoi(str);
		sum += num;


	}
	printf("%d\n", sum);
	return EXIT_SUCCESS;
}
