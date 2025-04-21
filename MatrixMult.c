#include <stdio.h>
#include <stdlib.h>

/*
 * This function multiplies two square matrices by first dynamically allocating memory for the result matrix.
 * It initializes each element of the result matrix to zero and then computes each element as the sum of products of corresponding elements from the input matrices.
 * Finally, it returns the pointer to the newly allocated result matrix containing the multiplication result.
 */

int** matMult(int **a, int **b, int size) {
    // Allocate memory for the result matrix
    int **result = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        *(result + i) = (int *)malloc(size * sizeof(int));
    }

    // Perform matrix multiplication
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(result + i) + j) = 0;
            for (int k = 0; k < size; k++) {
                *(*(result + i) + j) += *(*(a + i) + k) * *(*(b + k) + j);
            }
        }
    }

    return result;
}

/*
 * This function prints a square 2D array (matrix) to the console.
 * It iterates through each row and each column, printing each integer value followed by a space.
 * After printing all columns in a row, it outputs a newline to format the output as a matrix.
 */

void printArray(int **arr, int n) {
    // Print each element of the 2D array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

/*
 * The main function dynamically allocates two 3x3 matrices (matA and matB) and initializes them with sample values.
 * It prints both matrices using the printArray function, multiplies them using the matMult function, and then prints the resulting matrix.
 * Finally, the function returns 0, indicating successful program execution.
 */


int main() {
    int n = 3; // Example size of 3x3 matrices
    
    // (1) Define 2 (n x n) arrays (matrices) using malloc
    int **matA = (int **)malloc(n * sizeof(int *));
    int **matB = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        *(matA + i) = (int *)malloc(n * sizeof(int));
        *(matB + i) = (int *)malloc(n * sizeof(int));
    }

    // Initialize matrices with some sample values
    int count1 = 1, count2 = 9;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(*(matA + i) + j) = count1++;
            *(*(matB + i) + j) = count2--;
        }
    }

    // (3) Call printArray to print out the 2 arrays
    printf("Matrix A:\n");
    printArray(matA, n);
    printf("\nMatrix B:\n");
    printArray(matB, n);

    // (5) Call matMult to multiply the 2 arrays
    int **matC = matMult(matA, matB, n);

    // (6) Call printArray to print out resulting array
    printf("\nResulting Matrix C:\n");
    printArray(matC, n);

    return 0;
}