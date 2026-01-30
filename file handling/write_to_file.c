#include <stdio.h>

int main() {
    FILE *fp;  
    fp = fopen("example.txt", "w");  // open file in write mode

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "Hello, this is a test.\n");
    fputs("Writing another line.\n", fp);

    fclose(fp);  // close the file
    return 0;
}