#include <stdio.h>

int main()
{
    int n, k;
    int a[100], temp[100];

    printf("Enter array size: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter k: ");
    scanf("%d", &k);

    k = k % n;   // handle k > n

    // Store first k elements
    for(int i = 0; i < k; i++)
        temp[i] = a[i];

    // Shift remaining elements left
    for(int i = k; i < n; i++)
        a[i - k] = a[i];

    // Copy temp elements to end
    for(int i = 0; i < k; i++)
        a[n - k + i] = temp[i];

    printf("Left rotated array:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}
