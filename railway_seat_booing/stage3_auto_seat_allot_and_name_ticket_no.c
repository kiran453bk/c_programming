#include <stdio.h>
#include <string.h>

#define TOTAL_SEATS 10

int main() {
    int seats[TOTAL_SEATS] = {0};          // 0 = available, 1 = booked
    char passenger[TOTAL_SEATS][50];       // passenger names
    int ticket[TOTAL_SEATS];               // ticket numbers

    int choice, seatNo, i;
    int ticketCounter = 1001;              // starting ticket number

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
                    printf("Seat %d : Booked | Name: %s | Ticket: %d\n",
                           i + 1, passenger[i], ticket[i]);
            }
            break;

        case 2:
            printf("\nEnter passenger name: ");
            scanf(" %[^\n]", passenger[0]);  // temporary input buffer

            printf("Enter preferred seat number (1-%d): ", TOTAL_SEATS);
            scanf("%d", &seatNo);

            if (seatNo < 1 || seatNo > TOTAL_SEATS) {
                printf("Invalid seat number!\n");
                break;
            }

            // If preferred seat is available
            if (seats[seatNo - 1] == 0) {
                seats[seatNo - 1] = 1;
                strcpy(passenger[seatNo - 1], passenger[0]);
                ticket[seatNo - 1] = ticketCounter++;

                printf("Seat %d booked successfully!\n", seatNo);
                printf("Ticket Number: %d\n", ticket[seatNo - 1]);
            }
            else {
                // Auto re-book from available seats
                printf("\nSeat %d is already booked.\n", seatNo);
                printf("Auto-booking next available seat...\n");

                for (i = 0; i < TOTAL_SEATS; i++) {
                    if (seats[i] == 0) {
                        seats[i] = 1;
                        strcpy(passenger[i], passenger[0]);
                        ticket[i] = ticketCounter++;

                        printf("Seat %d booked successfully!\n", i + 1);
                        printf("Ticket Number: %d\n", ticket[i]);
                        break;
                    }
                }

                if (i == TOTAL_SEATS) {
                    printf("Sorry, no seats available!\n");
                }
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
                printf("Seat %d booking cancelled (Ticket %d).\n",
                       seatNo, ticket[seatNo - 1]);
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
