#include <stdio.h>
#include <stdlib.h>

int* bubbleSort(int arr[], int n) {
    int temp, i = 0, j = 0;
    int *s_arr = (int *) malloc(n * sizeof(int));

    // Copy arr to s_arr
    for(i = 0; i < n; i++)
        s_arr[i] = arr[i];

    // Sorting using array notations
    // Comment this when implementing pointer version.
    /*
    for (i = 0; i < n - 1; i++) {
        for(j = 0; j < n - 1; j++) {
            if(s_arr[j] > s_arr[j + 1]) {
                temp = s_arr[j + 1];
                s_arr[j + 1] = s_arr[j];
                s_arr[j] = temp;
            }
        }
    }
    */

   //This code reads an array from user input, then sorts it using bubble sort implemented with pointer arithmetic 
   //rather than array notation. After sorting, it displays both the original and sorted arrays. It then performs a 
   //recursive binary search, again using pointer arithmetic, to locate a user-specified key within the sorted array and prints the result.

    // Sorting using pointer notations. i.e. you cannot use "[]"!
    // Your code goes here...
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1; j++) {
            if (*(s_arr + j) > *(s_arr + j + 1)) {
                temp = *(s_arr + j + 1);
                *(s_arr + j + 1) = *(s_arr + j);
                *(s_arr + j) = temp;
            }
        }
    }

    return s_arr;
}

void printArray(int arr[], int n) {
    int i = 0;
    printf("[");
    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("]\n");
}

int bSearch(int *arr, int a, int b, int key) {
    // Binary search function. arr is the array, key is the value to search for, a and b are the boundaries of arr to be searched within.
    // You must use pointer notations. i.e. no "[]"
    // Your code goes here:
    
    // Base case: if the search space is empty
    if (a > b) {
        return -1; // Key not found
    }
    
    // Calculate middle index
    int mid = a + (b - a) / 2;
    
    // If key is found at middle point
    if (*(arr + mid) == key) {
        return mid;
    }
    
    // If key is smaller than middle element, search in left subarray
    if (*(arr + mid) > key) {
        return bSearch(arr, a, mid - 1, key);
    }
    
    // If key is greater than middle element, search in right subarray
    return bSearch(arr, mid + 1, b, key);
}

//The binary search function (bSearch) is the key component here that identifies the correct index.
 //It calculates the middle index using pointer arithmetic (e.g., *(arr + mid)) and recursively searches 
 //the appropriate subarray until the key is found, returning the correct index. This returned index is then 
 //stored in result in the main function and displayed using a printf statement.

int main() {

    int i = 0, size = 0, key = 0, result = 0;
    int *array, *sorted;

    printf("How big is your array? ");
    scanf("%d", &size);
    array = (int *) malloc(size * sizeof(int));

    for(i = 0; i < size; i++) {
        printf("Please enter array[%d]: ", i);
        scanf("%d", &array[i]);
    }

    printf("Please wait while I sort your numbers...\n");
    sorted = bubbleSort(array, size);
    printf("Here is your original array:\n");
    printArray(array, size);
    printf("Here is your SORTED array: \n");
    printArray(sorted, size);
    printf("What number are you looking for? ");
    scanf("%d", &key);
    printf("OK, let me see if I can find a \"%d\" in the array...\n", key);
    result = bSearch(sorted, 0, size-1, key);
    if(result != -1)
        printf("Got it! A \"%d\" is at index %d.\n", key, result);
    else
        printf("I'm sorry, \"%d\" cannot be found in the array.\n", key);

    return 0;
}