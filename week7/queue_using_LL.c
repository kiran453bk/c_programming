#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *next;
};

// Front and Rear pointers
struct Node *front = NULL;
struct Node *rear = NULL;

// Check if queue is empty
int isEmpty() {
    return (front == NULL);
}

// Enqueue operation
void enqueue(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Queue Overflow (Memory not allocated)\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    printf("%d enqueued successfully\n", value);
}

// Dequeue operation
void dequeue() {
    struct Node *temp;

    if (isEmpty()) {
        printf("Queue Underflow (Queue is empty)\n");
        return;
    }

    temp = front;
    printf("%d dequeued successfully\n", temp->data);
    front = front->next;

    if (front == NULL) {   // Queue becomes empty
        rear = NULL;
    }

    free(temp);
}

// Display queue elements
void display() {
    struct Node *temp;

    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }

    temp = front;
    printf("Queue elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function
int main() {
    int choice, value;

    while (1) {
        printf("\n--- Queue using Linked List ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
