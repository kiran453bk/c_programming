#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int sub[] = {3, 4, 5};

    int n1 = sizeof(arr) / sizeof(arr[0]);   // size of main array
    int n2 = sizeof(sub) / sizeof(sub[0]);   // size of subarray
    int i, j, found;

    for(i = 0; i <= n1 - n2; i++) {  // stop where subarray can still fit
        found = 1;  // assume match
        for(j = 0; j < n2; j++) {
            if(arr[i + j] != sub[j]) {
                found = 0;  // mismatch found
                break;
            }
        }

        if(found) {
            printf("Subarray found at index %d\n", i);
            return 0;
        }
    }

    printf("Subarray not found\n");
    return 0;
}
