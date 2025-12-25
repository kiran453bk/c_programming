#include <stdio.h>

int main() {
    int a[50], b[50], c[100];
    int n1, n2, i, j = 0;

    // Input size of first array
    printf("Enter size of first array: ");
    scanf("%d", &n1);

    printf("Enter elements of first array:\n");
    for (i = 0; i < n1; i++) {
        scanf("%d", &a[i]);
        c[j++] = a[i];   // Copy to third array
    }

    // Input size of second array
    printf("Enter size of second array: ");
    scanf("%d", &n2);

    printf("Enter elements of second array:\n");
    for (i = 0; i < n2; i++) {
        scanf("%d", &b[i]);
        c[j++] = b[i];   // Append to third array
    }

    // Print merged array
    printf("Merged array:\n");
    for (i = 0; i < j; i++) {
        printf("%d ", c[i]);
    }

    return 0;
}
