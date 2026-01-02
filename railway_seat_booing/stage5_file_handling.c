#include <stdio.h>
#include <string.h>

#define TOTAL_SEATS 10
#define MAX_NAME 50
#define MAX_TICKETS 100
#define FILE_NAME "railway_data.txt"

// Coach types
#define SLEEPER 1
#define AC 2
#define GENERAL 3

int seats[TOTAL_SEATS];
char passenger[TOTAL_SEATS][MAX_NAME];
int ticket[TOTAL_SEATS];
int coach[TOTAL_SEATS];

// Ticket reuse
int freeTickets[MAX_TICKETS];
int freeCount = 0;
int ticketCounter = 1001;

/* ---------- FILE FUNCTIONS ---------- */
void saveData() {
    FILE *fp = fopen(FILE_NAME, "w");
    for (int i = 0; i < TOTAL_SEATS; i++) {
        fprintf(fp, "%d %s %d %d\n",
                seats[i],
                seats[i] ? passenger[i] : "-",
                seats[i] ? ticket[i] : 0,
                seats[i] ? coach[i] : 0);
    }
    fclose(fp);
}

void loadData() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return;

    for (int i = 0; i < TOTAL_SEATS; i++) {
        fscanf(fp, "%d %s %d %d",
               &seats[i],
               passenger[i],
               &ticket[i],
               &coach[i]);

        if (seats[i] && ticket[i] >= ticketCounter)
            ticketCounter = ticket[i] + 1;
    }
    fclose(fp);
}

/* ---------- TICKET LOGIC ---------- */
int getTicketNumber() {
    if (freeCount > 0)
        return freeTickets[--freeCount];
    return ticketCounter++;
}

void printCoach(int c) {
    if (c == SLEEPER) printf("Sleeper");
    else if (c == AC) printf("AC");
    else printf("General");
}

int main() {
    int choice, seatNo, i, coachChoice;
    char name[MAX_NAME];

    loadData();   // Load previous data

    while (1) {
        printf("\n===== Railway Booking System =====\n");
        printf("1. View Seats\n");
        printf("2. Book Seat\n");
        printf("3. Cancel Ticket\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            for (i = 0; i < TOTAL_SEATS; i++) {
                printf("Seat %d: ", i + 1);
                if (seats[i] == 0)
                    printf("Available\n");
                else {
                    printCoach(coach[i]);
                    printf(" | %s | Ticket %d\n",
                           passenger[i], ticket[i]);
                }
            }
            break;

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
                printf("Invalid coach!\n");
                break;
            }

            for (i = start; i <= end; i++) {
                if (seats[i] == 0) {
                    seats[i] = 1;
                    strcpy(passenger[i], name);
                    coach[i] = coachChoice;
                    ticket[i] = getTicketNumber();

                    saveData();
                    printf("Seat %d booked | Ticket %d\n",
                           i + 1, ticket[i]);
                    break;
                }
            }
            if (i > end)
                printf("No seats available in this coach!\n");
            break;

        case 3:
            printf("Enter seat number to cancel: ");
            scanf("%d", &seatNo);

            if (seatNo < 1 || seatNo > TOTAL_SEATS ||
                seats[seatNo - 1] == 0) {
                printf("Invalid seat!\n");
            } else {
                freeTickets[freeCount++] = ticket[seatNo - 1];
                seats[seatNo - 1] = 0;

                saveData();
                printf("Ticket cancelled successfully!\n");
            }
            break;

        case 4:
            saveData();
            printf("System closed 🚆\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}
