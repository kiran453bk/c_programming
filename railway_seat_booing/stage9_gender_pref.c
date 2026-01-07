#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 25
#define SEATS 10
#define RAC_LIMIT 2
#define WL_LIMIT 2

typedef struct {
    int ticket;
    char name[30];
    int age;
    char gender;          // M / F
    char preference[6];   // LOWER / UPPER
    char coach[10];
    char berth[3];        // L M U SL SU
    char status[10];      // CONFIRMED / RAC / WL
    int active;
} Passenger;

Passenger p[MAX];
int count = 0;

/* Queue pointers */
int racFront = 0, racRear = 0;
int wlFront  = 0, wlRear  = 0;

/* ----------- FUNCTION PROTOTYPES ----------- */
void selectPreference(char pref[]);

/* ---------------- FILE HANDLING ---------------- */
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

/* ---------------- UTILITY ---------------- */
int getTicketNumber() {
    for (int i = 0; i < count; i++)
        if (p[i].active == 0)
            return p[i].ticket;
    return 1001 + count;
}

int confirmedCount() {
    int c = 0;
    for (int i = 0; i < count; i++)
        if (p[i].active && strcmp(p[i].status, "CONFIRMED") == 0)
            c++;
    return c;
}

int validBerth(char coach[], char berth[]) {
    if (strcmp(coach, "Sleeper") == 0)
        return (!strcmp(berth,"L")||!strcmp(berth,"M")||
                !strcmp(berth,"U")||!strcmp(berth,"SL")||!strcmp(berth,"SU"));

    if (strcmp(coach, "AC") == 0)
        return (!strcmp(berth,"L")||!strcmp(berth,"U")||
                !strcmp(berth,"SL")||!strcmp(berth,"SU"));

    if (strcmp(coach, "General") == 0)
        return (!strcmp(berth,"L")||!strcmp(berth,"U"));

    return 0;
}

/* ---------------- MENU SELECTIONS ---------------- */
void selectCoach(char coach[]) {
    int ch;
    do {
        printf("Select Coach:\n1.Sleeper\n2.AC\n3.General\nChoice: ");
        scanf("%d",&ch);
        if (ch==1) strcpy(coach,"Sleeper");
        else if (ch==2) strcpy(coach,"AC");
        else if (ch==3) strcpy(coach,"General");
        else ch=0;
    } while(ch==0);
}

void selectBerth(char berth[]) {
    int ch;
    do {
        printf("Select Berth:\n1.L 2.M 3.U 4.SL 5.SU\nChoice: ");
        scanf("%d",&ch);
        if (ch==1) strcpy(berth,"L");
        else if (ch==2) strcpy(berth,"M");
        else if (ch==3) strcpy(berth,"U");
        else if (ch==4) strcpy(berth,"SL");
        else if (ch==5) strcpy(berth,"SU");
        else ch=0;
    } while(ch==0);
}

void selectPreference(char pref[]) {
    int ch;
    do {
        printf("Seat Preference:\n1.LOWER\n2.UPPER\nChoice: ");
        scanf("%d",&ch);
        if (ch==1) strcpy(pref,"LOWER");
        else if (ch==2) strcpy(pref,"UPPER");
        else ch=0;
    } while(ch==0);
}

/* ---------------- BOOK TICKET ---------------- */
void book() {
    Passenger temp;
    temp.ticket = getTicketNumber();

    printf("Name: ");
    scanf("%s", temp.name);

    printf("Age: ");
    scanf("%d", &temp.age);

    do {
        printf("Gender (M/F): ");
        scanf(" %c",&temp.gender);
    } while(temp.gender!='M' && temp.gender!='F');

    /* Priority logic */
    if (temp.age >= 60 || (temp.gender=='F' && temp.age>=45)) {
        strcpy(temp.preference,"LOWER");
        printf("Priority applied → LOWER berth\n");
    } else {
        selectPreference(temp.preference);
    }

    selectCoach(temp.coach);

    /* Auto-try preferred berth */
    if (!strcmp(temp.preference,"LOWER"))
        strcpy(temp.berth,"L");
    else
        strcpy(temp.berth,"U");

    /* If invalid, manual selection */
    if (!validBerth(temp.coach,temp.berth)) {
        printf("Preferred berth invalid. Select manually.\n");
        do {
            selectBerth(temp.berth);
        } while(!validBerth(temp.coach,temp.berth));
    }

    /* Status allocation (QUEUE BASED) */
    if (confirmedCount() < SEATS) {
        strcpy(temp.status,"CONFIRMED");
    }
    else if (racRear - racFront < RAC_LIMIT) {
        strcpy(temp.status,"RAC");
        racRear++;
    }
    else if (wlRear - wlFront < WL_LIMIT) {
        strcpy(temp.status,"WL");
        wlRear++;
    }
    else {
        printf("❌ No tickets available\n");
        return;
    }

    temp.active = 1;
    p[count++] = temp;
    save();

    printf("✅ Booked | PNR:%d | %s | Berth:%s\n",
           temp.ticket,temp.status,temp.berth);
}

/* ---------------- UPGRADE (FIFO) ---------------- */
void upgrade() {
    for (int i=0;i<count;i++) {
        if (p[i].active && !strcmp(p[i].status,"RAC")) {
            strcpy(p[i].status,"CONFIRMED");
            racFront++;

            for (int j=0;j<count;j++) {
                if (p[j].active && !strcmp(p[j].status,"WL")) {
                    strcpy(p[j].status,"RAC");
                    wlFront++;
                    return;
                }
            }
            return;
        }
    }
}

/* ---------------- CANCEL ---------------- */
void cancel() {
    int t;
    printf("Ticket No: ");
    scanf("%d",&t);

    for (int i=0;i<count;i++) {
        if (p[i].ticket==t && p[i].active) {
            p[i].active=0;
            printf("❌ Ticket Cancelled\n");
            upgrade();
            save();
            return;
        }
    }
    printf("Invalid Ticket\n");
}

/* ---------------- SEARCH ---------------- */
void search() {
    int t;
    printf("Ticket No: ");
    scanf("%d",&t);

    for (int i=0;i<count;i++) {
        if (p[i].ticket==t && p[i].active) {
            printf("\nPNR:%d\nName:%s\nAge:%d\nGender:%c\nPref:%s\nCoach:%s\nBerth:%s\nStatus:%s\n",
                   p[i].ticket,p[i].name,p[i].age,p[i].gender,
                   p[i].preference,p[i].coach,p[i].berth,p[i].status);
            return;
        }
    }
    printf("Not Found\n");
}

/* ---------------- DISPLAY ---------------- */
void display() {
    printf("\n--- BOOKINGS ---\n");
    for (int i=0;i<count;i++)
        if (p[i].active)
            printf("PNR:%d | %s | %d | %c | %s | %s | %s | %s\n",
                   p[i].ticket,p[i].name,p[i].age,p[i].gender,
                   p[i].preference,p[i].coach,p[i].berth,p[i].status);
}

/* ---------------- MAIN ---------------- */
int main() {
    int ch;
    load();

    do {
        printf("\n1.Book\n2.Cancel\n3.Search\n4.Display\n5.Exit\nChoice: ");
        scanf("%d",&ch);

        if (ch==1) book();
        else if (ch==2) cancel();
        else if (ch==3) search();
        else if (ch==4) display();

    } while(ch!=5);

    return 0;
}
