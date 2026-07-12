#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char name[50];
    char character[50];
    int kill;
    int death;
    float combatScore;
}PlayerStat;

void analysis(PlayerStat list[], int size);

int main() {
    PlayerStat players[50];
    FILE* fptr;
    fptr = fopen("matches.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file");
    }
    else {
        printf("File has been opened succesfuly");
        char myLetter = fgetc(fptr);
        int fileSize = 1;
        while (myLetter != EOF) {
            if (myLetter == '\n') {
                   fileSize++;
            }
            myLetter = fgetc(fptr);
        }
        rewind(fptr);
        for (int i = 0;i<fileSize;i++) {
            fscanf(fptr,"%s %s %d %d %f",players[i].name,players[i].character,&players[i].kill,&players[i].death,&players[i].combatScore);
        }
        analysis(players,fileSize);
        fclose(fptr);
    }
}

void analysis(PlayerStat list[], int size) {
    for (int i = 0;i<size;i++) {
        float kda;
        float killF, deathF;
        killF = (float)(list[i].kill);
        deathF = (float)(list[i].death);
        kda = killF/deathF;
        printf("Player Name : %s -------------------->>>>>>>>> KD :%.2f",list[i].name,kda);
        printf("\n");
    }
}