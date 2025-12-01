#include <stdio.h>

int main() {
    char str1[100], str2[100];
    int i = 0, j = 0;

    printf("Enter first string: ");
    gets(str1);   // unsafe, used only for basic learning

    printf("Enter second string: ");
    gets(str2);

    // Find end of first string
    while (str1[i] != '\0') {
        i++;
    }

    // Copy str2 to str1
    while (str2[j] != '\0') {
        str1[i] = str2[j];
        i++;
        j++;
    }

    str1[i] = '\0'; // Add null terminator at end

    printf("Concatenated string: %s", str1);

    return 0;
}
