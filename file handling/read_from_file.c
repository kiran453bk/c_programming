#include <stdio.h>

int main() {
    FILE *fp;
    char buffer[100];

    fp = fopen("example.txt", "r");  // open file in read mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);  // print each line
    }

    fclose(fp);
    return 0;
}