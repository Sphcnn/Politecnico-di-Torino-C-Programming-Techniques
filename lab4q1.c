#include <stdio.h>

void subSequebces( int h[], int n) {
    int printed = 1;
    int i = 0;
    int arrlen;
    arrlen= sizeof(h)/sizeof(h[0]);
    for (i = 0; i < arrlen; i++) {
        int tempArr[n];
        if (h[i]!=0) {
            if (i+n<=arrlen) {
                tempArr[0] = h[i];
                for (int j = 1;j<n;j++) {
                    if (h[i+j]!=0) {
                        tempArr[j] = h[i+j];
                    }
                    else {
                        for (int j = 0;j<n;j++) {
                            tempArr[j] = 0;
                        }
                    }
                for (int j = 0;j<n;j++) {
                    if (h[j]==0)
                        printed = 0;
                }
                if (printed == 1) {
                    for (int j = 0;j<n;j++) {
                        printf("%d\t",tempArr[j]);
                    }
                }


                }
            }
        }

    }
}





int main() {
    int nums[5];
    int arrlen;
    arrlen= sizeof(nums)/sizeof(nums[0]);
    printf("Enter number of elements in array\n");
    for (int i = 0; i < arrlen; i++) {
        int num ;
        scanf("%d",&num);
        nums[i] = num;
    }

    subSequebces( nums, 2);
}