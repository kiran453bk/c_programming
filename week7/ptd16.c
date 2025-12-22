#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 2, 4, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i, j, count;

    printf("Unique elements are: ");

    for (i = 0; i < n; i++) {
        count = 0;

        for (j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }

        if (count == 1) {
            printf("%d ", arr[i]);
        }
    }

    return 0;
}
