#include <stdio.h>
#include <stdlib.h>

#define VALUES_IN_FILE 300 

void directRead(char* filename, long* lanternArr){

	   	FILE* inputFile = fopen(filename, "r");
		int cycle;	

		for(int i = 0; i < VALUES_IN_FILE - 1; i++){

			fscanf(inputFile,"%d,", &cycle);
			lanternArr[cycle] += 1;
		}
	
		fscanf(inputFile, "%d", &cycle);
		lanternArr[cycle] += 1;		

		fclose(inputFile);
}

void printLongArray(long* array, int len){
	
	printf("[");

	for(int i = 0; i < len - 1; i++){

		printf("%ld, ", array[i]);

	}

	printf("%ld]", array[len - 1]);

}


long sumLongArray(long* array, int len){

	long sum = 0;
		
	for(int i = 0; i < len; i++){

		sum += array[i];
	}

	return sum;
}

void simulateGrowth(long* lanterns, int cycles){

	for(int cycle = 0; cycle < cycles; cycle++){

		long newLanterns = lanterns[0];

		for(int i = 1; i < 9; i++){
	
			lanterns[i-1] = lanterns[i];
		}

		lanterns[8] = newLanterns;
		lanterns[6] += newLanterns;

		printf("After the %dth cycle, there are %ld lanterns!\n", cycle + 1, sumLongArray(lanterns, 9));
	
	}
}


void initLongArray(long* arr, int len){

	for(int i = 0; i < len; i++){
		arr[i] = 0;
	}
}


int main(int argc, char** argv){

	if(argc != 2){

		printf("Usage %s <input file>\n", argv[0]);
		return 1;

	}

	long lanterns[9];

	initLongArray(lanterns, 9);
	directRead(argv[1], lanterns);
	
	printLongArray(lanterns, 9);	
	printf("\n");
	simulateGrowth(lanterns, 256);

	return 0;

}

