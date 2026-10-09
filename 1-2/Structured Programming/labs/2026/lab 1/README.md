# Lab 1 — NxN Matris: Local Maximum Finder

## Problem Tanımı

Kullanıcıdan **dinamik bellek tahsisi (dynamic allocation)** ile alınan **N×N** boyutunda bir tamsayı matrisi üzerinde işlem yapan bir C programı yazınız.

### Görev

Program aşağıdaki işlemleri gerçekleştirmelidir:

1. Kullanıcıdan matrisin boyutunu (`N`) alınız.
2. `malloc` kullanarak **N×N**'lik bir 2D dizi dinamik olarak tahsis ediniz.
3. Kullanıcıdan matrisin elemanlarını okuyunuz.
4. Her bir elemanı **pointer aritmetiği** (`*(*(mat+i)+j)`) ile gezerek, o elemanın dört komşusundan (üst, alt, sol, sağ) **hepsinden büyük** olup olmadığını kontrol ediniz.
5. Koşulu sağlayan (yerel maksimum olan) elemanların **değerini ve konumunu** ekrana yazdırınız.
6. Tüm yerel maksimum elemanların toplamını hesaplayıp ekrana yazdırınız.
7. Programın sonunda tahsis edilen belleği `free` ile serbest bırakınız.

### Kısıtlar

- Matris elemanlarına **yalnızca pointer mantığı** ile erişilmelidir (`mat[i][j]` notasyonu kullanılmamalıdır).
- Bellek sızıntısı olmamalıdır; tüm `malloc` çağrıları karşılık gelen `free` ile eşleştirilmelidir.

### Yerel Maksimum Koşulu

Bir `mat[i][j]` elemanı yerel maksimum sayılır eğer:

- Üst komşusu varsa: `mat[i][j] > mat[i-1][j]`
- Alt komşusu varsa: `mat[i][j] > mat[i+1][j]`
- Sol komşusu varsa: `mat[i][j] > mat[i][j-1]`
- Sağ komşusu varsa: `mat[i][j] > mat[i][j+1]`

> Matrisin kenar veya köşe elemanları için olmayan komşular göz ardı edilir.

### Örnek Çalışma

```
Matrisin boyutunu giriniz:
3
Matrisinizi giriniz:
1 2 3
4 9 6
7 8 5

Deger:9 , Konum: (1,1)
Toplam:9
```

## Çözüm

Çözüm kodu [`kod.c`](./kod.c) dosyasında yer almaktadır.
