#include <stdio.h>
#include <string.h>

#define TOTAL_SEATS 10
#define MAX_NAME 50
#define FILE_NAME "railway_data.txt"

#define CONFIRMED 1
#define RAC 2

int status[TOTAL_SEATS];
char passenger[TOTAL_SEATS][MAX_NAME];
int ticket[TOTAL_SEATS];
char berth[TOTAL_SEATS][3];   // L M U SL SU

// Waiting List
char wlName[10][MAX_NAME];
int wlCount = 0;

// RAC
int racCount = 0;

// Ticket
int ticketCounter = 1001;

/* ---------- BERTH FROM SEAT ---------- */
void getBerthCode(int seatNo, char *b) {
    int m = seatNo % 8;
    if (m == 1 || m == 4) strcpy(b, "L");
    else if (m == 2 || m == 5) strcpy(b, "M");
    else if (m == 3 || m == 6) strcpy(b, "U");
    else if (m == 7) strcpy(b, "SL");
    else strcpy(b, "SU");
}

/* ---------- SAVE / LOAD ---------- */
void saveData() {
    FILE *fp = fopen(FILE_NAME, "w");
    fprintf(fp, "%d %d %d\n", ticketCounter, racCount, wlCount);

    for (int i = 0; i < TOTAL_SEATS; i++)
        fprintf(fp, "%d %s %d %s\n",
                status[i],
                status[i] ? passenger[i] : "-",
                status[i] ? ticket[i] : 0,
                status[i] ? berth[i] : "-");

    for (int i = 0; i < wlCount; i++)
        fprintf(fp, "%s\n", wlName[i]);

    fclose(fp);
}

void loadData() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) return;

    fscanf(fp, "%d %d %d", &ticketCounter, &racCount, &wlCount);

    for (int i = 0; i < TOTAL_SEATS; i++)
        fscanf(fp, "%d %s %d %s",
               &status[i], passenger[i], &ticket[i], berth[i]);

    for (int i = 0; i < wlCount; i++)
        fscanf(fp, "%s", wlName[i]);

    fclose(fp);
}

/* ---------- BOOKING ---------- */
void bookSeat() {
    char name[MAX_NAME], pref[3];

    printf("Passenger name: ");
    scanf(" %[^\n]", name);

    printf("Berth preference (L/M/U/SL/SU): ");
    scanf("%s", pref);

    // Try confirmed seat with preference
    for (int i = 0; i < TOTAL_SEATS; i++) {
        char temp[3];
        getBerthCode(i + 1, temp);

        if (status[i] == 0 && strcmp(pref, temp) == 0) {
            status[i] = CONFIRMED;
            strcpy(passenger[i], name);
            strcpy(berth[i], temp);
            ticket[i] = ticketCounter++;
            printf("CONFIRMED | Seat %d | Ticket %d | %s\n",
                   i + 1, ticket[i], berth[i]);
            saveData();
            return;
        }
    }

    // Try any confirmed seat
    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (status[i] == 0) {
            status[i] = CONFIRMED;
            strcpy(passenger[i], name);
            getBerthCode(i + 1, berth[i]);
            ticket[i] = ticketCounter++;
            printf("CONFIRMED | Seat %d | Ticket %d | %s\n",
                   i + 1, ticket[i], berth[i]);
            saveData();
            return;
        }
    }

    // RAC
    if (racCount < 2) {
        printf("RAC allotted | RAC No %d | Ticket %d\n",
               racCount + 1, ticketCounter);
        racCount++;
        ticketCounter++;
        saveData();
        return;
    }

    // Waiting List
    strcpy(wlName[wlCount++], name);
    printf("WAITING LIST | WL No %d\n", wlCount);
    saveData();
}

/* ---------- DISPLAY ---------- */
void viewSeats() {
    for (int i = 0; i < TOTAL_SEATS; i++) {
        printf("Seat %d: ", i + 1);
        if (status[i] == 0)
            printf("Available\n");
        else
            printf("Booked | %s | %s | Ticket %d\n",
                   passenger[i], berth[i], ticket[i]);
    }
    printf("RAC Count: %d\n", racCount);
    printf("Waiting List Count: %d\n", wlCount);
}

int main() {
    int ch;
    loadData();

    while (1) {
        printf("\n1.Book\n2.View\n3.Exit\nChoice: ");
        scanf("%d", &ch);

        if (ch == 1) bookSeat();
        else if (ch == 2) viewSeats();
        else if (ch == 3) {
            saveData();
            break;
        }
    }
    return 0;
}
