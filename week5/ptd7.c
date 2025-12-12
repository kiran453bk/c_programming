#include <stdio.h>

int main() {
    int n;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int a[n], b[n];

    // Input array A
    printf("Enter %d elements for array A:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Copy A → B
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }

    // Print copied array B
    printf("\nElements of array B:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", b[i]);
    }

    return 0;
}
