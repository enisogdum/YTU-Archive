#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int numbers[MAX_SIZE];
    int primeNumbers[MAX_SIZE];
    int totalPrimes = 0;
    int count, i, j;

    printf("How many elements will the array have?\n");
    scanf("%d", &count);

    printf("Enter the elements:\n");
    for (i = 0; i < count; i++) {
        scanf("%d", &numbers[i]);
    }

    // Check for prime numbers
    for (i = 0; i < count; i++) {
        if (numbers[i] < 2) continue; // Skip numbers less than 2

        j = 2;
        while (j < numbers[i] && numbers[i] % j != 0) {
            j++;
        }

        if (j == numbers[i]) {
            primeNumbers[totalPrimes++] = numbers[i];
        }
    }

    printf("Total number of prime elements: %d\n", totalPrimes);
    printf("Prime numbers:\n");

    for (i = 0; i < totalPrimes; i++) {
        printf("%d ", primeNumbers[i]);
    }

    printf("\n");
    return 0;
}