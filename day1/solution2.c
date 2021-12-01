#include <stdio.h>
#include <stdlib.h>

int sum(int* array, int len){
	
	int res = 0;

	for(int i = 0; i < len; i++){

		res += array[i];
	}

	return res;
}


int directCompare(char* filename){

	FILE* inputFile = fopen(filename, "r");
	
	int window[3];

	fscanf(inputFile, "%d\n", &window[0]);
	fscanf(inputFile, "%d\n", &window[1]);
	fscanf(inputFile, "%d\n", &window[2]);

	int prevSum = sum(window, 3);
	int timesBigger = 0;
	int windowPos = 0;


	while(1){

		int read = fscanf(inputFile, "%d\n", &window[windowPos]);
		windowPos++;

		if(read != 1){
			break;
		}

		int curSum = sum(window, 3);
		if(prevSum < curSum){
			
			timesBigger++;			

		}

		prevSum = curSum;

		if(windowPos == 3){

			windowPos = 0;

		}	

	}	

	fclose(inputFile);	
	return timesBigger;	

}


int main(int argc, char** argv){

	if(argc != 2){

		printf("Usage: %s <input File>\n", argv[0]);
		return 1;

	}

	int result = directCompare(argv[1]);

	printf("Window was %d times bigger than previous one\n", result);

	return 0;
}
