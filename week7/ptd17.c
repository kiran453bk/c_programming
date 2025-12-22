#include <stdio.h>
#include <limits.h>

int main() {
    int arr[] = {12, 5, 7, 19, 3, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    int largest = INT_MIN, secondLargest = INT_MIN;
    int smallest = INT_MAX, secondSmallest = INT_MAX;

    for (int i = 0; i < n; i++) {

        // For largest and second largest
        if (arr[i] > largest) {
            secondLargest = largest;
            largest = arr[i];
        } else if (arr[i] > secondLargest && arr[i] != largest) {
            secondLargest = arr[i];
        }

        // For smallest and second smallest
        if (arr[i] < smallest) {
            secondSmallest = smallest;
            smallest = arr[i];
        } else if (arr[i] < secondSmallest && arr[i] != smallest) {
            secondSmallest = arr[i];
        }
    }

    printf("Second Largest  : %d\n", secondLargest);
    printf("Second Smallest : %d\n", secondSmallest);

    return 0;
}
