#include <stdio.h>

int main() {
    int i;
    int four_ints[4];
    char* four_c;
    
    for(i = 0; i < 4; i++)
        four_ints[i] = 2;
    
    printf("1. Initial value of four_ints[0] in hex: %x\n", four_ints[0]);
    
    four_c = (char*)four_ints;
    
    for(i = 0; i < 4; i++)
        four_c[i] = 'A' + i; // ASCII value of 'A' is 65 or 0x41 in Hex.
    
    // 3. Print four_ints[0] at the end of the program
    printf("3. Value of four_ints[0] at the end: %x\n", four_ints[0]);
    
    // 4. Print four_ints[1] in hex
    printf("4. Value of four_ints[1] in hex: %x\n", four_ints[1]);
    
    // 5c. Print addresses of four_ints and four_c to verify if they point to the same location
    printf("5c. Address of four_ints: %p\n", (void*)four_ints);
    printf("5c. Address of four_c: %p\n", (void*)four_c);
    
    // 6. Print addresses and values of all elements in four_ints
    printf("\n6. Addresses and values of four_ints array:\n");
    for(i = 0; i < 4; i++) {
        printf("four_ints[%d]: address = %p, value = %x\n", 
               i, (void*)&four_ints[i], four_ints[i]);
    }
    
    // 8. Print addresses and values of all elements in four_c
    printf("\n8. Addresses and values of four_c array:\n");
    for(i = 0; i < 16; i++) {  // 4 ints × 4 bytes = 16 bytes total
        printf("four_c[%d]: address = %p, value = %x\n", 
               i, (void*)&four_c[i], (unsigned char)four_c[i]);
    }
    
    return 0;
}