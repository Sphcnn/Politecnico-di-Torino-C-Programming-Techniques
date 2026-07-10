#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxTeam 20
#define maxDay 20




int main() {
    int teamNum, dayNum;
    printf("Enter how many teams you are playing with");
    scanf("%d",&teamNum);
    getchar();
    while (teamNum > maxTeam) {
        printf("You have to enter a number under %d",maxTeam);
        scanf("%d",&teamNum);
        getchar();
    }
    printf("Enter how many days you are playing");
    scanf("%d",&dayNum);
    getchar();
    while (dayNum > maxDay) {
        printf("You have to enter a number under %d",maxDay);
        scanf("%d",&dayNum);
        getchar();
    }
    int results[teamNum][dayNum];
    printf("Enter the results\n Write only w(win) t(tie) lose(l). ------ No matter what case it is\n------------------------------------------------------------\n");
    char result ;
    for (int i =0;i<teamNum;i++) {
        for(int j =0;j<dayNum;j++) {
            printf("The result of the game played with team number: %d on day: %d",i+1,j+1);
            scanf("%c",&result);
            result = tolower(result);
            switch (result) {
                case 'w':
                    results[i][j] = 3;
                    break;
                case 't':
                    results[i][j] = 1;
                    break;
                case 'l':
                    results[i][j] = 0;
                    break;
            }
        }
    }

    for (int i = 0; i<teamNum; i++) {
        int highest = 0;
        int indofHighest = 0 ;
        for (int j = 0; j<dayNum; j++) {
            if (results[i][j] > highest) {
                highest = results[i][j];
                indofHighest = j;
            }
            printf("%d",results[i][j]);
        }
        printf("\t\t\t Winner for this day  : %d with this point %d",indofHighest,highest);
        printf("\n");
    }

}