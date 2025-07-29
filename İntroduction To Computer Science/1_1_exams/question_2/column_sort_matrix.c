#include <stdio.h>

#define MATRIX_SIZE 100

int main() {
    int rows, cols;
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    int i, j, k, temp;
    int swap;

    // Input dimensions of the matrix
    printf("Enter matrix dimensions (rows and columns):\n");
    scanf("%d %d", &rows, &cols);

    // Input elements of the matrix
    printf("Enter the elements of the matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Sort each column in ascending order
    for (j = 0; j < cols; j++) {
        swap = 1;
        k = 0;
        while (swap == 1) {
            swap = 0;
            for (i = 0; i < rows - 1 - k; i++) {
                if (matrix[i][j] > matrix[i + 1][j]) {
                    // Swap elements
                    temp = matrix[i][j];
                    matrix[i][j] = matrix[i + 1][j];
                    matrix[i + 1][j] = temp;
                    swap = 1;
                }
            }
            k++;
        }
    }

    // Output the sorted matrix
    printf("\nSorted matrix (columns in ascending order):\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}