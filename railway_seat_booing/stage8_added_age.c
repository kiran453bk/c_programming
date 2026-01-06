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
    int age;
    char preference[6];   // LOWER / UPPER
    char coach[10];
    char berth[3];        // L M U SL SU
    char status[10];      // CONFIRMED / RAC / WL
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
    for (int i = 0; i < count; i++) {
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
        printf("1. Sleeper\n2. AC\n3. General\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: strcpy(coach, "Sleeper"); break;
            case 2: strcpy(coach, "AC"); break;
            case 3: strcpy(coach, "General"); break;
            default:
                printf("❌ Invalid coach selection\n");
                choice = 0;
        }
    } while (choice == 0);
}

void selectBerth(char berth[]) {
    int choice;
    do {
        printf("Select Berth Type:\n");
        printf("1.L  2.M  3.U  4.SL  5.SU\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: strcpy(berth, "L"); break;
            case 2: strcpy(berth, "M"); break;
            case 3: strcpy(berth, "U"); break;
            case 4: strcpy(berth, "SL"); break;
            case 5: strcpy(berth, "SU"); break;
            default:
                printf("❌ Invalid berth\n");
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

    printf("Enter Age: ");
    scanf("%d", &temp.age);

    if (temp.age < 60) {
        if (temp.age < 60) {
    selectPreference(temp.preference);
} else {
    strcpy(temp.preference, "LOWER");
    printf("Senior Citizen → Lower berth preference applied\n");
}

    } else {
        strcpy(temp.preference, "LOWER");
    }

    selectCoach(temp.coach);

    /* Try auto allotment first */
    if (strcmp(temp.preference, "LOWER") == 0)
        strcpy(temp.berth, "L");
    else
        strcpy(temp.berth, "U");

    /* If auto allotment not valid, ask manually */
    if (!validBerth(temp.coach, temp.berth)) {
        printf("Preferred berth not available. Select manually.\n");
        do {
            selectBerth(temp.berth);
        } while (!validBerth(temp.coach, temp.berth));
    }

    /* Status logic unchanged */
    if (confirmedCount() < SEATS)
        strcpy(temp.status, "CONFIRMED");
    else if (racCount() < RAC_LIMIT)
        strcpy(temp.status, "RAC");
    else if (wlCount() < WL_LIMIT)
        strcpy(temp.status, "WL");
    else {
        printf("❌ No tickets available\n");
        return;
    }

    temp.active = 1;
    p[count++] = temp;
    save();

    printf("✅ Ticket Booked | PNR:%d | Status:%s | Berth:%s\n",
           temp.ticket, temp.status, temp.berth);
}

void selectPreference(char pref[]) {
    int choice;
    do {
        printf("Seat Preference:\n");
        printf("1. LOWER\n");
        printf("2. UPPER\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: strcpy(pref, "LOWER"); break;
            case 2: strcpy(pref, "UPPER"); break;
            default:
                printf("❌ Invalid preference. Try again.\n");
                choice = 0;
        }
    } while (choice == 0);
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

/* ----------------- CANCEL ----------------- */
void cancel() {
    int t;
    printf("Enter Ticket Number: ");
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

/* ----------------- SEARCH ----------------- */
void search() {
    int t;
    printf("Enter Ticket Number: ");
    scanf("%d", &t);

    for (int i = 0; i < count; i++) {
        if (p[i].ticket == t && p[i].active) {
            printf("\nPNR:%d\nName:%s\nAge:%d\nPreference:%s\nCoach:%s\nBerth:%s\nStatus:%s\n",
                   p[i].ticket, p[i].name, p[i].age,
                   p[i].preference, p[i].coach,
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
            printf("PNR:%d | %s | Age:%d | Pref:%s | %s | %s | %s\n",
                   p[i].ticket, p[i].name, p[i].age,
                   p[i].preference, p[i].coach,
                   p[i].berth, p[i].status);
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
