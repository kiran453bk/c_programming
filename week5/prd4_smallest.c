#include<stdio.h>
int main(){
    int a[25],n,i=0;
    int small;
    printf("enter the numbers of elements n:\n");
    scanf("%d",&n);
    printf("enter the array elements \n");
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    printf("array elements are below\n");
    for(i=0;i<n;i++){
        printf("%d\t",a[i]);
    }
    small=a[0];
    for(i=0;i<n;i++){
        if(small>a[i]){
            small=a[i];
        }
    }
        printf("smallest number is %d",small);
    
return 0;
}