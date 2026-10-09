#include <stdio.h>

int main() {
	int i;
    for (i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // Skip even numbers returning to the top of a loop earlier than normal.
        }
        printf("%d ", i);
    }

    return 0;
}
