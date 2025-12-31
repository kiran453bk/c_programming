#include <stdio.h>

#define TOTAL_SEATS 10

int main() {
    int seats[TOTAL_SEATS] = {0};   // 0 = available, 1 = booked
    int choice, seatNo, i;

    while (1) {
        printf("\n===== Railway Seat Booking System =====\n");
        printf("1. View Seats\n");
        printf("2. Book Seat\n");
        printf("3. Cancel Seat\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("\nSeat Status:\n");
            for (i = 0; i < TOTAL_SEATS; i++) {
                if (seats[i] == 0)
                    printf("Seat %d : Available\n", i + 1);
                else
                    printf("Seat %d : Booked\n", i + 1);
            }
            break;

        case 2:
            printf("\nEnter seat number to book (1-%d): ", TOTAL_SEATS);
            scanf("%d", &seatNo);

            if (seatNo < 1 || seatNo > TOTAL_SEATS) {
                printf("Invalid seat number!\n");
            }
            else if (seats[seatNo - 1] == 1) {
                printf("\nSeat %d is already booked!\n", seatNo);
                printf("Available seats are:\n");

                for (i = 0; i < TOTAL_SEATS; i++) {
                    if (seats[i] == 0) {
                        printf("Seat %d\n", i + 1);
                    }
                }
            }
            else {
                seats[seatNo - 1] = 1;
                printf("Seat %d booked successfully!\n", seatNo);
            }
            break;

        case 3:
            printf("\nEnter seat number to cancel (1-%d): ", TOTAL_SEATS);
            scanf("%d", &seatNo);

            if (seatNo < 1 || seatNo > TOTAL_SEATS) {
                printf("Invalid seat number!\n");
            }
            else if (seats[seatNo - 1] == 0) {
                printf("Seat is already available!\n");
            }
            else {
                seats[seatNo - 1] = 0;
                printf("Seat %d booking cancelled!\n", seatNo);
            }
            break;

        case 4:
            printf("Thank you for using Railway Booking System 🚆\n");
            return 0;

        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}
