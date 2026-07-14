#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXR 30
#define MAXC 30

void buildMatrix(int V[], int N, int M[MAXR][MAXC], int nR, int nC);

int main() {
int nR=3;
int nC=5;
int V[15] = {1, 2, 17, 2, 3, 1, 8, 4, 6, 1, 7, 3, 5, 2};
int M[MAXR][MAXC];
buildMatrix(V,14,M,nR,nC);
char name[10]="araba";
printf("%s\n : %d", name,strlen(name));

}
void buildMatrix(int V[], int N, int M[MAXR][MAXC], int nR, int nC) {
    int el;
    int elNum;
    int row=0;
    int column=0;
    for (int i = 0; i < N; i+=2) {
        el= V[i];
        elNum = V[i+1];
        while (elNum > 0) {
            M[row][column] = el;
            column++;
            elNum--;

            // Satır sonuna geldik mi diye kontrol et
            if (column == nC) {
                row++;
                column = 0;
            }
        }


    }

    for (int j = 0; j < nR; j++){
        for (int k = 0; k < nC; k++) {
            printf("%d ", M[j][k]);
        }
        printf("\n");
    }
}