#include <stdio.h>
#include <string.h>

int main() {
    char str[50];

    printf("Enter a string: ");
    gets(str);

    strrev(str);

    printf("Reversed string: %s\n", str);

    return 0;
}
