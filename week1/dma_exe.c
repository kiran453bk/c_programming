#include <stdio.h>
#include <stdlib.h>  // for malloc, calloc, realloc, free

int main() {
    int *arr, *newArr;
    int i;

    // 1. malloc() - allocate memory for 5 integers
    arr = (int*) malloc(5 * sizeof(int));
    if (arr == NULL) {
        printf("Memory not allocated using malloc.\n");
        return 1;
    }
    printf("Memory allocated using malloc (garbage values):\n");
    for (i = 0; i < 5; i++) {
        printf("%d ", arr[i]);  // contains garbage values
    }
    printf("\n");

    // 2. calloc() - allocate memory for 5 integers (initialized to 0)
    int *arr2 = (int*) calloc(5, sizeof(int));
    if (arr2 == NULL) {
        printf("Memory not allocated using calloc.\n");
        return 1;
    }
    printf("Memory allocated using calloc (initialized to 0):\n");
    for (i = 0; i < 5; i++) {
        printf("%d ", arr2[i]);  // contains zeros
    }
    printf("\n");

    // 3. realloc() - resize malloc block from 5 to 10 integers
    newArr = (int*) realloc(arr, 10 * sizeof(int));
    if (newArr == NULL) {
        printf("Memory not reallocated.\n");
        free(arr);  // free old memory if realloc fails
        return 1;
    }
    arr = newArr;  // point arr to new block
    printf("Memory reallocated to 10 integers:\n");
    for (i = 0; i < 10; i++) {
        arr[i] = i + 1;  // assign values
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 4. free() - release memory
    free(arr);
    free(arr2);
    printf("Memory freed successfully.\n");

    return 0;
}