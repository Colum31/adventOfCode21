#include <stdio.h>
#include <stdlib.h>

int countLines(char* filename){

	FILE* inputFile = fopen(filename, "r");
	int lines = 1;
	char c = ' ';
	int read = 1;
	
	while(read){

		if(c == '\n'){

			lines++;
		}

		read = fread(&c, 1, 1, inputFile);
	}
		
	fclose(inputFile);

	return lines;

}


int* createIntArray(char* filename, int size){

	int* intArray = malloc(size * sizeof(int));

	FILE* inputFile = fopen(filename, "r");
	
	for(int line = 0; line < size; line++){

		fscanf(inputFile, "%d\n", &intArray[line]);

	}
	
	fclose(inputFile);
	return intArray;

}


int compareEntries(int* inArray, int len){

	int res = 0;

	for(int i = 0; i < len - 2; i++){
		
		if(inArray[i] < inArray[i + 1] ){

			res++;
		}
	}

	return res;
}

int main(int argc, char** argv){

	if(argc != 2){

		printf("Usage: %s <inputFile>\n", argv[0]);
		return 1;
	}

	int lines = countLines(argv[1]);
	int* array = createIntArray(argv[1], lines);

	int res = compareEntries(array, lines);
	free(array);

	printf("Number increased %d times\n", res);
	return 0;

}
