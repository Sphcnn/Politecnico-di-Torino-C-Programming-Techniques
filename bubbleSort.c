#include <stdio.h>
void bubbleSort(int A[], int N) {
    int i, j, temp;
    int flag = 1; // Başlangıçta döngüye girebilmek için bayrağı 1 (havada) başlatıyoruz.

    // DIŞ DÖNGÜ: Turları sayar.
    // DİKKAT: Döngünün dönmeye devam etmesi için flag'in 1 olması ŞART!
    for (i = 1; i < N && flag == 1; i++) {

        flag = 0; // Tura başlarken bayrağı indiriyoruz. Başta indiriyoruyz bayrağı bulursak kaldırıcaz geri.

        // İÇ DÖNGÜ: Yan yana komşuları kıyaslar
        // Sınırımız N-i çünkü her turda en sağdaki 1 eleman zaten kilitleniyor.
        for (j = 0; j < N - i; j++) {

            if (A[j] > A[j+1]) {
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
                flag = 1; // değişiklik olduğu için flag tekrar 1 aramaya devam
            }
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
    int arr[] = {3, 6, 5, 1, 7, 9};
    int N = sizeof(arr) / sizeof(arr[0]); // Boyutu main içinde hesaplıyoruz

    printf("Base Array: \n");
    printArray(arr, N);

    bubbleSort(arr, N); // Diziyi ve boyutu fonksiyona yolluyoruz

    printf("Sorted Array: \n");
    printArray(arr, N);

    return 0;
}
