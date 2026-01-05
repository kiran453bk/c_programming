#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define SEATS 10
#define RAC_LIMIT 2
#define WL_LIMIT 2

typedef struct {
    int ticket;
    char name[30];
    char coach[10];
    char berth[3];   // L M U SL SU
    char status[10]; // CONFIRMED / RAC / WL
    int active;
} Passenger;

Passenger p[MAX];
int count = 0;

/* ----------------- FILE HANDLING ----------------- */
void load() {
    FILE *fp = fopen("railway.dat", "rb");
    if (fp) {
        fread(&count, sizeof(int), 1, fp);
        fread(p, sizeof(Passenger), count, fp);
        fclose(fp);
    }
}

void save() {
    FILE *fp = fopen("railway.dat", "wb");
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(p, sizeof(Passenger), count, fp);
    fclose(fp);
}

/* ----------------- UTILITY ----------------- */
int getTicketNumber() {
    int i;
    for (i = 0; i < count; i++) {
        if (p[i].active == 0)
            return p[i].ticket;
    }
    return 1001 + count;
}

int confirmedCount() {
    int c = 0;
    for (int i = 0; i < count; i++)
        if (p[i].active && strcmp(p[i].status, "CONFIRMED") == 0)
            c++;
    return c;
}

int racCount() {
    int c = 0;
    for (int i = 0; i < count; i++)
        if (p[i].active && strcmp(p[i].status, "RAC") == 0)
            c++;
    return c;
}

int wlCount() {
    int c = 0;
    for (int i = 0; i < count; i++)
        if (p[i].active && strcmp(p[i].status, "WL") == 0)
            c++;
    return c;
}

int validBerth(char coach[], char berth[]) {

    if (strcmp(coach, "Sleeper") == 0) {
        if (strcmp(berth, "L") == 0 || strcmp(berth, "M") == 0 ||
            strcmp(berth, "U") == 0 || strcmp(berth, "SL") == 0 ||
            strcmp(berth, "SU") == 0)
            return 1;
    }

    if (strcmp(coach, "AC") == 0) {
        if (strcmp(berth, "L") == 0 || strcmp(berth, "U") == 0 ||
            strcmp(berth, "SL") == 0 || strcmp(berth, "SU") == 0)
            return 1;
    }

    if (strcmp(coach, "General") == 0) {
        if (strcmp(berth, "L") == 0 || strcmp(berth, "U") == 0)
            return 1;
    }

    return 0;
}

void selectCoach(char coach[]) {
    int choice;

    do {
        printf("Select Coach Type:\n");
        printf("1. Sleeper\n");
        printf("2. AC\n");
        printf("3. General\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: strcpy(coach, "Sleeper"); break;
            case 2: strcpy(coach, "AC"); break;
            case 3: strcpy(coach, "General"); break;
            default:
                printf("❌ Invalid coach selection. Try again.\n");
                choice = 0;
        }
    } while (choice == 0);
}

void selectBerth(char berth[]) {
    int choice;

    do {
        printf("Select Berth Type:\n");
        printf("1. L  (Lower)\n");
        printf("2. M  (Middle)\n");
        printf("3. U  (Upper)\n");
        printf("4. SL (Side Lower)\n");
        printf("5. SU (Side Upper)\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: strcpy(berth, "L");  break;
            case 2: strcpy(berth, "M");  break;
            case 3: strcpy(berth, "U");  break;
            case 4: strcpy(berth, "SL"); break;
            case 5: strcpy(berth, "SU"); break;
            default:
                printf("❌ Invalid berth selection. Try again.\n");
                choice = 0;
        }
    } while (choice == 0);
}

/* ----------------- BOOK TICKET ----------------- */
void book() {
    Passenger temp;
    temp.ticket = getTicketNumber();

    printf("Enter Name: ");
    scanf("%s", temp.name);

do {
    selectCoach(temp.coach);

    selectBerth(temp.berth);


    if (!validBerth(temp.coach, temp.berth)) {
        printf("❌ Invalid berth for selected coach. Re-enter.\n");
    }

} while (!validBerth(temp.coach, temp.berth));


    if (confirmedCount() < SEATS) {
        strcpy(temp.status, "CONFIRMED");
    }
    else if (racCount() < RAC_LIMIT) {
        strcpy(temp.status, "RAC");
    }
    else if (wlCount() < WL_LIMIT) {
        strcpy(temp.status, "WL");
    }
    else {
        printf("❌ No tickets available\n");
        return;
    }

    temp.active = 1;
    p[count++] = temp;

    printf("✅ Ticket Booked | PNR: %d | Status: %s\n",
           temp.ticket, temp.status);

    save();
}

/* ----------------- UPGRADE LOGIC ----------------- */
void upgrade() {
    for (int i = 0; i < count; i++) {
        if (p[i].active && strcmp(p[i].status, "RAC") == 0) {
            strcpy(p[i].status, "CONFIRMED");

            for (int j = 0; j < count; j++) {
                if (p[j].active && strcmp(p[j].status, "WL") == 0) {
                    strcpy(p[j].status, "RAC");
                    return;
                }
            }
            return;
        }
    }
}

/* ----------------- CANCEL TICKET ----------------- */
void cancel() {
    int t;
    printf("Enter Ticket Number to Cancel: ");
    scanf("%d", &t);

    for (int i = 0; i < count; i++) {
        if (p[i].ticket == t && p[i].active) {
            p[i].active = 0;
            printf("❌ Ticket %d Cancelled\n", t);
            upgrade();
            save();
            return;
        }
    }
    printf("Invalid Ticket Number\n");
}

/* ----------------- SEARCH (PNR) ----------------- */
void search() {
    int t;
    printf("Enter Ticket Number: ");
    scanf("%d", &t);

    for (int i = 0; i < count; i++) {
        if (p[i].ticket == t && p[i].active) {
            printf("\nPNR: %d\nName: %s\nCoach: %s\nBerth: %s\nStatus: %s\n",
                   p[i].ticket, p[i].name, p[i].coach,
                   p[i].berth, p[i].status);
            return;
        }
    }
    printf("Ticket Not Found\n");
}

/* ----------------- DISPLAY ----------------- */
void display() {
    printf("\n---- CURRENT BOOKINGS ----\n");
    for (int i = 0; i < count; i++) {
        if (p[i].active) {
            printf("PNR:%d | %s | %s | %s | %s\n",
                   p[i].ticket, p[i].name,
                   p[i].coach, p[i].berth, p[i].status);
        }
    }
}

/* ----------------- MAIN ----------------- */
int main() {
    int ch;
    load();

    do {
        printf("\n1.Book\n2.Cancel\n3.Search PNR\n4.Display\n5.Exit\n");
        scanf("%d", &ch);

        switch (ch) {
            case 1: book(); break;
            case 2: cancel(); break;
            case 3: search(); break;
            case 4: display(); break;
        }
    } while (ch != 5);

    return 0;
}
