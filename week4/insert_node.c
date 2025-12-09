#include <stdio.h>
#include <stdlib.h>

// Self-referential structure
struct NODE {
    int data;
    struct NODE *next;   // Self-referential pointer
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

// Function to insert node at the end
struct NODE* insertEnd(struct NODE *head, int value) {
    struct NODE *newNode = createNode(value);

    if (head == NULL) {
        return newNode;
    }

    struct NODE *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

// Function to insert node at the front
struct NODE* insertFront(struct NODE *head, int value) {
    struct NODE *newNode = createNode(value);
    newNode->next = head;
    return newNode;
}

// Function to insert node at a specific position (middle)
// Position starts from 1 (front)
struct NODE* insertMiddle(struct NODE *head, int value, int position) {
    if (position == 1) {
        return insertFront(head, value);
    }

    struct NODE *newNode = createNode(value);
    struct NODE *temp = head;

    // Traverse to the node before the insertion point
    for (int i = 1; i < position - 1; i++) {
        if (temp == NULL) {
            printf("Position out of range. Inserting at end.\n");
            return insertEnd(head, value);
        }
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

// Function to display the list
void display(struct NODE *head) {
    struct NODE *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function
int main() {
    struct NODE *head = NULL;
    int n, value, i, choice, pos;

    printf("How many nodes to initially create? ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &value);
        head = insertEnd(head, value);
    }

    printf("\nSingly Linked List:\n");
    display(head);

    while (1) {
        printf("\nInsert a new node:\n");
        printf("1. At Front\n2. At Middle/Specific Position\n3. At End\n4. Display List\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                head = insertFront(head, value);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                printf("Enter position (1-based index): ");
                scanf("%d", &pos);
                head = insertMiddle(head, value, pos);
                break;
            case 3:
                printf("Enter value: ");
                scanf("%d", &value);
                head = insertEnd(head, value);
                break;
            case 4:
                printf("\nSingly Linked List:\n");
                display(head);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
