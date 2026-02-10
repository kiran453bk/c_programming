#include <stdio.h>
#include <stdlib.h>

// Self-referential structure
struct NODE {
    int data;
    struct NODE *next;
};

// Create a new node
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

// Insert node at the end
struct NODE* insertEnd(struct NODE *head, int value) {
    struct NODE *newNode = createNode(value);

    if (head == NULL)
        return newNode;

    struct NODE *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    return head;
}

// Display linked list to file
void displayToFile(struct NODE *head, FILE *fp) {
    struct NODE *temp = head;
    fprintf(fp, "Singly Linked List:\n");
    while (temp != NULL) {
        fprintf(fp, "%d -> ", temp->data);
        temp = temp->next;
    }
    fprintf(fp, "NULL\n");
}

int main() {
    FILE *fp_in, *fp_out;
    struct NODE *head = NULL;
    int n, value, i;

    // Open input file
    fp_in = fopen("input.txt", "r");
    if (fp_in == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    // Open output file
    fp_out = fopen("output.txt", "w");
    if (fp_out == NULL) {
        printf("Error opening output file!\n");
        fclose(fp_in);
        return 1;
    }

    // Read number of nodes
    fscanf(fp_in, "%d", &n);

    // Read node values
    for (i = 0; i < n; i++) {
        fscanf(fp_in, "%d", &value);
        head = insertEnd(head, value);
    }

    // Write output to file
    displayToFile(head, fp_out);

    // Close files
    fclose(fp_in);
    fclose(fp_out);

    return 0;
}
