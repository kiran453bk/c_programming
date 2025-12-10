#include <stdio.h>

int main() {
    int n;

    // Read size of array
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];   // array declaration

    // Read elements
    printf("Enter %d elements:\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Print elements
    printf("Array elements are:\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
