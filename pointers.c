#include <stdio.h>
#define MaxArr 10
typedef struct {
    int sensorId;
    float speed;
    float temp;
} Telemetry;

void initPointers(Telemetry data[], Telemetry *refs[], int size);

void sortData(Telemetry *refs[], int size);


int main() {
    int size = 3;
    Telemetry data[size];
    data[0].sensorId = 1;
    data[1].sensorId = 2;
    data[2].sensorId = 3;
    data[0].speed = 1.5;
    data[1].speed = 2.5;
    data[2].speed = 3.5;
    data[0].temp = 1.5;
    data[1].temp = 2.5;
    data[2].temp = 3.5;
    Telemetry *refs[size];
    initPointers(data, refs, size);

}


void initPointers(Telemetry data[MaxArr], Telemetry *refs[MaxArr], int size) {
    for (int i = 0; i<size;i++) {
        refs[i] = &data[i];
    }
}

void sortData(Telemetry *refs[MaxArr], int size) {
    //Bu tarz yerlerde [] koysam sadece sıkıntı çıkıyor mu ?

    float speed1, speed2;
    Telemetry* temp;
    for (int i =0;i<size;i++) {
        if (i+1>size){}
        else {
            speed1 = (*refs[i]).speed;
            speed2 = (*refs[i+1]).speed;
            if (speed1<speed2) {
                temp = refs[i];
                refs[i] = refs[i+1];
                refs[i+1] = temp;

        }

        }
    }
    printf("Sorted datas according to speed");
    printf("\n");
    printf("-------------------------------------------\n\n");
    for (int i = 0; i<size;i++) {
        printf("%d- \t : \n --------------------------",i);
        printf("%d\n",refs[i]->sensorId);
        printf("%f\n",refs[i]->speed);
        printf("%f\n",refs[i]->temp);
    }


}