#include <stdio.h>

int main() {
    int n;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];

    // Input array elements
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int positive = 0, negative = 0;
    int even = 0, odd = 0;

    // Count numbers
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0)
            positive++;
        else
            negative++;

        if (arr[i] % 2 == 0)
            even++;
        else
            odd++;
    }

    // Output results
    printf("\nPositive numbers: %d", positive);
    printf("\nNegative numbers: %d", negative);
    printf("\nEven numbers: %d", even);
    printf("\nOdd numbers: %d\n", odd);

    return 0;
}
