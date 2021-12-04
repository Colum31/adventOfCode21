#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBERWIDTH 12

void directRead(char* filename, int* arr){

	FILE* inputFile = fopen(filename, "r");

	if(!inputFile){

		printf("Could not open file %s!\n", filename);
		return;
	}

	int bits[NUMBERWIDTH];
	int lines = 0;
	int linePos = 0;
	char c;


	for(int pos = 0; pos < NUMBERWIDTH; pos++){

		bits[pos] = 0;

	}


	while(1){

		int read = fread(&c, 1, 1, inputFile);	

		if(!read){
		
			break;
	
		}

		if(c == '\n'){

			linePos = 0;
			lines++;
			continue;
		}

	
		if(c == '1'){
		
			bits[linePos] += 1;
				
		}

		linePos++;

	}
	
	fclose(inputFile);

	
	int gamma = 0;
	int epsilon = 0;

	for(int i = 0; i < NUMBERWIDTH; i++){

	
		if(bits[i] > (lines / 2)){

			gamma += (int) pow(2, NUMBERWIDTH - 1 - i);

		}else{

			epsilon += (int) pow(2, NUMBERWIDTH - 1 - i);	
		}
	}

	arr[0] = gamma;
	arr[1] = epsilon;

}


int main(int argc, char** argv){

	if(argc != 2){

		printf("Usage: %s <input file>\n", argv[0]);
		return 1;
	}


	int res[2] = {0,0};

	directRead(argv[1], res);
	
	printf("Gamma value: %d, Epsilon value %d\n", res[0], res[1]);
	return 0;

}
