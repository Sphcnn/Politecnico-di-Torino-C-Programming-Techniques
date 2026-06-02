#include <stdio.h>

void selectionSort(int arr[], int N) {
    int i, j, min_index, temp;

    // DIŞ DÖNGÜ (i): Hangi koltuğa (indekse) adam seçeceğimizi belirler
    for (i = 0; i < N - 1; i++) {

        // O turun başlangıç noktasını şimdilik "en küçük" kabul ediyoruz
        min_index = i;

        // İÇ DÖNGÜ (j): Geri kalanlar arasından GERÇEK en küçüğü arar
        for (j = i + 1; j < N; j++) {

            // Eğer varsaydığımızdan daha küçük biri varsa, sadece indeksini aklımızda tutarız!
            // YER DEĞİŞTİRME YOK!
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }


        if (min_index != i) {
            temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

void printArray(int arr[], int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {3, 6, 5, 1, 10, 9};
    int N = sizeof(arr) / sizeof(arr[0]);

    printf("Base Array: \n");
    printArray(arr, N);

    selectionSort(arr, N);

    printf("Sorted Array: \n");
    printArray(arr, N);

    return 0;
}