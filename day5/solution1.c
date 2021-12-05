#include <stdio.h>
#include <stdlib.h>

#define LINES_IN_FILE 500 


void directRead(char* filename, int arr[LINES_IN_FILE][4]){

	FILE* inputFile = fopen(filename, "r");
	
	if(!inputFile){

		printf("[directRead]: Could not open file %s!\n", filename);
		return;
	}

	char line[30];

	for(int i = 0; i < LINES_IN_FILE; i++){

		char* test = fgets(line, 30, inputFile);
		
		if(test == NULL){
			return;
		}

		for(int linepos = 0; linepos < 30; linepos++){

			char c = line[linepos];
		
			if(c == '\n'){
				break;
			}
	
			if( (int) c < 58 && (int) c > 47){

				line[linepos] = c;
			}else{
				line[linepos] = ' ';
			}
		}		

		line[29] = '\0';

		int read = sscanf(line, "%d %d %d %d\n", &arr[i][0], &arr[i][1], &arr[i][2], &arr[i][3]);			
		
		if(read != 4){
			printf("[directRead]: Error occured when reading values from file\n");
			return;	
		}
	}

	fclose(inputFile);
}


int min(int a, int b){

	if(a > b){
		return b;
	}
	return a;
}


int max(int a, int b){

	if(a > b){
		return a;
	}
	return b;
}


void printMap(int** map, int xsize, int ysize){


	printf("\n\nPrinting Map: \n");

	for(int y = 0; y <= ysize; y++){

		int* line = map[y];

		for(int x = 0; x <= xsize; x++){

			int value = line[x];			

			if(value == 0){
				printf("*");
				continue;
			}
		
			printf("%d", value);
		}

		printf("\n");
	
	}
}

void freeMap(int** map, int ysize){


	for(int i = 0; i <= ysize; i++){

		free(map[i]);
	}
	
	free(map);
}


int countCrossedLines(int** map, int xsize, int ysize){

	int count = 0;

	for(int y = 0; y <= ysize; y++){

		int* line = map[y];

		for(int x = 0; x <= xsize; x++){

			int n = line[x];
			if(n >= 2){

				count++;
			}
		}
	}

	return count;
}


int makeMap(int arr[LINES_IN_FILE][4]){


	int maxX = 0;
	int maxY = 0;

	int maxCross = 0;

	for(int pos = 0; pos < LINES_IN_FILE; pos++){

		int *vector = arr[pos];
		
		if(vector[0] > maxX){

			maxX = vector[0];
		}
	
		if(vector[1] > maxY){

			maxY = vector[1];
		}


		if(vector[2] > maxX){

			maxX = vector[2];
		}
	
		if(vector[3] > maxY){

			maxY = vector[3];
		}
	}

	printf("Size: %dx%d\n", maxX, maxY);

	int** map = malloc(sizeof(int*) * (maxY + 1));
	
	for(int y = 0; y <= maxY; y++){

		map[y] = calloc(maxX + 1, sizeof(int));

	}
	
	for(int cur = 0; cur < LINES_IN_FILE; cur++){

		int *vector = arr[cur];

		
		// check if horizontal or vertical
		if(vector[0] == vector[2] || vector[1] == vector[3]){

			// vertical 
			if( vector[0] == vector[2] ){

				int upperY = max(vector[1], vector[3]);
				int lowerY = min(vector[1], vector[3]);
				int xpos = vector[0];				

				for(int posy = lowerY; posy <= upperY; posy++){

					int* line = map[posy];

					line[xpos] += 1;
					int value = line[xpos];
			
					if(value > maxCross){

						maxCross = value;
						printf("Found a more dangerous place, with value %d: (%d,%d)\n", value, xpos, posy);				
		
					}	
				} 				
			}
		
			// horizontal	
			if( vector[1] == vector[3] ){

				int upperX = max(vector[0], vector[2]);
				int lowerX = min(vector[0], vector[2]);
				int ypos = vector[1];				

				int* line = map[ypos];

				for(int posx = lowerX; posx <= upperX; posx++){

					line[posx] += 1;
					int value = line[posx];
	
					if(value > maxCross){

						maxCross = value;
						printf("Found a more dangerous place, with value %d: (%d,%d)\n", value, posx, ypos);				
		
					}	
				} 				
			}
		}
	}

	printMap(map, maxX, maxY);
	int crossed = countCrossedLines(map, maxX, maxY);

	freeMap(map, maxY);
	return crossed;
}

void printVents(int arr[LINES_IN_FILE][4]){

	for(int i = 0; i < LINES_IN_FILE; i++){

		printf("Vent #%d: %d,%d -> %d,%d\n", i, arr[i][0], arr[i][1], arr[i][2], arr[i][3]);
	}
}

int main(int argc, char** argv){

	if(argc != 2){

		printf("Usage: %s <input file>\n", argv[0]);
		return 1;
	}


	int vents[LINES_IN_FILE][4];

	directRead(argv[1], vents);
	printVents(vents);		
	int twice = makeMap(vents);	
	
	printf("Crossed twice %d times\n", twice);


	return 0;
}
