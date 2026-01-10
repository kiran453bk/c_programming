#include <stdio.h>

int main() {
    int n, i;
    int arr[100], temp;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Right rotate by 1
    temp = arr[n - 1];
    for(i = n - 1; i > 0; i--)
        arr[i] = arr[i - 1];
    arr[0] = temp;

    printf("Array after right rotation by 1:\n");
    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
