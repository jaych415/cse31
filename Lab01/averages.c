#include <stdio.h>

int sum_of_digits(int num) {
    int sum = 0;
    num = (num < 0) ? -num : num; 
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

//This function calculates the sum of the digits of an integer. If the num is negative, it gets converted to a positive number. 
//It extracts digits using % 10, adds them to sum, and removes the last digit using /= 10. 
//after that, it returns the sum of the digits.


int main() {
    int num, count = 1;
    int sum_even = 0, sum_odd = 0;
    int count_even = 0, count_odd = 0;

    while (1) {
        printf("Enter the %d%s value: ", count, (count == 1) ? "st" : (count == 2) ? "nd" : (count == 3) ? "rd" : "th");
        scanf("%d", &num);

        if (num == 0) break; 

        int digit_sum = sum_of_digits(num);

        if (digit_sum % 2 == 0) {
            sum_even += num;
            count_even++;
        } else {
            sum_odd += num;
            count_odd++;
        }

        count++;
    }

    if (count_even > 0) {
        printf("Average of input values whose digits sum up to an even number: %.2f\n", (float)sum_even / count_even);
    }
    if (count_odd > 0) {
        printf("Average of input values whose digits sum up to an odd number: %.2f\n", (float)sum_odd / count_odd);
    }
    if (count_even == 0 && count_odd == 0) {
        printf("There is no average to compute.\n");
    }

    return 0;
}

//Runs an infinite loop to continuously take input
//The printf statement properly formats ordinal suffixes (st, nd, rd, th).
//scanf("%d", &num); reads an integer from the user.
//If num == 0, the loop exits using break.