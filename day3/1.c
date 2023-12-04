#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

FILE *fileptr;

int adjacent(char row[], int start, int end){
	for(int i = start; i <= end; i++){
		if(!isdigit(row[i]) & (row[i] != '.')){
			return 1;
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


	char line[250];
	int x = 0;
	int y = 0;
	while(fgets(line, 250, fileptr)){
		x = strlen(line) - 1;
		y++; 
	}
	char grid[y+2][x+2];
	for(int i = 0; i < y+2; i++){
		for(int j = 0; j < x+2; j++){
			if(i == 0 | i == y+1){
				grid[i][j] = '.';
			}
			if(j == 0 | j == x + 1){
				grid[i][j] = '.';
			}
		}
	}

	rewind(fileptr);
	int index = 1;
	while(fgets(line, 250, fileptr)){
		for(int i = 1; i < x+1; i++){
			grid[index][i] = line[i-1];
		}
     		index++;
	}


	int sum = 0;
	for(int i = 1; i < y+1; i++){
		for(int j = 1; j < x+1; j++){
			if(!isdigit(grid[i][j])){
				continue;
			}
			int left = 0;
			int right = 0;
			int l_index = j;
			while(isdigit(grid[i][j])){
				j++;
			}
			int r_index = j-1;
			int start = l_index-1;
			int end = r_index+1;
			if(grid[i][start] != '.'){
				left = 1;
			}
			if(grid[i][end] != '.'){
				right = 1;
			}
			int above = adjacent(grid[i-1], start, end);
			int below = adjacent(grid[i+1], start, end);
			if(left | right | above | below){
				int num_length = r_index-l_index + 1;
				char numstr[num_length+1];
				char *row = grid[i];
				strncpy(numstr, row+l_index, num_length);
				numstr[num_length] = '\0';
				int num = atoi(numstr);
				sum += num;
			}
		}
	}
	printf("%d\n", sum);
	
	return EXIT_SUCCESS;
}
