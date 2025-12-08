#include <stdio.h>

int main() {
    char str[100], ch;
    int i = 0, count = 0;

    printf("Enter a string: ");
    gets(str);   // For basic learning (not safe)

    printf("Enter the character to count: ");
    scanf(" %c", &ch);   // Space before %c to ignore newline

    // Count occurrences
    while (str[i] != '\0') {   // Loop until null terminator
        if (str[i] == ch) {
            count++;          // Increase count when match found
        }
        i++;
    }

    printf("Character '%c' occurs %d times.", ch, count);

    return 0;
}
