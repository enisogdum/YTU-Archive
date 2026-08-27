# LAB 4 — İç İçe Kare Deseni

Kullanıcıdan **pozitif bir tam sayı `N`** alan ve ekrana **`N × N` boyutunda** iç içe geçmiş karelerden oluşan bir desen yazdıran C programını yazınız.

## Kurallar

Programın oluşturacağı desen şu kurallara göre çizilmelidir:

1. Desenin boyutu **`N × N`** olmalıdır.
2. En dıştaki kare, `N` uzunluğunda kenarlara sahip olmalı ve `*` karakterlerinden oluşmalıdır.
3. İçteki her yeni kare, bir önceki kareye göre **her yönde 2 birim küçülmelidir**.
   - Yani yeni karenin başlangıç satırı ve sütunu birer birim içeri kaymalıdır.
4. Her yeni kare, kendisini çevreleyen karenin kenarlarından **birer boşluk içeride** çizilmelidir.
5. Kareler, merkeze ulaşılana veya daha küçük bir kare çizmek için yeterli alan kalmayana kadar oluşturulmalıdır.
6. Karelerin dışında kalan ve çizilmeyen tüm alanlar **boşluk (`' '`)** karakteri ile doldurulmalıdır.
7. Karelerin kenarları `*` karakteri ile çizilmelidir.
8. Program, `N` değerinin tek veya çift olabileceği durumları dikkate almalıdır.

## Örnek 1

**Girdi:**
```text
N: 5

*****
*   *
* * *
*   *
*****