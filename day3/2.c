#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

FILE *fileptr;

int adjacent(char row[], int start, int end){
	for(int i = start; i <= end; i++){
		if(isdigit(row[i])){
			return i;
		}
	}
	return 0;
}

int extract_from_row(char row[], int start){
	int l_index = start;
	while(isdigit(row[l_index])){
		l_index--;
	}
	l_index++;
	int r_index = start;
	while(isdigit(row[r_index])){
		r_index++;
	}
	r_index--;
	int num_length = r_index-l_index + 1;
	char numstr[num_length+1];
	char *row_ptr = row;
	strncpy(numstr, row_ptr+l_index, num_length);
	numstr[num_length] = '\0';
	int num = atoi(numstr);
	return num;


}

int extract_left(char row[], int start){
	int r_index = start;
	while(isdigit(row[start])){
		start--;
	}
	int l_index = start+1;

	int num_length = r_index-l_index + 1;
	char numstr[num_length+1];
	char *row_ptr = row;
	strncpy(numstr, row_ptr+l_index, num_length);
	numstr[num_length] = '\0';
	int num = atoi(numstr);
	return num;
}

int extract_right(char row[], int start){
	int l_index = start;
	while(isdigit(row[start])){
		start++;
	}
	int r_index = start-1;

	int num_length = r_index-l_index + 1;
	char numstr[num_length+1];
	char *row_ptr = row;
	strncpy(numstr, row_ptr+l_index, num_length);
	numstr[num_length] = '\0';
	int num = atoi(numstr);
	return num;
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
			if(grid[i][j] != '*'){
				continue;
			}
			int candidate_left = 1;
			int candidate_right = 1;
			int candidate_above = 1;
			int candidate_below = 1;
			int candidate_above_left = 1;
			int candidate_above_right = 1;
			int candidate_below_left = 1;
			int candidate_below_right = 1;
			int num_found = 0;
			if(isdigit(grid[i][j+1])){
				candidate_right = extract_right(grid[i], j+1);
				num_found++;
			}
			if(isdigit(grid[i][j-1])){
				candidate_left = extract_left(grid[i], j-1);
				num_found++;
			}

			if(isdigit(grid[i-1][j])){
				candidate_above = extract_from_row(grid[i-1], j);
				num_found++;
			}
			else{
				if(isdigit(grid[i-1][j-1])){
				candidate_above_left = extract_from_row(grid[i-1], j-1);
				num_found++;
				}
				if(isdigit(grid[i-1][j+1])){
				candidate_right = extract_from_row(grid[i-1], j+1);
				num_found++;
				}
			}

			if(isdigit(grid[i+1][j])){
				candidate_below = extract_from_row(grid[i+1], j);
				num_found++;
			}
			else{
				if(isdigit(grid[i+1][j-1])){
					candidate_below_left = extract_from_row(grid[i+1], j-1);
					num_found++;
				}
				if(isdigit(grid[i+1][j+1])){
					candidate_below_right = extract_from_row(grid[i+1], j+1);
					num_found++;
				}
			}
			int candidate_sum = candidate_below * candidate_above * candidate_left * candidate_right * candidate_below_right * candidate_below_left * candidate_above_left * candidate_above_right;
			if(num_found > 1){
				sum += candidate_sum;
			}

		}
	}
	printf("%d\n", sum);
	
	return EXIT_SUCCESS;
}
