#include <stdio.h>

#define MAX 100

int main() {
    int m, n; // Matris boyutları
    int matris[MAX][MAX];
    int ziyaret[MAX][MAX] = {0}; // Ziyaret edilen hücreleri takip etmek için
    int uzunluk[MAX] = {0}; // Her yolun uzunluğunu tutmak için
    int yol_no[MAX] = {0}; // Her yolun numarasını tutmak için
    int i,j;
    int start_row,current_row,current_col,current_length,current_path;
    int control=1;
    
    printf("gidilicek yolun boyutunu giriniz: \n");
scanf("%d %d",&m,&n);


    printf("Matrisi giriniz:\n");
    for ( i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &matris[i][j]);
        }
    }

    // Her yol için uzunluğu hesapla
    for (start_row = 0; start_row < m; start_row++) {
        if (matris[start_row][0] != 0) {
             current_row = start_row;
             current_col = 0;
             current_length = 0;
             current_path = matris[start_row][0];

            while (current_row < m && current_col < n && matris[current_row][current_col] != 0 && control==1) {
                current_length++;
                ziyaret[current_row][current_col] = 1;

                // Sağa  hareket
                if (current_col + 1 < n && matris[current_row][current_col] == matris[current_row][current_col + 1] && !ziyaret[current_row][current_col + 1]) {
                    current_col++;
                    control=1;
                }
                // Aşağı  hareket
                else if (current_row + 1 < m && matris[current_row][current_col] == matris[current_row + 1][current_col] && !ziyaret[current_row + 1][current_col]) {
                    current_row++;
                    control=1;
                }
                // Yukarı  hareket
                else if (current_row - 1 >= 0 && matris[current_row][current_col] == matris[current_row - 1][current_col] && !ziyaret[current_row - 1][current_col]) {
                    current_row--;
                    control=1;
                }
                // Çapraz (sağ alt) doğru hareket
                else if (current_row + 1 < m && current_col + 1 < n && matris[current_row][current_col] == matris[current_row + 1][current_col + 1] && !ziyaret[current_row + 1][current_col + 1]) {
                    current_row++, current_col++;
                    control=1;
                }
                // Çapraz (sol alt) doğru hareket
                else if (current_row + 1 < m && current_col - 1 >= 0 && matris[current_row][current_col] == matris[current_row + 1][current_col - 1] && !ziyaret[current_row + 1][current_col - 1]) {
                    current_row++, current_col--;
                    control=1;
                }
                // Çapraz (sağ üst) doğru hareket
                else if (current_row - 1 >= 0 && current_col + 1 < n && matris[current_row][current_col] == matris[current_row - 1][current_col + 1] && !ziyaret[current_row - 1][current_col + 1]) {
                    current_row--, current_col++;
                    control=1;
                }
                // Çapraz (sol üst) doğru hareket
                else if (current_row - 1 >= 0 && current_col - 1 >= 0 && matris[current_row][current_col] == matris[current_row - 1][current_col - 1] && !ziyaret[current_row - 1][current_col - 1]) {
                    current_row--, current_col--;
                    control=1;
                }
                else {
                    // Hiçbir yöne gidilemezse döngüyü sonlandır
                    control=0;
                }
            
            }
             control=1;
            // Eğer son sütuna ulaşıldıysa uzunluğu kaydet
            if (current_col == n - 1) {
                uzunluk[current_path] = current_length;
                yol_no[current_path] = current_path;
            }

            // Ziyaret dizisini sıfırla
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    ziyaret[i][j] = 0;
                }
            }
        }
    }

    // Sonuçları yazdır
    for (int i = 0; i < MAX; i++) {
        if (yol_no[i] != 0) {
            printf("Yol %d -> Uzunluk: %d\n", yol_no[i], uzunluk[i]);
        }
    }

    return 0;
}
