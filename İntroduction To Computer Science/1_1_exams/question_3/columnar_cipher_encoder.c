#include <stdio.h>
#define SIZE 100

int main() {
    int i, j;
    int x; // number of rows
    int column;
    char password[SIZE];
    char matrix_password[SIZE][SIZE];
    char new_password[SIZE];  // Resulting rearranged password
    int total_letters = 0;
    int temp;

    printf("Enter your password: ");
    scanf("%s", password);

    // Count the number of characters in the password
    while (password[total_letters] != '\0') {
        total_letters++;
    }
    printf("Password length: %d\n", total_letters);

    printf("Enter the number of rows to split the password into: ");
    scanf("%d", &x);

    // Calculate number of columns
    if (total_letters % x != 0) {
        column = (total_letters / x) + 1;
    } else {
        column = total_letters / x;
    }

    printf("Number of columns: %d\n", column);

    // Fill matrix row by row
    temp = 0;
    for (i = 0; i < x; i++) {
        for (j = 0; j < column; j++) {
            if (temp < total_letters) {
                matrix_password[i][j] = password[temp++];
            } else {
                matrix_password[i][j] = '-'; // padding
            }
        }
    }

    // Print the matrix
    printf("Matrix:\n");
    for (i = 0; i < x; i++) {
        for (j = 0; j < column; j++) {
            printf("%c ", matrix_password[i][j]);
        }
        printf("\n");
    }

    // Reconstruct password column by column
    temp = 0;
    for (j = 0; j < column; j++) {
        for (i = 0; i < x; i++) {
            if (matrix_password[i][j] != '-') {
                new_password[temp++] = matrix_password[i][j];
            }
        }
    }
    new_password[temp] = '\0'; // Null-terminate the new password

    printf("New password: %s\n", new_password);

    return 0;
}