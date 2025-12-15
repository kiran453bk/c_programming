#include<stdio.h>
struct node {
    double a;
    char b;
    char c;
    char d;
    char e;
    

};
struct nodee{
    int data;
    struct nodee *next;

};
void main(){
    printf("size of %zu\n",sizeof(struct node));
    printf("size of %zu\n",sizeof(struct nodee));
}