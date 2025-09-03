#include <stdio.h>
#define dizi_size 100

int main() {
    int i, j, k, z;
    int n, m;
    int matrix[dizi_size][dizi_size];
    int number[dizi_size * dizi_size]; // Adjusted size
    int swap;
    int temp;
    int choice;
    int running = 1;

    printf("Enter matrix dimensions (rows columns):\n");
    scanf("%d %d", &n, &m);

    printf("Enter matrix elements:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    while (running) {
        printf("\nMenu:\n");
        printf("1. Sort matrix and display it\n");
        printf("2. Display original matrix\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Flatten matrix into 1D array
                k = 0;
                for (i = 0; i < n; i++) {
                    for (j = 0; j < m; j++) {
                        number[k++] = matrix[i][j];
                    }
                }

                // Bubble Sort
                swap = 1;
                z = 0;
                while (swap == 1) {
                    swap = 0;
                    for (j = 0; j < k - 1 - z; j++) {
                        if (number[j] > number[j + 1]) {
                            temp = number[j];
                            number[j] = number[j + 1];
                            number[j + 1] = temp;
                            swap = 1;
                        }
                    }
                    z++;
                }

                // Refill sorted values into matrix
                k = 0;
                for (i = 0; i < n; i++) {
                    for (j = 0; j < m; j++) {
                        matrix[i][j] = number[k++];
                    }
                }

                printf("Sorted matrix:\n");
                for (i = 0; i < n; i++) {
                    for (j = 0; j < m; j++) {
                        printf("%d ", matrix[i][j]);
                    }
                    printf("\n");
                }
                break;

            case 2:
                printf("Original matrix:\n");
                for (i = 0; i < n; i++) {
                    for (j = 0; j < m; j++) {
                        printf("%d ", matrix[i][j]);
                    }
                    printf("\n");
                }
                break;

            case 3:
                running = 0;
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}