#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_STRINGS 3  // Number of strings
#define MAX_LENGTH 50  // Maximum length of each string

int main() {
	int i;
    // Allocate memory for an array of string pointers
    char **stringArray = (char **)malloc(NUM_STRINGS * sizeof(char *));
    if (stringArray == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Allocate memory for each string
    for (i = 0; i < NUM_STRINGS; i++) {
        stringArray[i] = (char *)malloc(MAX_LENGTH * sizeof(char));
        if (stringArray[i] == NULL) {
            printf("Memory allocation failed for string %d!\n", i);
            return 1;
        }
    }

    // Assign values to the strings
    strcpy(stringArray[0], "Hello, World!");
    strcpy(stringArray[1], "Dynamic memory allocation.");
    strcpy(stringArray[2], "C programming is fun!");

    // Print the strings
    printf("Stored strings:\n");
    for (i = 0; i < NUM_STRINGS; i++) {
        printf("%s\n", stringArray[i]);
    }

    // Free allocated memory
    for (i = 0; i < NUM_STRINGS; i++) {
        free(stringArray[i]);  // Free each string
    }
    free(stringArray);  // Free the array of pointers

    return 0;
}
