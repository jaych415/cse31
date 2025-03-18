#include <stdio.h>

int read_values(double *sum) {  // Changed to pointer
    int values = 0, input = 0;
    *sum = 0;  // Use pointer to modify the actual sum variable
    
    printf("Enter input values (enter 0 to finish):\n");
    scanf("%d", &input);
    
    while(input != 0) {
        values++;
        *sum += input;  // Use pointer to modify sum
        scanf("%d", &input);  // Added & operator
    }
    
    return values;
}

int main() {
    double sum = 0;
    int values;
    
    values = read_values(&sum);  // Pass address of sum
    
    if (values > 0) {
        printf("\nAverage: %g\n", sum/values);
    } else {
        printf("\nNo values entered.\n");
    }
    
    return 0;
}