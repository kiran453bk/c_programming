#include <stdio.h>

int main() {
    int arr[100], n;
    int evenSum = 0, oddSum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for(int i = 0; i < n; i++) {
        if(i % 2 == 0)
            evenSum += arr[i];   // even index
        else
            oddSum += arr[i];    // odd index
    }

    printf("Sum of elements at even indices = %d\n", evenSum);
    printf("Sum of elements at odd indices  = %d\n", oddSum);

    return 0;
}
