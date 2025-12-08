#include <stdio.h>

int main() {
    int r1, c1, r2, c2;

    // Input rows & columns
    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    // Check multiplication condition
    if (c1 != r2) {
        printf("Matrix multiplication not possible!\n");
        return 0;
    }

    int A[r1][c1], B[r2][c2], M[r1][c2];

    // Input Matrix A
    printf("\nEnter elements of Matrix A:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // Input Matrix B
    printf("\nEnter elements of Matrix B:\n");
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Initialize result matrix M to 0
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            M[i][j] = 0;
        }
    }

    // Matrix multiplication
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {   // or r2
                M[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Display Result
    printf("\nResult of Matrix Multiplication (A × B):\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    return 0;
}
