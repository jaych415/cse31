#include <stdio.h>

typedef struct node {
  int value;
  struct node *next;
} node;

//This code implements cycle detection in a singly linked list using Floyd's Tortoise and Hare algorithm.
 //It defines a node structure with an integer value and a pointer to the next node, and the has_cycle function checks 
 //for a cycle by advancing two pointers at different speeds until they meet (indicating a cycle) or reach the end of the list. 
 //The test_has_cycle function sets up several linked list scenarios—some with cycles and some without—to verify the correctness
// of the cycle detection, and the main function executes these tests.


int has_cycle(node *head) {
  // Your code goes here:
  
  // Handle empty list or single node that doesn't point to itself
  if (head == NULL || head->next == NULL) {
    return 0; // No cycle
  }
  
  // Initialize two pointers - slow (tortoise) and fast (hare)
  node *slow = head;
  node *fast = head;
  
  // Move slow pointer by 1 and fast pointer by 2
  // If there's a cycle, they will eventually meet
  while (fast != NULL && fast->next != NULL) {
    // Move slow pointer one step
    slow = slow->next;
    
    // Move fast pointer two steps
    fast = fast->next->next;
    
    // Check if the pointers meet, indicating a cycle
    if (slow == fast) {
      return 1; // Cycle detected
    }
  }
  
  // If fast pointer reaches NULL, there's no cycle
  return 0;
}

//The has_cycle function determines whether a singly linked list contains a cycle. 
//It uses Floyd's Tortoise and Hare algorithm, where two pointers traverse the list at
//different speeds (one moving one node at a time and the other two nodes at a time).
//If these pointers meet, it means there's a cycle, so the function returns 1; otherwise, 
//if the fast pointer reaches the end of the list, it returns 0, indicating no cycle.

void test_has_cycle(void) {
  int i;
  node nodes[25]; //enough to run our tests
  for(i=0; i < sizeof(nodes)/sizeof(node); i++) {
    nodes[i].next = 0;
    nodes[i].value = 0;
  }
  nodes[0].next = &nodes[1];
  nodes[1].next = &nodes[2];
  nodes[2].next = &nodes[3];
  printf("Checking first list for cycles. There should be none, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[0])?"a":"no");
  
  nodes[4].next = &nodes[5];
  nodes[5].next = &nodes[6];
  nodes[6].next = &nodes[7];
  nodes[7].next = &nodes[8];
  nodes[8].next = &nodes[9];
  nodes[9].next = &nodes[10];
  nodes[10].next = &nodes[4];
  printf("Checking second list for cycles. There should be a cycle, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[4])?"a":"no");
  
  nodes[11].next = &nodes[12];
  nodes[12].next = &nodes[13];
  nodes[13].next = &nodes[14];
  nodes[14].next = &nodes[15];
  nodes[15].next = &nodes[16];
  nodes[16].next = &nodes[17];
  nodes[17].next = &nodes[14];
  printf("Checking third list for cycles. There should be a cycle, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[11])?"a":"no");
  
  nodes[18].next = &nodes[18];
  printf("Checking fourth list for cycles. There should be a cycle, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[18])?"a":"no");
  
  nodes[19].next = &nodes[20];
  nodes[20].next = &nodes[21];
  nodes[21].next = &nodes[22];
  nodes[22].next = &nodes[23];
  printf("Checking fifth list for cycles. There should be none, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[19])?"a":"no");
  
  printf("Checking length-zero list for cycles. There should be none, has_cycle says it has %s cycle\n",
    has_cycle(NULL)?"a":"no");
}

int main(void) {
  test_has_cycle();
  return 0;
}
