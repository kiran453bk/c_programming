//Find the sum of all elements in an array
#include <stdio.h>

int main() {
    int n, sum = 0;

    // Read size of array
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    // Read array elements
    printf("Enter %d elements:\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Calculate sum
    for(int i = 0; i < n; i++) {
        sum += arr[i];
    }

    // Print sum
    printf("Sum of all elements = %d\n", sum);

    return 0;
}
