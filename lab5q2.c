#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sözlükteki her bir kural için bir struct oluşturuyoruz
typedef struct {
    char replaced[20]; // Kodlanan hali (Örn: $11$)
    char original[20]; // Orijinal kelime (Örn: pelle)
} Rule;

int main() {
    FILE *fptrSource, *fptrDic, *fptrOut;
    Rule dictionary[30]; // PDF'te S'nin max 30 olacağı söylenmiş
    int S; // Kural sayısı

    // 1. DOSYALARI AÇ VE KONTROL ET (Düz ve Temiz Mantık)
    fptrSource = fopen("ex2_source.txt", "r");
    fptrDic = fopen("ex2_dictionary.txt", "r");
    fptrOut = fopen("ex2_output.txt", "w");

    // Eğer herhangi biri açılamadıysa programı direkt bitir
    if (fptrSource == NULL || fptrDic == NULL || fptrOut == NULL) {
        printf("Dosyalardan biri veya birkaci acilamadi!\n");
        return 1;
    }

    // 2. SÖZLÜĞÜ (DICTIONARY) OKU
    // İlk satırdaki kural sayısını (S) okuyoruz
    fscanf(fptrDic, "%d", &S);

    // S kadar dönüp kuralları struct dizimize kaydediyoruz
    for (int i = 0; i < S; i++) {
        // Dosyadaki sıra: <replaced> <original> ($11$ pelle)
        fscanf(fptrDic, "%s %s", dictionary[i].replaced, dictionary[i].original);
    }

    // Okuma bittiğine göre sözlük dosyasını kapatabiliriz
    fclose(fptrDic);

    // Sözlüğün doğru okunduğunu test etmek için ekrana yazdıralım:
    printf("Sözlük basariyla okundu! %d kural bulundu.\n", S);
    for (int i = 0; i < S; i++) {
        printf("Orjinal: %s -> Kod: %s\n", dictionary[i].original, dictionary[i].replaced);
    }

    // --- ASIL ZOR KISIM BURADAN SONRA BAŞLAYACAK (Metni okuyup değiştirme) ---

    // Kapatmaları unutmuyoruz
    fclose(fptrSource);
    fclose(fptrOut);

    return 0;
}







