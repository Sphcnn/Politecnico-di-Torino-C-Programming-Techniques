#include <stdio.h>

// Fonksiyon sadece ekrana yazdıracağı için void yaptık
void calculator(int n, int numStep) {

    // Temel Durum (Base Case): Sayı 1'e ulaştıysa bitir
    if (n == 1) {
        printf("Process has been done. Number of steps = %d\n", numStep);
        return; // Fonksiyondan çık
    }

    // Sayı çiftse
    if (n % 2 == 0) {
        n = n / 2;
    }
    // Sayı tekse
    else {
        n = (n * 3) + 1;
    }

    // İşlem yapıldı, adım sayısını 1 artır
    numStep++;

    // Aynı fonksiyonu yeni değerlerle tekrar çağır
    calculator(n, numStep);
}

int main() {
    int n, numStep = 0; // numStep'i burada sıfırladık

    printf("Enter the number: ");
    scanf("%d", &n);

    calculator(n, numStep);

    return 0;
}