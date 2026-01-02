#include <stdio.h>
#include <string.h>

#define TOTAL_SEATS 10
#define MAX_NAME 50
#define MAX_TICKETS 100

// Coach types
#define SLEEPER 1
#define AC 2
#define GENERAL 3

int seats[TOTAL_SEATS] = {0};
char passenger[TOTAL_SEATS][MAX_NAME];
int ticket[TOTAL_SEATS];
int coach[TOTAL_SEATS];

// Ticket reuse system
int freeTickets[MAX_TICKETS];
int freeCount = 0;
int ticketCounter = 1001;

// Function to get ticket number
int getTicketNumber() {
    if (freeCount > 0)
        return freeTickets[--freeCount];  // reuse cancelled ticket
    else
        return ticketCounter++;           // new ticket
}

// Function to display coach name
void printCoach(int c) {
    if (c == SLEEPER) printf("Sleeper");
    else if (c == AC) printf("AC");
    else printf("General");
}

int main() {
    int choice, seatNo, i, coachChoice;
    char name[MAX_NAME];

    while (1) {
        printf("\n===== Railway Booking System =====\n");
        printf("1. View Seats\n");
        printf("2. Book Seat\n");
        printf("3. Cancel Ticket\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        // ---------------- VIEW SEATS ----------------
        case 1:
            for (i = 0; i < TOTAL_SEATS; i++) {
                printf("Seat %d : ", i + 1);
                if (seats[i] == 0)
                    printf("Available\n");
                else {
                    printCoach(coach[i]);
                    printf(" | %s | Ticket %d\n",
                           passenger[i], ticket[i]);
                }
            }
            break;

        // ---------------- BOOK SEAT ----------------
        case 2:
            printf("Enter passenger name: ");
            scanf(" %[^\n]", name);

            printf("Select Coach (1-Sleeper, 2-AC, 3-General): ");
            scanf("%d", &coachChoice);

            int start, end;

            if (coachChoice == SLEEPER) { start = 0; end = 3; }
            else if (coachChoice == AC) { start = 4; end = 6; }
            else if (coachChoice == GENERAL) { start = 7; end = 9; }
            else {
                printf("Invalid coach type!\n");
                break;
            }

            // Auto-assign seat in selected coach
            for (i = start; i <= end; i++) {
                if (seats[i] == 0) {
                    seats[i] = 1;
                    strcpy(passenger[i], name);
                    coach[i] = coachChoice;
                    ticket[i] = getTicketNumber();

                    printf("Seat %d booked successfully!\n", i + 1);
                    printf("Ticket Number: %d\n", ticket[i]);
                    break;
                }
            }

            if (i > end)
                printf("No seats available in selected coach!\n");

            break;

        // ---------------- CANCEL TICKET ----------------
        case 3:
            printf("Enter seat number to cancel (1-%d): ", TOTAL_SEATS);
            scanf("%d", &seatNo);

            if (seatNo < 1 || seatNo > TOTAL_SEATS || seats[seatNo - 1] == 0) {
                printf("Invalid or empty seat!\n");
            } else {
                // Store cancelled ticket for reuse
                freeTickets[freeCount++] = ticket[seatNo - 1];

                seats[seatNo - 1] = 0;
                printf("Ticket %d cancelled successfully!\n",
                       ticket[seatNo - 1]);
            }
            break;

        case 4:
            printf("System closed 🚆\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}
