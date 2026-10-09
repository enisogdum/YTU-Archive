#include <stdio.h>
// Define an enum for days of the week
enum Day { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };
int main() {
    enum Day today = WEDNESDAY;
    printf("The value of today is: %d\n", today); // Enums are internally stored as integers
    // Using enum in a switch statement
    switch (today) {
        case MONDAY:
            printf("It's Monday, time to start the week!\n");
            break;
        case WEDNESDAY:
            printf("It's Wednesday, midweek already!\n");
            break;
        case FRIDAY:
            printf("It's Friday, weekend is near!\n");
            break;
        default:
            printf("It's another day!\n");
    }
    printf("%d",MONDAY+WEDNESDAY); //0 for MONDAY + 3 for WEDNESDAY
    return 0;
}

