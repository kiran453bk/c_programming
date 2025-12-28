#include <stdio.h>

int main() {
    char buffer[50]; // The destination array
    int score = 95;
    char name[] = "Alice";

    // Formats the string and stores it in 'buffer'
    sprintf(buffer, "Player %s scored %d points.", name, score);

    // Now 'buffer' contains "Player Alice scored 95 points."
    printf("%s\n", buffer); 

    return 0;
}
