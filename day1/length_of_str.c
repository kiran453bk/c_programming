#include <stdio.h>

int main() {
    char str[100];
    int i = 0;

    printf("Enter a string: ");
    gets(str);   // Note: gets() is unsafe, better to use fgets() in real programs

    while (str[i] != '\0') {   // Loop until null terminator
        i++;
    }

    printf("Length of the string = %d", i);

    return 0;
}
