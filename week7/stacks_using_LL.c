#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL;

// Check if stack is empty
int isEmpty() {
    if (top == NULL)
        return 1;
    else
        return 0;
}

// Check if stack is full (memory allocation fails)
int isFull() {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    if (temp == NULL)
        return 1;
    else {
        free(temp);
        return 0;
    }
}

// Push operation
void push(int value) {
    if (isFull()) {
        printf("Stack Overflow\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = top;
    top = newNode;

    printf("%d pushed into stack\n", value);
}

// Pop operation
void pop() {
    if (isEmpty()) {
        printf("Stack Underflow\n");
        return;
    }

    struct Node *temp = top;
    printf("%d popped from stack\n", temp->data);
    top = temp->next;
    free(temp);
}

// Display stack
void display() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }

    struct Node *temp = top;
    printf("Stack elements:\n");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function
int main() {
    int choice, value;

    while (1) {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. isEmpty\n");
        printf("4. isFull\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                pop();
                break;

            case 3:
                if (isEmpty())
                    printf("Stack is EMPTY\n");
                else
                    printf("Stack is NOT empty\n");
                break;

            case 4:
                if (isFull())
                    printf("Stack is FULL\n");
                else
                    printf("Stack is NOT full\n");
                break;

            case 5:
                display();
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
