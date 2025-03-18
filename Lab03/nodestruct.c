#include <stdio.h>
#include <stdlib.h>

struct Node {
    int iValue;
    float fValue;
    struct Node *next;
};

int main() {

    struct Node *head = (struct Node*) malloc(sizeof(struct Node));
    head->iValue = 5;
    head->fValue = 3.14;
	
    // Insert code here
    // Create one more node and link it
    head->next = (struct Node*) malloc(sizeof(struct Node));
    head->next->iValue = 10;
    head->next->fValue = 6.28;
    head->next->next = NULL;
    
    // Print the values
    printf("Node 1: %d, %.2f\n", head->iValue, head->fValue);
    printf("Node 2: %d, %.2f\n", head->next->iValue, head->next->fValue);
    
    // Free memory
    free(head->next);
    free(head);
	
    return 0;
}
