#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int sensorID;
    char streetName[50];
    int carNumber;
    float averageSpeed;
} TrafficData;

int readData(FILE* filePointer, TrafficData list[], int max_size);
void sortTraffic(TrafficData list[], TrafficData *refs[], int size);

int main() {
    TrafficData datas[100];
    TrafficData *refs[100];
    int size;

    FILE* fptr = fopen("matches.txt", "r");
    if (fptr == NULL) {
        printf("File not found\n");
        return 1;
    }

    size = readData(fptr, datas, 100);
    sortTraffic(datas, refs, size);

    fclose(fptr);
    return 0;
}

int readData(FILE* filePointer, TrafficData datas[], int max_size) {
    int i = 0;
    while (i < max_size && fscanf(filePointer, "%d %s %d %f", &datas[i].sensorID, datas[i].streetName, &datas[i].carNumber, &datas[i].averageSpeed) != EOF) {
        i++;
    }
    return i;
}

void sortTraffic(TrafficData list[], TrafficData *refs[], int size) {
    TrafficData* temp;

    for (int i = 0; i < size; i++) {
        refs[i] = &list[i];
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (refs[j]->carNumber < refs[j+1]->carNumber) {
                temp = refs[j];
                refs[j] = refs[j+1];
                refs[j+1] = temp;
            }
        }
    }

    int printCount = (size < 3) ? size : 3;
    for (int i = 0; i < printCount; i++) {
        printf("%d------------%d\t%s\t%d\t%.2f\n", i + 1, refs[i]->sensorID, refs[i]->streetName, refs[i]->carNumber, refs[i]->averageSpeed);
    }
}