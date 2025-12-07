#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;

    printf("%d", a+++b);
    return 0;
}

// compiler treates it as a++ + b answer is 30 after printf a will increment
