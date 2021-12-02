#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void directRead(char* filename, long* res){

	FILE* inputFile = fopen(filename, "r");

	if(!inputFile){
		printf("File not found!\n");
		return;
	}

	long x = 0;
	int aim = 0;
	long y = 0;


	int read;

	char direction[8];
	int movement;
		

	while(1){

		read = fscanf(inputFile, "%s %d\n", direction, &movement);
		
		if(read != 2){
			break;
		}


		if(!strcmp("up", direction)){

			aim -= movement;
			continue;
		}

		if(!strcmp("down", direction)){
 
             aim += movement;
             continue;
         }

		if(!strcmp("forward", direction)){
 
             x += movement;
             y += aim * movement;
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

	long result[2] = {0,0};
	

	directRead(argv[1], result);

	printf("Position: %ld, Depth: %ld\n", result[0], result[1]);
	return 0;
}
