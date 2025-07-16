#include <stdio.h>
#define dizi_size 100

int main() {
    int n, i, k;
    int ucak_numara[dizi_size], ucak_saat[dizi_size];
    int pist1_ucak[dizi_size] = {0}, pist1_saat[dizi_size] = {0};
    int pist2_ucak[dizi_size] = {0}, pist2_saat[dizi_size] = {0};
    int pist1_gecikme[dizi_size] = {0}, pist2_gecikme[dizi_size] = {0};
    int pist1_sayi = 0, pist2_sayi = 0;
    int pist1_toplam_gecikme = 0, pist2_toplam_gecikme = 0;

    // Uçak sayısını al
    printf("Kaç adet uçak bulunmaktadır? : \n");
    scanf("%d", &n);

    // Uçak numaraları ve kalkış saatlerini al
    printf("Uçak numaralarını ve kalkış saatlerini giriniz : \n");
    for (i = 0; i < n; i++) {
        printf("%d. uçak numarasını giriniz: ", i + 1);
        scanf("%d", &ucak_numara[i]);
        printf("%d. uçak kalkış saatini dakika cinsinden giriniz: ", i + 1);
        scanf("%d", &ucak_saat[i]);
    }

    // Kalkış aralığını al
    printf("Kaç dakika arayla uçaklar kalksın? : \n");
    scanf("%d", &k);

    // Uçakları pistlere yerleştirme
    for (i = 0; i < n; i++) {
        if (i % 2 == 0) { // Pist 1
            pist1_ucak[pist1_sayi] = ucak_numara[i];
            pist1_saat[pist1_sayi] = ucak_saat[i];
            if (pist1_sayi > 0 && pist1_saat[pist1_sayi - 1] + k > pist1_saat[pist1_sayi]) {
                pist1_gecikme[pist1_sayi] = (pist1_saat[pist1_sayi - 1] + k) - pist1_saat[pist1_sayi];
                pist1_saat[pist1_sayi] = pist1_saat[pist1_sayi - 1] + k;
                pist1_toplam_gecikme = pist1_toplam_gecikme+pist1_gecikme[pist1_sayi];
            }
            pist1_sayi++;
        } else { // Pist 2
            pist2_ucak[pist2_sayi] = ucak_numara[i];
            pist2_saat[pist2_sayi] = ucak_saat[i];
            if (pist2_sayi > 0 && pist2_saat[pist2_sayi - 1] + k > pist2_saat[pist2_sayi]) {
                pist2_gecikme[pist2_sayi] = (pist2_saat[pist2_sayi - 1] + k) - pist2_saat[pist2_sayi];
                pist2_saat[pist2_sayi] = pist2_saat[pist2_sayi - 1] + k;
                pist2_toplam_gecikme =pist2_toplam_gecikme+ pist2_gecikme[pist2_sayi];
            }
            pist2_sayi++;
        }
    }

    // Pist 1 sonuçlarını yazdır
    printf("Pist 1 için uçaklar:\n");
    for (i = 0; i < pist1_sayi; i++) {
        printf("Uçak: %d, Kalkış saati: %d, Gecikme: %d\n", pist1_ucak[i], pist1_saat[i], pist1_gecikme[i]);
    }
    if (pist1_sayi > 0) {
        printf("Pist 1 ortalama gecikme: %.2f\n", (float)pist1_toplam_gecikme / pist1_sayi);
    } else {
        printf("Pist 1'de uçak bulunmamaktadır.\n");
    }

    // Pist 2 sonuçlarını yazdır
    printf("Pist 2 için uçaklar:\n");
    for (i = 0; i < pist2_sayi; i++) {
        printf("Uçak: %d, Kalkış saati: %d, Gecikme: %d\n", pist2_ucak[i], pist2_saat[i], pist2_gecikme[i]);
    }
    if (pist2_sayi > 0) {
        printf("Pist 2 ortalama gecikme: %.2f\n", (float)pist2_toplam_gecikme / pist2_sayi);
    } else {
        printf("Pist 2'de uçak bulunmamaktadır.\n");
    }

    return 0;
}