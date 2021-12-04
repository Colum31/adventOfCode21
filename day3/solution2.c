#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUMBERWIDTH 12 

typedef struct _element element;


struct _element{
	
	element* prev;
	char value[NUMBERWIDTH + 1];
	element* next;

};


typedef struct{

	int size;
	element* first;
	element* last;

} list;


int convertToInt(char* line){

	int result = 0;

	for(int i = 0; i < NUMBERWIDTH; i++){

		if(line[i] == '1'){
			result += (int) pow(2, NUMBERWIDTH - 1 - i);
		}
	}
	
	return result;

}

void addElementToList(char* line, list* numberList){

	element* newElement = malloc(sizeof(element));
		
	strncpy(newElement->value, line, NUMBERWIDTH + 1);
	

	if(!numberList->first){

		numberList->first = newElement;
		numberList->last = newElement;		

		numberList->size = 1;
		newElement->next = NULL;
		newElement->prev = NULL;				

		return;
	
	}

	element* lastElement = numberList->last;
	
	lastElement->next = newElement;
	numberList->size += 1;
	numberList->last = newElement;
	newElement->next = NULL;
	newElement->prev = lastElement;

}


void deleteElementFromList(element* toDelete, list* numberList){

	element* nextElement = toDelete->next;

	if(toDelete == numberList->first){

		free(toDelete);
		numberList->size -= 1;
		numberList->first = nextElement;

		if(!nextElement){

			numberList->last = NULL;
			return;

		}

		nextElement->prev = NULL;

		return;
	}

	element* prevElement = toDelete->prev;
	
	if(toDelete == numberList->last){

		free(toDelete);
		prevElement->next = NULL;
		numberList->last = prevElement;
		numberList->size -= 1;
		return;
	}

	free(toDelete);
	prevElement->next = nextElement;
	nextElement->prev = prevElement;
	numberList->size -= 1;

}

list* cloneList(list* oldList){

	list* newList = malloc(sizeof(list));
	newList->size = 0;
	newList->first = NULL;
	newList->last = NULL;	

	element* nextElement = oldList->first;
	
	while(nextElement){

		addElementToList(nextElement->value, newList);
		nextElement = nextElement->next;		
	}

	return newList;
}


void deleteList(list* toDelete){

	element* firstElement = toDelete->first;

	while(firstElement){
		deleteElementFromList(firstElement, toDelete);
		firstElement = toDelete->first;
	}

	free(toDelete);
}


void countBits(int* bits, list* numberList){

	int listLength = numberList->size;
	element* next = numberList->first;
	
	for(int i = 0; i < listLength; i++){

		char* line = next->value;


		for(int pos = 0; pos < NUMBERWIDTH; pos++){
	
			if(line[pos] == '1'){
		
				bits[pos] += 1;
			}
		}

		next = next->next;

	}
}


void directRead(char* filename, list* numberList, int* totalBits){

	FILE* inputFile = fopen(filename, "r");

	if(!inputFile){

		printf("Could not open file %s!\n", filename);
		return;
	}

	char line[NUMBERWIDTH + 1];

	int lines = 0;

	while(1){

		int read = fscanf(inputFile, "%s\n", line);	

		if(!(read == 1)){

			break;
		}

		addElementToList(line, numberList);

		lines++;

	}
	
	*totalBits = lines;
	fclose(inputFile);
}

void initIntArray(int *array, int len){

	for(int i = 0; i < len; i++){

		array[i] = 0;
	}

}


void printIntArray(int* array, int len){
	
	printf("[");

	for(int i = 0; i < len - 1; i++){

		printf("%d, ", array[i]);

	}

	printf("%d]", array[len - 1]);

}



void printList(list* listToPrint, int maxElems, int pos, char* formatStr, int* bits){

	int listLength = listToPrint->size;

	printf("[Run %d, %d Elements remaining] Formatstring: (%s) Bits: ",pos, listLength, formatStr);
	printIntArray(bits, NUMBERWIDTH);	
	printf(" of %d values",listToPrint->size);
	if(listLength > maxElems){

		printf( "\nList to long: Printing only first %d Elements:", maxElems);
		}

	element* nextElement = listToPrint->first;
	int y = 0;

	printf("\n");
	
	while(maxElems >= 0){
		
		y++;

		if(!nextElement){
			break;
		}

		printf("%s  ", nextElement->value);

		if(y > 9){
			
			printf("\n");
			y = 0;
		}

		nextElement = nextElement->next;		
		maxElems--;

	}

	printf("\n\n");
}


char calcFilter(int mode, int *bits, int totalBits, int pos){

	char filter;	
	int bitsAtPos = bits[pos];

	if(bitsAtPos > totalBits - bitsAtPos){
	
		if(mode == 1){
			filter = '1';

		}else{
			filter = '0';
			}

	}
	else if(bitsAtPos < totalBits - bitsAtPos){

			if(mode == 1){
				filter = '0';
	
			}else{
				filter = '1';

				}
	}
	else{

			printf("Equal amounts of bits in %d position!\n", pos);
			if(mode == 1){
				filter = '1';
			}else{
				filter = '0';
			}	
	}

	return filter;

}


void filterElements(int mode, list* numberList, char* res){

	int bits[NUMBERWIDTH];
	int pos = 0;
	char filter;
	char formatStr[NUMBERWIDTH + 1];

	for(int i = 0; i < NUMBERWIDTH; i++){

		formatStr[i] = '*';
	}

	formatStr[NUMBERWIDTH] = '\0';

	while(numberList->size != 1){

		if(pos == NUMBERWIDTH){
			break;
		}

		initIntArray(bits, NUMBERWIDTH);
		countBits(bits, numberList);

		filter = calcFilter(mode, bits, numberList->size, pos);
		
		printList(numberList, 200, pos, formatStr, bits);
		element* nextElement = numberList->first;
	
		while(nextElement){

			char* value = nextElement->value;
			
			if(value[pos] != filter){
		
				element* tmp = nextElement;
				nextElement = nextElement->next;
			
				deleteElementFromList(tmp, numberList);				
				continue;
			}			
			
			nextElement = nextElement->next;

		}

		formatStr[pos] = filter;
		pos++;
	}

	if(numberList->size != 1){

		printf("Error: After filtering the list, no element remains!\n");
		res = NULL;

	}else{
		
		printf("SUCCESS: Only one Element remains:\n");
		printList(numberList, 200, pos, formatStr, bits);
		strncpy(res, (numberList->first)->value, NUMBERWIDTH + 1); 

	}


}


int main(int argc, char** argv){

	if(argc != 2){

		printf("Usage: %s <input file>\n", argv[0]);
		return 1;
	}

	list* numberList = malloc(sizeof(list));
	int totalBits;

	numberList->size = 0;
	numberList->first = NULL;
	numberList->last = NULL;

	directRead(argv[1], numberList, &totalBits);

	char result[2][NUMBERWIDTH + 1];  
	
	list* cpy = cloneList(numberList);

	filterElements(1, cpy, result[0]);
	deleteList(cpy);

	printf("\n\n\n");	

	cpy = cloneList(numberList);
	filterElements(0, cpy, result[1]); 	
	deleteList(cpy);

	printf("O2 Value: %d, CO2 Value: %d\n", convertToInt(result[0]), convertToInt(result[1]) );
	deleteList(numberList);
}
