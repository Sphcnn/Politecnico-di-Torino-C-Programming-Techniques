#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define maxDim 10
void subMatrices(int h[maxDim][maxDim], int n, int d) {

    int biggestArr[d][d];
    int i,j;
    int biggest = 0;
    for (i = 0;i<n;i++) {
        for (j=0;j<n;j++) {
            int sum = 0;
            int tempArr[d][d];
            if (i+d-1>n || j+d-1>n) {
                continue;
            }
            else {

                for (int k=0;k<d;k++) {
                    int inc = 0;
                    for (int a = 0;a<d;a++) {
                        tempArr[k][a] = h[k+i][j+a];
                        sum = sum + tempArr[k][a];
                        inc++;
                    }
                }
                for (int k=0;k<d;k++) {
                    for (int a=0;a<d;a++) {
                        printf("%d\t",tempArr[k][a]);
                    }
                    printf("\n");
                }
                if (sum>biggest) {
                    biggest = sum;
                    for (int k=0;k<d;k++) {
                        for (int a=0;a<d;a++) {
                            biggestArr[k][a] = tempArr[k][a];
                        }
                    }
                }
            }
        }
    }
    printf("Biggest sum submatrix with sum(%d): ",biggest);
    for (int i =0;i<d;i++) {
        for (int j=0;j<d;j++) {
            printf("%d\t",biggestArr[i][j]);
        }
    }

}



int main() {
    int dim,subDim;
    printf("Enter the length of square matrix: ");
    scanf("%d", &dim);
    int arr[dim][dim];

    for (int i =0;i<dim;i++) {
        for (int j = 0;j<dim;j++) {
            int element ;
            printf("Enter the element for Row: %d Column: %d :  ",i+1,j+1);
            scanf("%d", &element);
            arr[i][j] = element;
        }
    }
    printf("Enter the dimension of subsequences you want to see : ");
    scanf("%d", &subDim);
    while (1){
        if (subDim>dim) {
            printf("You entered a bigger number than your matrixes dim : %d ",dim);
            break;
        }
        else if (subDim == dim) {
            int sum=0;
            for (int i =0;i<dim;i++) {
                for (int j = 0;j<dim;j++) {
                    sum = sum + arr[i][j];
                    printf("%d\t",arr[i][j]);
                    printf("\n");
                    printf("Sum of all elements : %d",sum);
                }
            }
            break;
        }
        else if (subDim == 1) {
            int biggest = 0;
            printf("All of sub matrixes are : ");
            for (int i =0;i<dim;i++) {
                for (int j = 0;j<dim;j++) {
                    printf("%d\n",arr[i][j]);
                    if (arr[i][j]>biggest) {
                        biggest = arr[i][j];
                    }
                }
            }
            printf("Biggest sum submatrix : %d",biggest);
            break;
        }
        else {
            printf("All of sub matrixes are : ");
            subMatrices(arr, dim, subDim);
            break;
        }
    }



}