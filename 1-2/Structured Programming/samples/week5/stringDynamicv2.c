#include <stdio.h>
#include <stdlib.h>
#define MAX_INPUT 100  // Max input length for reading

// Custom strcpy function
void my_strcpy(char *dest, const char *src) {
    while ((*dest++ = *src++)) {
        // Copies each character including the null terminator
    }
}

int main() {
	int i,num_strings;
	printf("give the number of strings\n");
	scanf ("%d",&num_strings);
    char **stringArray = (char **)malloc(num_strings * sizeof(char *));
    if (stringArray == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Read strings from the user
    for (i = 0; i < num_strings; i++) {
        char temp[MAX_INPUT];  // Temporary buffer to hold input
        printf("Enter string %d: ", i + 1);
        scanf ("%s",temp);
        // Allocate exact memory for the string
        stringArray[i] = (char *)malloc((strlen(temp) + 1) * sizeof(char));
        if (stringArray[i] == NULL) {
            printf("Memory allocation failed for string %d!\n", i);
            return 1;
        }

        my_strcpy(stringArray[i], temp);  // Use custom strcpy
    }

    // Print the stored strings
    printf("\nStored strings:\n");
    for (i = 0; i < num_strings; i++) {
        printf("%s\n", stringArray[i]);
    }

    // Free allocated memory
    for (i = 0; i < num_strings; i++) {
        free(stringArray[i]);
    }
    free(stringArray);

    return 0;
}
