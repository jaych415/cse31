#include <stdio.h>
#include <stdlib.h>

int size;
int evenCount = 0, oddCount = 0;
int *arr;
int *arr_even;
int *arr_odd;
char *str1 = "Original array's contents: ";
char *str2 = "Contents of new array containing even elements from original: ";
char *str3 = "Contents of new array containing odd elements from original: ";

void printArr(int *a, int size, char *prompt) {
   printf("%s", prompt);
   if (size == 0) {
       printf("empty\n");
       return;
   }
   for (int i = 0; i < size; i++) {
       printf("%d ", a[i]);
   }
   printf("\n");
}

void arrCopy() {
   evenCount = 0;
   oddCount = 0;
   for (int i = 0; i < size; i++) {
       if (arr[i] % 2 == 0) {
           evenCount++;
       } else {
           oddCount++;
       }
   }

   arr_even = (int *)malloc(evenCount * sizeof(int));
   arr_odd = (int *)malloc(oddCount * sizeof(int));

   int evenIndex = 0, oddIndex = 0;
   for (int i = 0; i < size; i++) {
       if (arr[i] % 2 == 0) {
           arr_even[evenIndex++] = arr[i];
       } else {
           arr_odd[oddIndex++] = arr[i];
       }
   }
}

int main() {
   printf("Enter the size of array you wish to create: ");
   scanf("%d", &size);

   if (size > 0) {
       arr = (int *)malloc(size * sizeof(int));
       if (arr == NULL) {
           printf("Memory allocation failed!\n");
           return 1;
       }

       for (int i = 0; i < size; i++) {
           printf("Enter array element #%d: ", i + 1);
           scanf("%d", &arr[i]);
       }
   }

   printArr(arr, size, str1);
   arrCopy();

   printArr(arr_even, evenCount, str2);
   printArr(arr_odd, oddCount, str3);
   printf("\n");

   if (size > 0) {
       free(arr);
       free(arr_even);
       free(arr_odd);
   }

   return 0;
}
