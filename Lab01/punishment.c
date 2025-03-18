#include <stdio.h>

int main() {
    int repetitionCount, typoLine;
    
    printf("Enter the repetition count for the punishment phrase: ");
    while (scanf("%d", &repetitionCount) != 1 || repetitionCount <= 0) {
        printf("You entered an invalid value for the repetition count! Please re-enter: ");
        while (getchar() != '\n'); 
    }
    
    printf("Enter the line where you want to insert the typo: ");
    while (scanf("%d", &typoLine) != 1 || typoLine <= 0 || typoLine > repetitionCount) {
        printf("You entered an invalid value for the typo placement! Please re-enter: ");
    }
    
    for (int i = 1; i <= repetitionCount; i++) {
        if (i == typoLine)
            printf("Cading wiht is C avesone!\n");
        else
            printf("Coding with C is awesome!\n");
    }

    return 0;
}