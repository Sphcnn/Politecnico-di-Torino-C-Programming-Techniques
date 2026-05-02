#include <stdio.h>

int gcd(int a, int b) {
    // Temel durum: kalan sıfırsa işlem biter.
    if (b == 0) {
        return a;
    }
    // Değilse, (b) ve (a'nın b'ye bölümünden kalan) ile devam et.
    else {
        return gcd(b, a % b);
    }
}

int main() {
    int a, b;
    printf("Enter a value for a: ");
    scanf("%d", &a);
    printf("Enter a value for b: ");
    scanf("%d", &b);

    // Dönen sonucu bir değişkende tutup veya direkt printf içinde yazdırıyoruz:
    printf("Greatest Common Divisor (EBOB): %d\n", gcd(a, b));

    return 0;
}