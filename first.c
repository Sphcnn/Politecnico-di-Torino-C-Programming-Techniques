//
// Created by batus on 3.04.2026.
//

#include <stdio.h>

int main() {
    int num, i, j, space;
    scanf("%d",&num);

    if (num <1){printf("You have to input a number bigger than 2");}
    for (i=0; i<num; i++) {
        for (int k = 0; k<num-i-1; k++) {
            printf(" ");
        }
        for (j=(i*2)+1; j>0; j--) {
            printf("*");
        }
        printf("\n");
    }
}


