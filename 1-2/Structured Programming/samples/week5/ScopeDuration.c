#include <stdio.h>
#include <stdlib.h>
// Global variable (program scope)
int global_var = 10;

void staticExample() {
    static int static_var = 0;  // Block scope, fixed duration
    static_var++;
    printf("fixed duration:%d\n",static_var);
}

// automatic and register variables
void autoAndRegisterExample() {
    int auto_var = 5;       // Block scope, automatic duration
    register int reg_var = 15; // Block scope, automatic duration, hint to store in CPU register)
    printf("Automatic duration: %d\n", auto_var);
    printf("Register variable: %d\n", reg_var);
}

// Function using extern variable
void GlobalExample() {
    printf("Global variable (global_var): %d\n", global_var);
    global_var++;
    int global_var=15; //Block scope, global value of global_val is protected
    printf("Block scope (global_var): %d\n", global_var);
}

// dynamic memory allocation 
void dynamicMemoryExample() {
    int *heap_var = (int*)malloc(sizeof(int)); // Dynamically allocated variable 
    if (heap_var != NULL) {
        *heap_var = 50;
        printf("Heap variable: %d\n", *heap_var);
        free(heap_var); // Freeing allocated memory
    }
}

int main() {
    printf("Global variable: %d\n", global_var);

    staticExample();
    staticExample(); // Calls again to show static variable behavior

    autoAndRegisterExample();

    GlobalExample();
	GlobalExample();
    dynamicMemoryExample();

    return 0;
}
