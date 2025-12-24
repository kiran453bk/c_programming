#include <stdio.h>

int main() {
    int n, i;
    int arr[100];
    int isSorted = 1;   // assume array is sorted

    // Input size
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Input array
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Check sorted condition
    for (i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            isSorted = 0;
            break;
        }
    }

    // Output result
    if (isSorted)
        printf("The array is sorted in ascending order\n");
    else
        printf("The array is NOT sorted\n");

    return 0;
}
