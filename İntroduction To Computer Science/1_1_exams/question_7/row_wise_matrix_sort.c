#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

int main() {
    int matrix[MAX_ROWS][MAX_COLS];
    int rows, cols;
    int i, j, k;
    int swapped;
    int temp;

    // Input matrix dimensions
    printf("Enter matrix dimensions (rows columns):\n");
    scanf("%d %d", &rows, &cols);

    // Input matrix elements
    printf("Enter matrix elements:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Sort each row individually using bubble sort
    for (i = 0; i < rows; i++) {
        int pass = 0;
        swapped = 1;
        while (swapped == 1 && pass < cols) {
            swapped = 0;
            for (j = 0; j < cols - pass - 1; j++) {
                if (matrix[i][j] > matrix[i][j + 1]) {
                    // Swap elements
                    temp = matrix[i][j];
                    matrix[i][j] = matrix[i][j + 1];
                    matrix[i][j + 1] = temp;
                    swapped = 1;
                }
            }
            pass++;
        }
    }

    // Print the sorted matrix
    printf("Sorted matrix (each row sorted):\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}