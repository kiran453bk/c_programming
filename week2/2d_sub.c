#include <stdio.h>

int main() {
    int r, c;

    printf("Enter number of rows: ");
    scanf("%d", &r);

    printf("Enter number of columns: ");
    scanf("%d", &c);

    int a[r][c], b[r][c], sub[r][c];

    // Input for Matrix A
    printf("\nEnter elements of Matrix A:\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // Input for Matrix B
    printf("\nEnter elements of Matrix B:\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    // Subtraction: A - B
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            sub[i][j] = a[i][j] - b[i][j];
        }
    }

    // Display Result
    printf("\nResult of A - B:\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", sub[i][j]);
        }
        printf("\n");
    }

    return 0;
}
