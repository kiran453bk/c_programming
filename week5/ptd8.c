#include <stdio.h>

int main() {
    int n;
    float sum = 0;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];

    // Input elements
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];     // Add each element to sum
    }

    float avg = sum / n;

    // Output
    printf("\nAverage = %.2f\n", avg);

    return 0;
}
