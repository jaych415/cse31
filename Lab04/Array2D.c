#include <stdio.h>
#include <stdlib.h>

void printArray(int**, int);

int main() {
    int i = 0, j = 0, n = 5;
    int **arr = (int**)malloc(n * sizeof(int*)); // Line #8
    
    // (3) Add code to complete allocating and initializing the 2-D array here
    for (i = 0; i < n; i++) {
        *(arr + i) = (int*)malloc(n * sizeof(int));
        for (j = 0; j < n; j++) {
            *(*(arr + i) + j) = 0; // Initialize all elements to 0
        }
    }
    
    // This will print out your array
    printArray(arr, n);
    
    // (6) Add code to make arr a diagonal matrix
    for (i = 0; i < n; i++) {
        *(*(arr + i) + i) = 1; // Set diagonal elements to 1
    }
    
    // (7) Call printArray to print array
    printf("\nDiagonal Matrix:\n");
    printArray(arr, n);
    
    // Free allocated memory
    for (i = 0; i < n; i++) {
        free(*(arr + i));
    }
    free(arr);
    
    return 0;
}

void printArray(int **array, int size) {
    // (5) Implement printArray
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%d ", *(*(array + i) + j));
        }
        printf("\n");
    }
}