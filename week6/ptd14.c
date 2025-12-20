#include <stdio.h>

int main() {
    int n, i, j, count;
    int arr[100];
    int visited[100] = {0};

    // Read number of elements
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Read array elements
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Count frequency
    for (i = 0; i < n; i++) {
        if (visited[i] == 1)
            continue;

        count = 1;
        for (j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
                visited[j] = 1;
            }
        }

        printf("Element %d occurs %d times\n", arr[i], count);
    }

    return 0;
}
