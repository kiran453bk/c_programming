//Birth preference and pnr search feature 
#include <stdio.h>
#include <string.h>

#define TOTAL_SEATS 10
#define MAX_NAME 50
#define MAX_TICKETS 100
#define FILE_NAME "railway_data.txt"

// Coach Types
#define SLEEPER 1
#define AC 2
#define GENERAL 3

// Berth Types
#define LOWER 1
#define MIDDLE 2
#define UPPER 3
#define SIDE_LOWER 4
#define SIDE_UPPER 5

int seats[TOTAL_SEATS];
char passenger[TOTAL_SEATS][MAX_NAME];
int ticket[TOTAL_SEATS];
int coach[TOTAL_SEATS];
int berth[TOTAL_SEATS];

// Ticket reuse
int freeTickets[MAX_TICKETS];
int freeCount = 0;
int ticketCounter = 1001;

/* ---------- BERTH LOGIC ---------- */
int getBerth(int seatNo) {
    int mod = seatNo % 8;
    if (mod == 1 || mod == 4) return LOWER;
    if (mod == 2 || mod == 5) return MIDDLE;
    if (mod == 3 || mod == 6) return UPPER;
    if (mod == 7) return SIDE_LOWER;
    return SIDE_UPPER;
}

void printBerth(int b) {
    if (b == LOWER) printf("Lower");
    else if (b == MIDDLE) printf("Middle");
    else if (b == UPPER) printf("Upper");
    else if (b == SIDE_LOWER) printf("Side Lower");
    else printf("Side Upper");
}

void printCoach(int c) {
    if (c == SLEEPER) printf("Sleeper");
    else if (c == AC) printf("AC");
    else printf("General");
}

/* ---------- FILE HANDLING ---------- */
void saveData() {
    FILE *fp = fopen(FILE_NAME, "w");
    for (int i = 0; i < TOTAL_SEATS; i++) {
        fprintf(fp, "%d %s %d %d %d\n",
                seats[i],
                seats[i] ? passenger[i] : "-",
                seats[i] ? ticket[i] : 0,
                seats[i] ? coach[i] : 0,
                seats[i] ? berth[i] : 0);
    }
    fclose(fp);
}

void loadData() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) return;

    for (int i = 0; i < TOTAL_SEATS; i++) {
        fscanf(fp, "%d %s %d %d %d",
               &seats[i], passenger[i],
               &ticket[i], &coach[i], &berth[i]);

        if (seats[i] && ticket[i] >= ticketCounter)
            ticketCounter = ticket[i] + 1;
    }
    fclose(fp);
}

/* ---------- TICKET MANAGEMENT ---------- */
int getTicketNumber() {
    if (freeCount > 0)
        return freeTickets[--freeCount];
    return ticketCounter++;
}

/* ---------- PNR SEARCH ---------- */
void searchByTicket() {
    int tno, found = 0;
    printf("Enter ticket number: ");
    scanf("%d", &tno);

    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[i] && ticket[i] == tno) {
            printf("\n--- Ticket Found ---\n");
            printf("Passenger : %s\n", passenger[i]);
            printf("Seat No   : %d\n", i + 1);
            printf("Coach     : ");
            printCoach(coach[i]);
            printf("\nBerth     : ");
            printBerth(berth[i]);
            printf("\nTicket No : %d\n", ticket[i]);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Ticket not found!\n");
}

int main() {
    int choice, i, coachChoice;
    char name[MAX_NAME];

    loadData();

    while (1) {
        printf("\n===== Railway Reservation System =====\n");
        printf("1. View Seats\n");
        printf("2. Book Seat\n");
        printf("3. Cancel Ticket\n");
        printf("4. Search by Ticket (PNR)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            for (i = 0; i < TOTAL_SEATS; i++) {
                printf("Seat %d: ", i + 1);
                if (!seats[i]) printf("Available\n");
                else {
                    printCoach(coach[i]);
                    printf(" | ");
                    printBerth(berth[i]);
                    printf(" | %s | Ticket %d\n",
                           passenger[i], ticket[i]);
                }
            }
            break;

        case 2:
            printf("Enter passenger name: ");
            scanf(" %[^\n]", name);

            printf("Select Coach (1-Sleeper 2-AC 3-General): ");
            scanf("%d", &coachChoice);

            int start, end;
            if (coachChoice == SLEEPER) { start = 0; end = 3; }
            else if (coachChoice == AC) { start = 4; end = 6; }
            else if (coachChoice == GENERAL) { start = 7; end = 9; }
            else { printf("Invalid coach!\n"); break; }

            for (i = start; i <= end; i++) {
                if (!seats[i]) {
                    seats[i] = 1;
                    strcpy(passenger[i], name);
                    coach[i] = coachChoice;
                    berth[i] = getBerth(i + 1);
                    ticket[i] = getTicketNumber();
                    saveData();

                    printf("Booked Seat %d | Ticket %d | ",
                           i + 1, ticket[i]);
                    printBerth(berth[i]);
                    printf("\n");
                    break;
                }
            }
            if (i > end)
                printf("No seats available in this coach!\n");
            break;

        case 3:
            printf("Enter seat number to cancel: ");
            scanf("%d", &i);
            i--;

            if (i < 0 || i >= TOTAL_SEATS || !seats[i]) {
                printf("Invalid seat!\n");
            } else {
                freeTickets[freeCount++] = ticket[i];
                seats[i] = 0;
                saveData();
                printf("Ticket cancelled successfully!\n");
            }
            break;

        case 4:
            searchByTicket();
            break;

        case 5:
            saveData();
            printf("System closed 🚆\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}
