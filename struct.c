/*
#include<stdio.h>
#include<string.h>

struct student {
    char name[20];
    int age;
    char gender[20];
    float score;
};

typedef struct {
    char name[20];
    char surname[20];
    int age;
    char lecture[20];
} teacher;


int main() {


    struct student student1;
    printf("Enter student name: ");
    fgets(student1.name,20,stdin);
    student1.name[strcspn(student1.name, "\n")] = 0;
    printf("\n");

    printf("Enter the age of student:");
    scanf("%d",&student1.age);
    printf("\n");
    getchar();


    printf("Enter the gender of the student: ");
    fgets(student1.gender,20,stdin);
    student1.gender[strcspn(student1.gender, "\n")] = 0;
    printf("\n");

    printf("Enter the score of student: ");
    scanf("%f",&student1.score);



    printf("Informations for %s\n Age: %d\n Gender: %s\n Note: %f\n ",student1.name,student1.age,student1.gender,student1.score);


}
*/

#include<stdio.h>
#include<string.h>

typedef struct{
    char sensor_name[20];
    int id_number;
    float reliability;
}SensorData_t ;

int main() {
    SensorData_t sensors[3];
    int length = sizeof(sensors) / sizeof(sensors[0]);
    for (int i=0;i<length;i++) {
        if (sensors[i].reliability>=90) {
            printf("%s",sensors[i].sensor_name);
        }
    }
}




























