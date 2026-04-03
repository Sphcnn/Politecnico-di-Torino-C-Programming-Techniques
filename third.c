//
// Created by batus on 3.04.2026.
//


#include <stdio.h>

    int main() {
        int num, sayici = 1;
        printf("Satir sayisini giriniz: ");
        scanf("%d", &num);

        // i satır numarasını temsil eder
        for (int i = 1; i <= num; i++) {
            // j o satırdaki kaçıncı sayıyı bastığımızı temsil eder
            for (int j = 1; j <= i; j++) {
                printf("%d ", sayici);
                sayici++; // Sayıyı bastıktan sonra 1 artırıyoruz
            }
            printf("\n"); // Satır bitti, alt satıra geç
        }

        return 0;
    }