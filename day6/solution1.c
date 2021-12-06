#include <stdio.h>
#include <stdlib.h>

#define VALUES_IN_FILE 5 

typedef struct _element element;


struct _element{
	
	element* prev;
	int value;
	element* next;

};


typedef struct{

	int size;
	element* first;
	element* last;

} list;

void addElementToList(int value, list* numberList){

	element* newElement = malloc(sizeof(element));
		
	newElement->value = value;
	

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

void deleteList(list* toDelete){

	element* firstElement = toDelete->first;

	while(firstElement){
		deleteElementFromList(firstElement, toDelete);
		firstElement = toDelete->first;
	}

}


void directRead(char* filename, list* lanternList){

	   	FILE* inputFile = fopen(filename, "r");
		int cycle;	

		for(int i = 0; i < VALUES_IN_FILE - 1; i++){

			fscanf(inputFile,"%d,", &cycle);
			addElementToList(cycle, lanternList); 

		}
	
		fscanf(inputFile, "%d", &cycle);
		addElementToList(cycle, lanternList);		

		fclose(inputFile);
}

void printList(list* listToPrint, int maxElems){

	int listLength = listToPrint->size;

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

		printf("%d  ", nextElement->value);

		if(y > 75){
			
			printf("\n");
			y = 0;
		}

		nextElement = nextElement->next;		
		maxElems--;

	}

	printf("\n\n");
}

void simulateGrowth(list* lanterns, int cycles){

	for(int cycle = 0; cycle < cycles; cycle++){

		int num = lanterns->size;
		element* cur = lanterns->first;

		for(int i = 0; i < num; i++){

			int value = cur->value;
			
			if(value == 0){
				
				cur->value = 6;
				addElementToList(8, lanterns);
				cur = cur->next;
				continue;				
			}
		
			cur->value = value - 1;
			cur = cur->next;
		}
	
		printf("After the %dth cycle, there are %d lanterns!", cycle + 1, lanterns->size);
		printList(lanterns, 1000);
	}
}

int main(int argc, char** argv){

	if(argc != 2){

		printf("Usage %s <input file>\n", argv[0]);
		return 1;

	}

	list lanterns;
	lanterns.first = NULL;
	lanterns.last = NULL;
	lanterns.size = 0;	


	directRead(argv[1], &lanterns);
	simulateGrowth(&lanterns, 256);

	deleteList(&lanterns);

	return 0;

}

