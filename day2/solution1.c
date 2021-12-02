#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void directRead(char* filename, int* res){

	FILE* inputFile = fopen(filename, "r");

	if(!inputFile){
		printf("File not found!\n");
		return;
	}

	int x = 0;
	int y = 0;

	int read;

	char direction[8];
	int movement;
		

	while(1){

		read = fscanf(inputFile, "%s %d\n", direction, &movement);
		
		if(read != 2){
			break;
		}


		if(!strcmp("up", direction)){

			y -= movement;
			continue;
		}

		if(!strcmp("down", direction)){
 
             y += movement;
             continue;
         }

		if(!strcmp("forward", direction)){
 
             x += movement;
             continue;
         }



	}
	

	res[0] = x;
	res[1] = y;

	fclose(inputFile);
}


int main(int argc, char** argv){

	if(argc != 2){

		printf("Usage: %s <input File>\n", argv[0]);
		return 1;

	}

	int result[2] = {0,0};

	directRead(argv[1], result);

	printf("Position: %d, Depth: %d\n", result[0], result[1]);
	return 0;
}
