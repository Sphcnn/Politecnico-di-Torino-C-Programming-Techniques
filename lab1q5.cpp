#include <stdio.h>


int main() {
    char op;
    float num1,num2;


    printf("Define your process");
    scanf("%f",&num1);
    scanf("%c",&op);
    scanf("%f",&num2);

        switch (op) {
            case '+':printf("%f",num1+num2);break;
            case '-':printf("%f",num1-num2);break;
            case '*':printf("%f",num1*num2);break;
            case '/':printf("%f",num1/num2);break;

        }

}