#include <stdio.h>
#include <stdlib.h>

// Self-referential structure
struct NODE {
    int data;
    struct NODE *previous;
    struct NODE *next;  // Self-referential pointer
};

// Function to create a new node
struct NODE *createNode(int value) {
    struct NODE *newNode = (struct NODE*)malloc(sizeof(struct NODE));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->previous=NULL;
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
    newNode->previous=temp;
    return head;
}

void asc(struct NODE *head){
    struct NODE *temp = head;
    struct NODE *previous=NULL;
    int temp2;
    if(head==NULL){
        printf("empty linked list\n");
        exit(1);
    }
    while(temp!=NULL){
        if(temp->data >previous->data){
            temp2=temp->data;
            temp->data=previous->data;
            previous->data=temp2;

        }
        temp=temp->next;
    }
    
}

// Function to display the list
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
    
    int n, value, i;
    int choice;


    printf("How many nodes? ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &value);
        head = insertEnd(head, value);
    }

    printf("\nDoubly Linked List:\n");
    display(head);
    printf("enter the choice\n");
    printf("enter 1:ascending\n 2:descending\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:asc(head);
    display(head);
        
        break;
    
    default:printf("enter correct choice");
        break;
    }


    return 0;
}
