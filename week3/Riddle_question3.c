#include <stdio.h>

int main() {
    int x = 1;

    if (x == 1)
        if (x == 2)
            printf("A");
        else
            printf("B");
    else
        printf("C");

    return 0;
}
//B will print