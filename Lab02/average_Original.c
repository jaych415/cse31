#include <stdio.h>
/*
* Read a set of values from the user.
* Store the sum in the sum variable and return the number of values read.
*/
/*
/gcc -g average_original.c -o average_original
/lldb average_original 
/run
/breakpoint set --file average_original.c --line 25 
* You CANNOT declare any global variables.
* DO NOT change the definition of the read_values function when it comes to
* adding/removing function parameters, or changing its return type. You may,
* however, modify the single function parameter and the body of the function if
* you wish.
* Use GDB or LLDB to discover and fix errors.  //14: *sum, *sum 16, *sum 21, &input 22, &sum 29
*/
int read_values(double *sum) {
int values = 0, input = 0;
*sum = 0;
printf("Enter input values (enter 0 to finish):\n");
scanf("%d", &input);
while(input != 0) {
values++;
*sum += input;
scanf("%d", &input);
}
return values;
}
int main() {
double sum = 0;
int values;
values = read_values(&sum);
printf("\nAverage: %g\n", sum/values); // Hint: How do we ensure that sum is
//updated here
// AFTER read_values() manipulates it?
// Make sure to use GDB or LLDB for this.
return 0;
}
