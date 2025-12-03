#include <stdio.h>

#define MAX 10

int main() {
    int r, c;
    printf("Enter rows and columns of matrix: ");
    scanf("%d %d", &r, &c);

    float a[MAX][MAX];

    // Input Matrix
    printf("\nEnter matrix elements:\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%f", &a[i][j]);
        }
    }

    int rank = c;

    for (int row = 0; row < rank; row++) {

        // If the diagonal element is non-zero
        if (a[row][row] != 0) {

            // Make all rows except current row = 0 at current column
            for (int col = 0; col < r; col++) {
                if (col != row) {
                    float mult = a[col][row] / a[row][row];
                    for (int i = 0; i < rank; i++)
                        a[col][i] -= mult * a[row][i];
                }
            }
        }

        // If diagonal element is zero, swap with a row below
        else {
            int reduce = 1;
            for (int i = row + 1; i < r; i++) {
                if (a[i][row] != 0) {
                    // Swap rows
                    for (int j = 0; j < rank; j++) {
                        float temp = a[row][j];
                        a[row][j] = a[i][j];
                        a[i][j] = temp;
                    }
                    reduce = 0;
                    break;
                }
            }

            // If no row could fix it, reduce rank
            if (reduce) {
                rank--;
                for (int i = 0; i < r; i++)
                    a[i][row] = a[i][rank];
            }

            row--;
        }
    }

    printf("\nRank of the Matrix = %d\n", rank);

    return 0;
}
