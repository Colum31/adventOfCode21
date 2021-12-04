#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct{
	
	int moves;
	int board[25];
	int hits[10];
	int id;

} boardInfo;


int readInputNumbers(char* filename, int* boardPosition, int** arr){


	FILE* inputFile = fopen(filename, "r");
	int firstBoardPos = 0;


	if(!inputFile){
		
		printf("[readInputNumbers]: Could not open file %s!\n", filename);
		return 0;
	}

	int numbers = 1;
	char c = ' ';
		
	while(c != '\n'){

		fread(&c, 1, 1, inputFile);

		if(c == ','){
	
			numbers++;
		}
	}
	
	firstBoardPos = ftell(inputFile) + 1;

	int* inputNumbers = malloc(numbers * sizeof(int));
	fseek(inputFile, 0, SEEK_SET);

	int read;

	for(int i = 0; i < numbers - 1; i++){

		read = fscanf(inputFile, "%d,", &inputNumbers[i]);
		
		if(read != 1){

			printf("[readInputNumbers]: WARNING: Failed to read %d numbers, expected to read %d numbers!\n", i, numbers);
			return 0;
		}		
	}

	read = fscanf(inputFile, "%d", &inputNumbers[numbers - 1]);	

	if(read != 1){

		printf("[readInputNumbers]: WARNING: Failed to read %d numbers, expected to read %d numbers!\n", numbers, numbers);
		return 0;
	}		

	*boardPosition = firstBoardPos;
	fclose(inputFile);	
	*arr = inputNumbers;
	return numbers;

}


void printIntArray(int* array, int len){
	
	printf("[");

	for(int i = 0; i < len - 1; i++){

		printf("%d, ", array[i]);

	}

	printf("%d]", array[len - 1]);

}

void printBoard(int* board){

	for(int i = 0; i < 5; i++){
		
		printIntArray(board + i * 5, 5);
		printf("\n");
	}
}


int parseLine(char* line, int* arr, int pos){

	int read = sscanf(line, "%d %d %d %d %d \n", &arr[pos], &arr[pos + 1], &arr[pos + 2] , &arr[pos + 3], &arr[pos + 4]);
	return read;
}


int readBoardFromFile(char* filename, int filepos, int* board){

	FILE* inputFile = fopen(filename, "r");

	char line[16];

	fseek(inputFile, filepos, SEEK_SET);
	
	for(int i = 0; i < 5; i++){
		char* ptr = fgets(line, 16, inputFile);
		
		if(ptr != line){
		
			fclose(inputFile);
			return 0;
		}

		int read = parseLine(line, board, i * 5);

		if(read != 5){
			
			fclose(inputFile);
			printf("[readBoardFromFile]: FATAL error: line %s supposed to be valid, but sscanf could not extract 5 values. Exiting!\n", line);
			return 0;

		}
	}

	int pos = ftell(inputFile) + 1;
	fclose(inputFile);	

	return pos;	
}

int searchArray(int* arr, int len, int value){

	for(int i = 0; i < len; i++){

		if(arr[i] == value){

			return i;
		}
	}

	return -1;
}

void initIntArray(int* arr, int len){

	for(int i = 0; i < len; i++){
		arr[i] = 0;
	}
}

int sumBoard(int* board){
	
	int sum = 0;

	for(int i = 0; i < 25; i++){

		int n = board[i];
		
		if(n != -1){
			sum += n;
		}
	}

	return sum;

}


int solveBoard(boardInfo* board, int* inputNumbers, int limit){

	int* boardArray = board->board;
	int* resultArray = board->hits;

	initIntArray(resultArray, 10);

	for(int i = 0; i < limit; i++){
		
		int result = searchArray(boardArray, 25, inputNumbers[i]);

		if(result >= 0){
	
			boardArray[result] = -1;
			
			resultArray[result % 5] += 1;
			resultArray[result / 5 + 5] += 1;

			if( resultArray[result / 5 + 5] == 5 || resultArray[result % 5] == 5){

				board->moves = i;
				board->id = sumBoard(boardArray) * inputNumbers[i];
				return i;
			}
		}
	}

	return limit + 1;

}



int main(int argc, char** argv){

	if(argc != 2){

		printf("Usage: %s <input file>\n", argv[0]);
		return 1;

	}
	
	int* numbers = NULL;
	int boardPosition;

	int inputNumbers = readInputNumbers(argv[1], &boardPosition, &numbers);

	printf("Found %d input numbers!\n", inputNumbers);
	printIntArray(numbers, inputNumbers);
	printf("\n\n");
	
	boardInfo bestBoard;	
	int fastest = inputNumbers;

	int counter = 1;
	
	while(1){

		boardInfo curBoard;
		boardPosition  = readBoardFromFile(argv[1], boardPosition, curBoard.board);
		
		if(boardPosition == 0){
			break;
		}

		
		int moves = solveBoard(&curBoard, numbers, fastest);

		printf("\n\nBoard #%d:", counter);

		if(moves > fastest){

			printf(" Did not solve in under %d moves\n", fastest);

		}else{
			
			printf(" Solved in %d moves. Setting upper limit from %d to %d\n", moves, fastest, moves);
			bestBoard = curBoard;
			fastest = moves;
		}

		printBoard(curBoard.board);
		counter++;
	}	

	printf("\n\n\nBest board: (solved in %d, sum: %d)\n", bestBoard.moves, bestBoard.id);
	printBoard(bestBoard.board);


	free(numbers);
	return 0;


}
