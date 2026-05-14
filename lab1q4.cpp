#include<stdio.h>

#define PI 3.14
int main() {

    char shape, type;
    int length;
    float result;

    printf("Define your process");
    scanf(" %c",&shape);
    scanf(" %c", &type);
    scanf("%d", &length);
    printf("%c , %c , %d",shape,type,length);

    switch (shape) {
        case 'S':
            switch (type) {
                case 'D':
                   if (length <= 0) {
                       printf("Not a valid shape");
                   }
                   else {
                       result = (float)(length*length)/2;
                       printf("The area of your shape is %.2f",result);
                   }
                    break;
                case 'E':
                    if (length <= 0) {
                        printf("Not a valid shape");
                    }
                    else {
                        result = (float)(length*length);
                        printf("The area of your shape is %.2f",result);

                    }
                    break;
            }
            break;
        case 'C':
                switch (type) {
                    case 'R':
                        if (length <= 0) {
                            printf("Not a valid shape");
                        }
                        else {
                            result = (length*length)*PI;
                            printf("The area of your shape is %.2f",result);
                        }
                        break;
                    case 'D':
                        if (length <= 0) {
                            printf("Not a valid shape");
                        }
                        else {
                            length = length/2;
                            result = (length*length)*PI;
                            printf("The area of your shape is %.2f",result);
                        }
                        break;


                }
                break;
    }

}