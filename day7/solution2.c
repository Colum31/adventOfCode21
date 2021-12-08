#include <stdio.h>
#include <stdlib.h>


int findPosWithSmallestValue(int* arr, int size){

    int smallestValue = arr[0];
    int smallestPos = 0;

    for(int i = 0; i < size; i++){

        if(arr[i] < smallestValue){
            smallestValue = arr[i];
            smallestPos = i;
        }
    }

    return smallestPos;
}

int smallestArrayElem(int* arr, int size){

int smallest = arr[0];

    for(int i = 0; i < size; i++){

        if(smallest > arr[i]){
            smallest = arr[i];
        }
    }

    return smallest;
}

int gauss(int n){

    return (n*n + n) / 2;
}


int biggestArrayElem(int* arr, int size){

    int biggest = 0;

    for(int i = 0; i < size; i++){

        if(biggest < arr[i]){
            biggest = arr[i];
        }
    }

    return biggest;
}

int countCommaSeperatedInts(char* filename){

    FILE* inputFile = fopen(filename, "r");

    if(inputFile == NULL){
        printf("Could not open %s!\n", filename);
        exit(2);
    }

    char c = ' ';
    int counter = 1;

    while(c != '\n'){
        fread(&c, 1, 1, inputFile);

        if(c == ','){
            counter++;
        }
    }

    fclose(inputFile);
    return counter;
}

void printIntArray(int* arr, int size){

    for(int i = 0; i < size - 1; i++){
        printf("%d,", arr[i]);
    }

    printf("%d\n", arr[size -1]);

}

int* directRead(char* filename, int* retSize){

    int size = countCommaSeperatedInts(filename);
    int* arr = malloc(size * sizeof(int));

    FILE* inputFile = fopen(filename, "r");

    for(int i = 0; i < size - 1; i++){

        fscanf(inputFile, "%d,", &arr[i]);

    }

    fscanf(inputFile, "%d,", &arr[size - 1]);

    fclose(inputFile);

    *retSize = size;
    return arr;
}

int calcMinFuel(int* arr, int inputSize){

    int calcSize = biggestArrayElem(arr, inputSize) + 1;
    int* calcArray = calloc(calcSize, sizeof(int));

    for(int i = 0; i < inputSize; i++){

        int index = arr[i];

        for(int j = 0; j < calcSize; j++){

            int diff = j - index;
            calcArray[j] += gauss(abs(diff)); 

        }

        printIntArray(calcArray, calcSize);
    }

    int fuel = smallestArrayElem(calcArray, calcSize);
    int position = findPosWithSmallestValue(calcArray, calcSize);

    printf("Best option: Goto position %d, using %d fuel!\n", position, fuel);
    free(calcArray);

    return fuel;
}

int main(int argc, char** argv){

    if(argc != 2){

        printf("Usage: %s <input file>\n", argv[0]);
        return 1;
    }

    int size;
    int* array = directRead(argv[1], &size);
    printIntArray(array, size);

    calcMinFuel(array, size);

    free(array);
    return 0;

}