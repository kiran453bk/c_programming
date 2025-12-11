#include<stdio.h>
int main(){
    int a[25],n,i=0;
    int large;
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
    large=a[0];

    for(i=0;i<n;i++){
        if(large<a[i]){
            large=a[i];
        }
    }
        printf("largest number is %d",large);
    
return 0;
}