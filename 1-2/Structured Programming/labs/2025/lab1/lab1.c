#include <stdio.h>
#include <locale.h>
#define MAX 100

int main() {
	setlocale(LC_ALL, "Turkish");
    int matris1[2][MAX], matris2[2][MAX];
    int N, M, i, j,k, toplam, ortak_sayi, deger1, deger2;
	int bayrak;
    
    printf("İlk matris (2xN) için N değerini girin: ");
    scanf("%d", &N);
    printf("İlk matris elemanlarını girin (ilk satır: sayılar, ikinci satır: değerler):\n");
    printf("ilk satır..\n");
    for (i = 0; i < N; i++) {
    	bayrak = 0;
        scanf("%d", (*(matris1) + i));
        for(k=0;k< i;k++){
        	if(*(*(matris1) + i) == *(*(matris1) + k)){
        		bayrak = 1;
			}
		}
		if(bayrak == 1){
			printf("Matrisin ilk satırı benzersiz olmalıdır..");
			i--;
		}        
		 
    }
    printf("ikinci satır..\n");
    for (i = 0; i < N; i++) {
        scanf("%d", (*(matris1 + 1) + i));
    }

    
    printf("İkinci matris (2xM) için M değerini girin: ");
    scanf("%d", &M);
    printf("İkinci matris elemanlarını girin (ilk satır: sayılar, ikinci satır: değerler):\n");
    printf("ilk satır..\n");
    for (i = 0; i < M; i++) {
        bayrak = 0;
        scanf("%d", (*(matris2) + i));
        for(k=0;k< i;k++){
        	if(*(*(matris2) + i) == *(*(matris2) + k)){
        		bayrak = 1;
			}
		}
		if(bayrak == 1){
			printf("Matrisin ilk satırı benzersiz olmalıdır..");
			i--;
		} 
    }
    printf("ikinci satır..\n");
    for (i = 0; i < M; i++) {
        scanf("%d", (*(matris2 + 1) + i));  
    }

    
    printf("\nOrtak sayılar ve toplamları:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (*(*(matris1) + i) == *(*(matris2) + j)) {  
                ortak_sayi = *(*(matris1) + i);
                deger1 = *(*(matris1 + 1) + i);
                deger2 = *(*(matris2 + 1) + j);
                toplam = deger1 + deger2;
                
                printf("%d -> %d + %d = %d\n", ortak_sayi, deger1, deger2, toplam);
            }
        }
    }

    return 0;
}
