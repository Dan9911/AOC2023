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


	char line[250];
	int game_num = 0;
	int sum = 0;
	while(fgets(line, 250, fileptr)){
		int not_valid = 0;
		int max_red = 0;
		int max_blue = 0;
		int max_green = 0;
		game_num++;
		char *token = strtok(line, ":");
		while(token != NULL){
			int red = 0, blue = 0, green = 0;
			token = strtok(NULL,";");
			if(token != NULL){
				char *blueptr = strstr(token, "blue");
				char *redptr = strstr(token, "red");
				char *greenptr = strstr(token, "green");
				if(blueptr != NULL){
					blue = atoi(blueptr-3);
				}
				if(redptr != NULL){
					red = atoi(redptr-3);
				}
				if(greenptr != NULL){
					green = atoi(greenptr-3);
				}
				if(red > max_red){
					max_red = red;
				}
				if(blue > max_blue){
					max_blue = blue;
				}
				if(green > max_green){
					max_green = green;
				}
			}
		}
		if(!not_valid){
			sum += max_red * max_blue * max_green;
		}
	}
	printf("%d\n", sum);

	return EXIT_SUCCESS;
}
