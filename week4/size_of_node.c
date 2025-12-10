#include <stdio.h>

// Define a simple struct
struct node {
    int data;
    struct node *next;
};

int main() {
    struct node *a;  // pointer to struct node
    struct node b;   // actual struct node

    printf("Size of struct node *a (pointer): %zu bytes\n", sizeof(a));
    printf("Size of struct node b (struct): %zu bytes\n", sizeof(b));

    return 0;
}