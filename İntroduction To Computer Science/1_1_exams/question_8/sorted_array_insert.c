#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int numbers[MAX_SIZE];
    int n, i, j, temp, newValue;
    int swapped;

    // Input number of elements
    printf("How many elements will the array have?\n");
    scanf("%d", &n);

    // Input elements
    printf("Enter the elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    // Bubble sort
    i = 0;
    swapped = 1;
    while (swapped == 1) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
                swapped = 1;
            }
        }
        i++;
    }

    // Print sorted array
    printf("Sorted array:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Input value to insert
    printf("Enter the value to insert:\n");
    scanf("%d", &newValue);

    // Increase size by one for new element
    n++;

    // Find the correct position for the new value
    j = 0;
    while (j < n - 1 && numbers[j] <= newValue) {
        j++;
    }

    // Shift elements to make space
    for (i = n - 1; i > j; i--) {
        numbers[i] = numbers[i - 1];
    }

    // Insert the new value
    numbers[j] = newValue;

    // Print the new array
    printf("Array after insertion:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}