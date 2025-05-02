#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char **arr);
void searchPuzzle(char **arr, char *word);
int bSize;

// Main function, DO NOT MODIFY
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);

    // Allocate space for the puzzle block and the word to be searched
    char **block = (char **)malloc(bSize * sizeof(char *));
    char *word = (char *)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for (i = 0; i < bSize; i++)
    {
        *(block + i) = (char *)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j)
        {
            fscanf(fptr, "%c ", *(block + i) + j);
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);

    for (int i = 0; *(word + i) != '\0'; i++)
    {
        char c = *(word + i);
        if (c >= 'a' && c <= 'z')
        {
            *(word + i) -= 32;
        }
    }

    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);

    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);

    return 0;
}

void printPuzzle(char **arr)
{
    // This function will print out the complete puzzle grid (arr).
    // It must produce the output in the SAME format as the samples
    // in the instructions.
    // Your implementation here...

    for (int i = 0; i < bSize; i++)
    {
        for (int j = 0; j < bSize; j++)
        {
            char *row = *(arr + i);
            printf("%c", *(row + j));

            if (j != bSize - 1)
            {
                printf(" ");
            }
        }

        printf("\n");
    }

    printf("\n");
}

int search(char **arr, char ***searchPath, char *word, int wordIdx, int i, int j)
{
    char buffer[10];

    // convert current step number to a string
    sprintf(buffer, "%d", wordIdx + 1);

    // append current step number to the string at search path (i, j)
    char *cell = *(*(searchPath + i) + j);
    if (*cell == '\0')
    {
        strcpy(cell, buffer);
    }
    else
    {
        char temp[50];
        strcpy(temp, cell);
        strcpy(cell, buffer);
        strcat(cell, temp);
    }

    // code to track codepath
    int wordLen = strlen(word);
    if (wordIdx == wordLen - 1)
    {
        return 1;
    }

    char targetChar = *(word + wordIdx + 1);

    // recursive search for all 8 directions.
    // order: UP, RIGHT, DOWN-RIGHT, UP-LEFT, LEFT, DOWN, DOWN-LEFT, UP-RIGHT

    // UP
    if (i > 0)
    {
        char up = *(*(arr + i - 1) + j);
        if (up == targetChar && search(arr, searchPath, word, wordIdx + 1, i - 1, j))
        {
            return 1;
        }
    }

    // RIGHT
    if (j + 1 < bSize)
    {
        char right = *(*(arr + i) + j + 1);
        if (right == targetChar && search(arr, searchPath, word, wordIdx + 1, i, j + 1))
        {
            return 1;
        }
    }

    // DOWN-RIGHT
    if (i + 1 < bSize && j + 1 < bSize)
    {
        char bottomRight = *(*(arr + i + 1) + j + 1);
        if (bottomRight == targetChar && search(arr, searchPath, word, wordIdx + 1, i + 1, j + 1))
        {
            return 1;
        }
    }

    // UP-LEFT
    if (i > 0 && j > 0)
    {
        char topLeft = *(*(arr + i - 1) + j - 1);
        if (topLeft == targetChar && search(arr, searchPath, word, wordIdx + 1, i - 1, j - 1))
        {
            return 1;
        }
    }

    // LEFT
    if (j > 0)
    {
        char left = *(*(arr + i) + j - 1);
        if (left == targetChar && search(arr, searchPath, word, wordIdx + 1, i, j - 1))
        {
            return 1;
        }
    }

    // DOWN
    if (i + 1 < bSize)
    {
        char down = *(*(arr + i + 1) + j);
        if (down == targetChar && search(arr, searchPath, word, wordIdx + 1, i + 1, j))
        {
            return 1;
        }
    }

    // DOWN-LEFT
    if (i + 1 < bSize && j > 0)
    {
        char bottomLeft = *(*(arr + i + 1) + j - 1);
        if (bottomLeft == targetChar && search(arr, searchPath, word, wordIdx + 1, i + 1, j - 1))
        {
            return 1;
        }
    }

    // UP-RIGHT
    if (i > 0 && j + 1 < bSize)
    {
        char topRight = *(*(arr + i - 1) + j + 1);
        if (topRight == targetChar && search(arr, searchPath, word, wordIdx + 1, i - 1, j + 1))
        {
            return 1;
        }
    }

    // since the new step number was prepended, remove the first bufferLen characters (backtrack)
    int currentLen = strlen(cell);
    int bufferLen = strlen(buffer);
    if (currentLen >= bufferLen)
    {
        int k = 0;
        while (k <= currentLen - bufferLen)
        {
            *(cell + k) = *(cell + k + bufferLen);
            k++;
        }
    }

    return 0;
}

char ***createSearchPath(int size)
{
    char ***grid = (char ***)calloc(size, sizeof(char **));
    for (int i = 0; i < size; i++)
    {
        *(grid + i) = (char **)calloc(size, sizeof(char *));
        for (int j = 0; j < size; j++)
        {
            *(*(grid + i) + j) = (char *)calloc(50, sizeof(char));
            (*(*(grid + i) + j))[0] = '\0';
        }
    }
    return grid;
}

void searchPuzzle(char **arr, char *word)
{
    // This function checks if arr contains the search word. If the
    // word appears in arr, it will print out a message and the path
    // as shown in the sample runs. If not found, it will print a
    // different message as shown in the sample runs.
    // Your implementation here...

    char ***globalPath = createSearchPath(bSize);
    int found = 0;

    for (int i = 0; i < bSize; i++)
    {
        for (int j = 0; j < bSize; j++)
        {
            char *row = *(arr + i);
            char c = *(row + j);

            if (c == *word)
            {
                char ***tempPath = createSearchPath(bSize);
                if (search(arr, tempPath, word, 0, i, j))
                {
                    found = 1;

                    // merge tempPath into globalPath
                    for (int r = 0; r < bSize; r++)
                    {
                        for (int col = 0; col < bSize; col++)
                        {
                            char *tempCell = *(*(tempPath + r) + col);
                            if (*tempCell != '\0')
                            {
                                char *globalCell = *(*(globalPath + r) + col);
                                if (*globalCell == '\0')
                                {
                                    strcpy(globalCell, tempCell);
                                }
                                else
                                {
                                    char merged[50];
                                    strcpy(merged, globalCell);
                                    strcpy(globalCell, tempCell);
                                    strcat(globalCell, merged);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (!found)
    {
        printf("Word not found!");
        return;
    }

    printf("Word found!\nPrinting the search path:\n");
    for (int r = 0; r < bSize; r++)
    {
        for (int c = 0; c < bSize; c++)
        {
            char *cellStr = *(*(globalPath + r) + c);
            if (*cellStr == '\0')
            {
                printf("0\t");
            }
            else
            {
                printf("%s\t", cellStr);
            }
        }
        printf("\n");
    }
}







