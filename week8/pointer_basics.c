#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;

    // Pointer declaration
    int *ptr;

    // Pointer initialization
    ptr = &a;

    printf("Value of a = %d\n", a);
    printf("Address of a = %p\n", &a);
    printf("Pointer ptr holds address = %p\n", ptr);
    printf("Value pointed by ptr = %d\n", *ptr);

    // Changing pointer to point to another variable
    ptr = &b;
    printf("\nAfter pointing to b:\n");
    printf("Value of b = %d\n", b);
    printf("Pointer ptr holds address = %p\n", ptr);
    printf("Value pointed by ptr = %d\n", *ptr);

    // Pointer arithmetic using array
    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;   // points to first element

    printf("\nPointer Arithmetic using array:\n");

    for (int i = 0; i < 5; i++) {
        printf("Address: %p  Value: %d\n", p, *p);
        p++;   // move to next integer
    }

    return 0;
}
