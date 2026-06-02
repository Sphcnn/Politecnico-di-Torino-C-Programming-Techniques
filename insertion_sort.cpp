#include <stdio.h>

// Diziyi ve dizinin boyutunu (N) parametre olarak alıyoruz
void insertionSort(int arr[], int N) {
    int i, j, x;

    // i = 1'den başlıyor çünkü 0. indeksteki eleman zaten sıralı kabul ediliyor
    for (i = 1; i < N; i++) {
        x = arr[i]; // Sağdaki sırasız kısımdan çektiğimiz yeni iskambil kağıdı
        j = i - 1;  // Sol eldeki sıralı destenin en sağındaki kartın indeksi

        // j, 0'dan büyük/eşit olduğu sürece VE solumuzdaki kart çektiğimiz karttan (x) büyükse:
        while (j >= 0 && arr[j] > x) {
            arr[j + 1] = arr[j]; // Büyük olan kartı bir adım sağa kaydır
            j--;                 // Bir soldaki karta geç
        }

        // Kaydırma işlemi bitti. Açılan boşluğa elimizdeki kartı (x) yerleştiriyoruz.
        arr[j + 1] = x;
    }
}

// Diziyi ekrana yazdırmak için yardımcı fonksiyon
void printArray(int arr[], int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {3, 6, 5, 1, 7, 9};
    int N = sizeof(arr) / sizeof(arr[0]); // Boyutu main içinde hesaplıyoruz

    printf("Base Array: \n");
    printArray(arr, N);

    insertionSort(arr, N); // Diziyi ve boyutu fonksiyona yolluyoruz

    printf("Sorted Array: \n");
    printArray(arr, N);

    return 0;
}
