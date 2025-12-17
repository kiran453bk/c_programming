#include <stdio.h>
#include <stdlib.h>

// Doubly linked list node
struct NODE {
    int data;
    struct NODE *previous;
    struct NODE *next;
};

// Create node
struct NODE* createNode(int value) {
    struct NODE *newNode = (struct NODE*)malloc(sizeof(struct NODE));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->previous = NULL;
    newNode->next = NULL;
    return newNode;
}

// Insert at beginning
struct NODE* insertBeginning(struct NODE *head, int value) {
    struct NODE *newNode = createNode(value);
    if (head != NULL) {
        newNode->next = head;
        head->previous = newNode;
    }
    return newNode;
}

// Insert at end
struct NODE* insertEnd(struct NODE *head, int value) {
    struct NODE *newNode = createNode(value);
    if (head == NULL)
        return newNode;

    struct NODE *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->previous = temp;
    return head;
}

// Insert at middle (position)
struct NODE* insertAtPosition(struct NODE *head, int value, int pos) {
    if (pos == 1)
        return insertBeginning(head, value);

    struct NODE *temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Invalid position!\n");
        return head;
    }

    struct NODE *newNode = createNode(value);
    newNode->next = temp->next;
    newNode->previous = temp;

    if (temp->next != NULL)
        temp->next->previous = newNode;

    temp->next = newNode;
    return head;
}

// Delete from beginning
struct NODE* deleteBeginning(struct NODE *head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }

    struct NODE *temp = head;
    head = head->next;

    if (head != NULL)
        head->previous = NULL;

    free(temp);
    return head;
}

// Delete from end
struct NODE* deleteEnd(struct NODE *head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }

    struct NODE *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    if (temp->previous != NULL)
        temp->previous->next = NULL;
    else
        head = NULL;

    free(temp);
    return head;
}

// Delete from middle (position)
struct NODE* deleteAtPosition(struct NODE *head, int pos) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }

    if (pos == 1)
        return deleteBeginning(head);

    struct NODE *temp = head;
    for (int i = 1; i < pos && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Invalid position!\n");
        return head;
    }

    temp->previous->next = temp->next;
    if (temp->next != NULL)
        temp->next->previous = temp->previous;

    free(temp);
    return head;
}

// Display list
void display(struct NODE *head) {
    struct NODE *temp = head;
    printf("NULL <-> ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function
int main() {
    struct NODE *head = NULL;
    int choice, value, pos;

    do {
        printf("\n--- DOUBLY LINKED LIST MENU ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at Middle\n");
        printf("3. Insert at End\n");
        printf("4. Delete from Beginning\n");
        printf("5. Delete from Middle\n");
        printf("6. Delete from End\n");
        printf("7. Display\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value: ");
            scanf("%d", &value);
            head = insertBeginning(head, value);
            break;

        case 2:
            printf("Enter value and position: ");
            scanf("%d %d", &value, &pos);
            head = insertAtPosition(head, value, pos);
            break;

        case 3:
            printf("Enter value: ");
            scanf("%d", &value);
            head = insertEnd(head, value);
            break;

        case 4:
            head = deleteBeginning(head);
            break;

        case 5:
            printf("Enter position: ");
            scanf("%d", &pos);
            head = deleteAtPosition(head, pos);
            break;

        case 6:
            head = deleteEnd(head);
            break;

        case 7:
            display(head);
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}
