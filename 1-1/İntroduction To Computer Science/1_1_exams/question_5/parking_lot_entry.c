#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROWS 7
#define MAX_COLS 7
#define MAX_VEHICLES 49
#define MAX_STRING 30

void initializeParking(char parking[MAX_ROWS][MAX_COLS]) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            parking[i][j] = '.';
        }
    }
}

void displayParking(char parking[MAX_ROWS][MAX_COLS]) {
    printf("\nCurrent Parking Lot Status:\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%c ", parking[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char parkingLot[MAX_ROWS][MAX_COLS];
    char vehicleRecords[MAX_VEHICLES][MAX_STRING * 2] = {0};
    int totalVehicles = 0;
    int choice;

    initializeParking(parkingLot);

    while (true) {
        printf("\n--- Parking Lot Menu ---\n");
        printf("1. Vehicle Entry\n");
        printf("2. Vehicle Exit\n");
        printf("3. Show Parking Lot\n");
        printf("4. Find Longest Parked Vehicle\n");
        printf("5. Calculate Daily Income\n");
        printf("6. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int row, col;
                char licensePlate[MAX_STRING];
                char entryTime[MAX_STRING];
                char exitTime[MAX_STRING];
                char formatted[MAX_STRING * 2];

                printf("Enter desired parking position (row column): ");
                scanf("%d %d", &row, &col);

                if (row < 1 || row > MAX_ROWS || col < 1 || col > MAX_COLS) {
                    printf("Invalid parking position.\n");
                    break;
                }

                if (parkingLot[row - 1][col - 1] == '.') {
                    printf("Enter license plate: ");
                    scanf("%s", licensePlate);

                    printf("Enter entry time: ");
                    scanf("%s", entryTime);

                    printf("Enter expected exit time: ");
                    scanf("%s", exitTime);

                    // Format record: [LICENSE][ENTRY][EXIT]
                    sprintf(formatted, "[%s][%s][%s]", licensePlate, entryTime, exitTime);
                    strcpy(vehicleRecords[totalVehicles++], formatted);

                    // Mark as occupied
                    parkingLot[row - 1][col - 1] = 'X';

                    printf("Vehicle parked successfully.\n");
                } else {
                    printf("That spot is already occupied.\n");
                }
                break;
            }

            case 2:
                printf("Vehicle Exit - Feature not implemented yet.\n");
                break;

            case 3:
                displayParking(parkingLot);
                break;

            case 4:
                printf("Find Longest Parked Vehicle - Feature not implemented yet.\n");
                break;

            case 5:
                printf("Calculate Daily Income - Feature not implemented yet.\n");
                break;

            case 6:
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid selection. Please try again.\n");
        }
    }

    return 0;
}