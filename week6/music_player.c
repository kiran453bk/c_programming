#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Song {
    char name[50];
    struct Song *prev;
    struct Song *next;
};

struct Song *head = NULL;
struct Song *current = NULL;

/* Add song to playlist */
void addSong(char song[]) {
    struct Song *newSong = (struct Song *)malloc(sizeof(struct Song));
    strcpy(newSong->name, song);
    newSong->prev = NULL;
    newSong->next = NULL;

    if (head == NULL) {
        head = newSong;
        current = newSong;
    } else {
        struct Song *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newSong;
        newSong->prev = temp;
    }
    printf("Song added: %s\n", song);
}

/* Play current song */
void playSong() {
    if (current == NULL)
        printf("Playlist is empty\n");
    else
        printf("Playing: %s\n", current->name);
}

/* Pause song */
void pauseSong() {
    if (current == NULL)
        printf("No song to pause\n");
    else
        printf("Paused: %s\n", current->name);
}

/* Next song */
void nextSong() {
    if (current == NULL || current->next == NULL)
        printf("No next song\n");
    else {
        current = current->next;
        playSong();
    }
}

/* Previous song */
void previousSong() {
    if (current == NULL || current->prev == NULL)
        printf("No previous song\n");
    else {
        current = current->prev;
        playSong();
    }
}

/* Display playlist */
void displayPlaylist() {
    if (head == NULL) {
        printf("Playlist empty\n");
        return;
    }

    struct Song *temp = head;
    printf("\nPlaylist:\n");
    while (temp != NULL) {
        if (temp == current)
            printf("-> %s (Current)\n", temp->name);
        else
            printf("   %s\n", temp->name);
        temp = temp->next;
    }
}

/* Main menu */
int main() {
    int choice;
    char song[50];

    while (1) {
        printf("\n--- Music Player ---\n");
        printf("1. Add Song\n");
        printf("2. Play\n");
        printf("3. Pause\n");
        printf("4. Next\n");
        printf("5. Previous\n");
        printf("6. Display Playlist\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
        case 1:
            printf("Enter song name: ");
            gets(song);
            addSong(song);
            break;
        case 2:
            playSong();
            break;
        case 3:
            pauseSong();
            break;
        case 4:
            nextSong();
            break;
        case 5:
            previousSong();
            break;
        case 6:
            displayPlaylist();
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
