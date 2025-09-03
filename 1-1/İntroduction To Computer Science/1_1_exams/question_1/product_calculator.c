#include <stdio.h>

#define MAX_PRODUCTS 100

int main() {
    char productNames[MAX_PRODUCTS][100];
    int productQuantities[MAX_PRODUCTS] = {0};
    int productPrices[MAX_PRODUCTS];
    int productCount;
    int totalCost = 0;

    printf("How many different products will you buy?\n");
    scanf("%d", &productCount);

    // Get product names
    for (int i = 0; i < productCount; i++) {
        printf("Enter the name of product %d:\n", i + 1);
        scanf("%s", productNames[i]);
    }

    // Get product quantities
    for (int i = 0; i < productCount; i++) {
        printf("How many units of %s will be bought?\n", productNames[i]);
        scanf("%d", &productQuantities[i]);
    }

    // Get product prices
    for (int i = 0; i < productCount; i++) {
        printf("Enter the shelf price of %s:\n", productNames[i]);
        scanf("%d", &productPrices[i]);
    }

    // Calculate total cost
    for (int i = 0; i < productCount; i++) {
        totalCost += productQuantities[i] * productPrices[i];
    }

    printf("The total cost is %d TL.\n", totalCost);

    return 0;
}