#include <stdio.h>
#include <stdlib.h>

// Definition of node
struct node {
    int data;
    struct node *next;
};

// Function to count nodes
int countNodes(struct node *head) {
    int count = 0;
    struct node *temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

// Function to create a new node
struct node* createNode(int value) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

int main() {
    struct node *head = NULL, *temp = NULL;

    // Creating linked list: 10 -> 20 -> 30
    head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);

    printf("Number of nodes in the linked list: %d\n", countNodes(head));

    return 0;
}
