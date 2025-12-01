#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    char arr1[] = {'a', 'b', 'c', 'd'};
    
    

    // Using sizeof to find capacity (total allocated elements)
    int length = sizeof(arr) / sizeof(arr[0]);
    int length1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Length of integer array (capacity) = %d\n", length);
    printf("Length of char array (capacity) = %d\n", length1);



    return 0;
}
