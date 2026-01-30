#include <stdio.h>
#include <stdlib.h>

// Self-referential structure
struct NODE {
    int data;
    struct NODE *next;
};

// Function to create a new node
struct NODE* createNode(int value) {
    struct NODE *newNode = (struct NODE*)malloc(sizeof(struct NODE));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Insert node at end
struct NODE* insertEnd(struct NODE *head, int value) {
    struct NODE *newNode = createNode(value);
    if (head == NULL) return newNode;

    struct NODE *temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return head;
}

// Display linked list
void display(struct NODE *head) {
    struct NODE *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Read linked list from file
struct NODE* readFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return NULL; // file may not exist yet

    struct NODE *head = NULL;
    int value;
    while (fscanf(fp, "%d", &value) == 1) {
        head = insertEnd(head, value);
    }
    fclose(fp);
    return head;
}

// Write linked list to file (overwrite with latest list)
void writeToFile(struct NODE *head, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    struct NODE *temp = head;
    while (temp != NULL) {
        fprintf(fp, "%d\n", temp->data);
        temp = temp->next;
    }
    fclose(fp);
}

int main() {
    struct NODE *head = NULL;
    int n, value, i;
    const char *filename = "linkedlist_output.txt";

    // Step 1: Load existing linked list from file
    head = readFromFile(filename);

    printf("Existing Linked List:\n");
    if (head == NULL) printf("Empty list.\n");
    else display(head);

    // Step 2: Add new nodes
    printf("\nHow many new nodes to add? ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &value);
        head = insertEnd(head, value);
    }

    // Step 3: Show updated list
    printf("\nUpdated Linked List:\n");
    display(head);

    // Step 4: Save updated list back to file
    writeToFile(head, filename);

    return 0;
}