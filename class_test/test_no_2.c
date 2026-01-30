#include<stdio.h>
#include<stdlib.h>

struct NODE{
    
    int data;
    struct NODE* next;
};

struct NODE* createNode(int diff) {
    struct NODE *newNode = (struct NODE*)malloc(sizeof(struct NODE));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = diff;
    newNode->next = NULL;
    return newNode;
}

struct NODE* insertEnd(struct NODE *head, int diff){
    struct NODE *newNode = createNode(diff);

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

void display(struct NODE *head) {
    struct NODE *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main(){
    int n,i,diff,sum=0,avg;
    int arr[20];
    struct NODE *head =NULL;

    printf("Enter vaule of N : ");
    scanf("%d",&n);

    printf("Enter array elements\n");
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
        sum=sum+arr[i];
    }
    avg=sum/n;
    diff=0;
    for(i=0;i<n;i++){
        diff=avg-arr[i];
        head=insertEnd(head,diff);
    }
    printf("linked list \n");
    display(head);

    return 0;
}


