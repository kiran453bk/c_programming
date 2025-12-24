#include <stdio.h>

int main() {
    int n, k, i, j, temp;
    int arr[100];

    // Input size
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Input array
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Input k
    printf("Enter value of k: ");
    scanf("%d", &k);

    // Check validity of k
    if (k > n || k <= 0) {
        printf("Invalid value of k\n");
        return 0;
    }

    // Sorting array (Bubble Sort)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Output results
    printf("Kth smallest element = %d\n", arr[k - 1]);
    printf("Kth largest element  = %d\n", arr[n - k]);

    return 0;
}
