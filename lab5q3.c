#include <stdio.h>
#include <string.h>

#define maxN 30

void rotate(int h[maxN][maxN], int r, int c, char selector[], int index, char direction[], int positions) {
    int tempArr[maxN];
    int actual_idx = index - 1; // Kullanıcı 1 girdiğinde C için 0. indekstir

    if (strcmp(selector, "row") == 0) {
        // --- SATIR KAYDIRMA ---
        positions = positions % c; // Gereksiz turları önlemek için mod al

        // 1. Satırı önce geçici bir diziye (tempArr) güvenle alalım
        for (int i = 0; i < c; i++) {
            tempArr[i] = h[actual_idx][i];
        }

        // 2. Temp dizisindeki elemanları, yeni yerlerini hesaplayarak (mod ile) ana matrise geri yazalım
        for (int i = 0; i < c; i++) {
            int new_i;
            if (strcmp(direction, "right") == 0) {
                new_i = (i + positions) % c;
            } else if (strcmp(direction, "left") == 0) {
                new_i = (i - positions + c) % c;
            }
            h[actual_idx][new_i] = tempArr[i];
        }

    } else if (strcmp(selector, "column") == 0) {
        // --- SÜTUN KAYDIRMA ---
        positions = positions % r;

        // 1. Sütunu geçici diziye al
        for (int i = 0; i < r; i++) {
            tempArr[i] = h[i][actual_idx];
        }

        // 2. Kaydırarak geri yaz
        for (int i = 0; i < r; i++) {
            int new_i;
            if (strcmp(direction, "down") == 0) {
                new_i = (i + positions) % r;
            } else if (strcmp(direction, "up") == 0) {
                new_i = (i - positions + r) % r;
            }
            h[new_i][actual_idx] = tempArr[i];
        }
    }

    // İşlem bittikten sonra matrisi yazdır
    printf("\nSonuc:\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", h[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char filename[25];
    printf("Dosya adini girin: ");
    scanf("%s", filename);

    FILE *fptr = fopen(filename, "r"); // "w" DEĞİL, "r" OLMALI!
    if (fptr == NULL) {
        printf("Dosya bulunamadi!\n");
        return 1;
    }

    int row, column;
    fscanf(fptr, "%d %d", &row, &column);

    int table[maxN][maxN]; // Fonksiyonla uyumlu olması için maxN ile tanımladık

    // Matrisi dosyadan oku
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            fscanf(fptr, "%d", &table[i][j]);
        }
    }
    fclose(fptr); // Okuma bitti, kapat.

    // Komut döngüsü
    char selector[10];
    int index, positions;
    char direction[10];

    while (1) {
        printf("\nKomut girin (Orn: row 2 right 1) veya bitirmek icin 'end' yazin:\n");

        // Sadece ilk kelimeyi okuyup ne olduğuna karar veriyoruz
        scanf("%s", selector);

        // Eğer kullanıcı "end" yazdıysa döngüyü ve programı bitir
        if (strcmp(selector, "end") == 0) {
            printf("Program sonlandirildi.\n");
            break;
        }

        // Eğer "end" değilse, komutun geri kalanını da oku
        scanf("%d %s %d", &index, direction, &positions);

        // Rotasyon fonksiyonumuzu çağır
        rotate(table, row, column, selector, index, direction, positions);
    }

    return 0;
}