# Lab 2 — Staj Adayı Seçim Sistemi

## Veri Yapısı

```c
typedef struct {
    int no;
    char name[30];
    float gpa;
    int interview;
    int english;
    int disciplinary;
} Candidate;
```

## Problem Tanımı

- Başlangıçta kapasitesi **2** olan dinamik bir dizi oluşturulmalıdır.
- Dizi dolduğunda kapasitesi `realloc` kullanılarak **iki katına** çıkarılmalıdır.
- Aday numarası olarak **-1** girildiğinde giriş işlemi sonlanır.

### Staj Uygunluk Koşulları

Bir aday aşağıdaki koşulların tamamını sağlıyorsa staja hak kazanır:

- Disiplin cezası **yoktur** (`disciplinary == 0`)
- Mülakat puanı en az **70**'tir (`interview >= 70`)
- Aşağıdaki koşullardan **en az biri** sağlanır:
  - `gpa >= 2.50`
  - `english >= 80`

> **Not:** Çözümünüz pointer mantığına dayanmalıdır. Yapı dizisi fonksiyonlara `Candidate array[]` değil, `Candidate*` olarak geçirilmelidir.

---

## Yazılacak Fonksiyonlar

### 1. `void add_candidate(Candidate** array, int* n, int* capacity, Candidate newCandidate)`

Yeni bir adayı dinamik diziye ekler. Dizi doluysa kapasite iki katına çıkarılır ve `realloc` ile bellek yeniden tahsis edilir.

### 2. `int eligible_for_internship(Candidate c)`

Verilen adayın staja uygun olup olmadığını kontrol eder. Uygunsa `1`, değilse `0` döndürür.

### 3. `int best_candidate(Candidate* array, int n)`

Yalnızca staja uygun adaylar arasından en iyi adayı seçer. Seçim önceliği:

1. **Yüksek mülakat puanı**
2. Eşitlik durumunda → **yüksek GPA**
3. Hâlâ eşitlik varsa → **yüksek İngilizce puanı**

En iyi adayın dizideki **indeksini** döndürür. Uygun aday yoksa `-1` döndürür.

### 4. `int borderline_candidate_count(Candidate* array, int n)`

Yalnızca staja uygun adaylar arasında, aşağıdaki iki koşuldan **yalnızca birini** sağlayanların sayısını döndürür:

- `gpa >= 2.50`
- `english >= 80`

Her iki koşulu birden sağlayan adaylar **sayılmaz**.

---

## Beklenen Çıktı

En iyi adayın **adı** ve **numarası** ekrana yazdırılmalıdır.  
Ayrıca sınır koşullarından yalnızca birini sağlayan uygun aday sayısı da yazdırılmalıdır.
