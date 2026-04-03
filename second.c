//
// Created by batus on 3.04.2026.
//
#include<stdio.h>

int main() {
    int num,i,j,k;
    printf("Enter the number : ");
    scanf("%d",&num);

    for (i=1;i<=num;i++) {
        if (i==num || i == 1) {
            for (j =1; j<=num;j++) {
                printf("*");
            }
            printf("\n");
        }
        else {
            printf("*");
            for(k=1;k<=num-2;k++) {
                printf(" ");
            }
            printf("*");
            printf("\n");
        }
    }

}