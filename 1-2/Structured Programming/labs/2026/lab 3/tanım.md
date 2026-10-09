# Lab 3 — Demo Day Etkinlik Katılım Sistemi

**Ders:** STRUCTURED PROGRAMMING  
**Lab:** Lab-3 Session-1  
**Tarih:** 15.05.2026  
**Süre:** 60 dk + 5 dk yükleme  
**Yükleme Linki:** https://forms.gle/LXXkxHxVux5ib3qPA

---

## Problem Tanımı

Bilgisayar Mühendisliği Bölümü tarafından düzenlenen Demo Day etkinliğine öğrenciler, mezunlar ve şirket temsilcileri katılacaktır. Etkinlik girişinde katılımcı kayıtlarını tutmak için **bağlı liste (linked list)** tabanlı bir C programı yazınız. Program bir menü üzerinden çalışmalı ve kullanıcı çıkış seçeneğini seçene kadar işlem yapmaya devam etmelidir.

---

## 1. Yapı Tanımı

`Participant` adında bir `struct` tanımlanmalıdır. Bu yapı; katılımcı kimliği, adı, kurumu, katılımcı türü ve kendi türünden bir işaretçi içermelidir. Bu sayede **öz-referanslı** bir yapı elde edilir.

```c
typedef struct Participant {
    int id;
    char name[50];
    char institution[50];
    int type;
    struct Participant *next;
} Participant;
```

---

## 2. Yeni Katılımcı Oluşturma Fonksiyonu

`createParticipant` fonksiyonu, verilen bilgileri kullanarak yeni bir katılımcı kaydı oluşturmalı ve oluşturulan kaydı döndürmelidir.

---

## 3. Bağlı Listeye Katılımcı Ekleme Fonksiyonu

`addParticipant` fonksiyonu yeni katılımcı kaydını listenin **sonuna** eklemeli. Liste boşsa yeni kayıt listenin ilk elemanı olmalıdır.

---

## 4. Katılımcıları Listeleme Fonksiyonu

`listParticipants` fonksiyonu katılımcı listesindeki tüm kayıtları yazdırmalıdır. Liste boşsa uygun bir uyarı mesajı görüntülemelidir.

---

## 5. Katılımcı Türünü Yazdıran Yardımcı Fonksiyon

`printType` fonksiyonu katılımcı türünü açıklamasıyla birlikte yazdırmalıdır. Geçersiz bir tür değeri girilirse `"Unknown"` yazdırmalıdır.

---

## 6. Kimliğe Göre Katılımcı Arama Fonksiyonu

`searchParticipant` fonksiyonu, listede katılımcı kimliğine göre **iteratif** arama yapmalı ve bulunursa katılımcıyı döndürmelidir.

---

## 7. Katılımcı Sayısını Hesaplayan Özyinelemeli Fonksiyon

`countParticipantsRecursive` fonksiyonu listedeki katılımcı sayısını **özyinelemeli (recursive)** olarak hesaplamalı ve toplam sayıyı döndürmelidir.

---

## 8. Fonksiyon İşaretçisi ile Katılımcı Filtreleme

`listFilteredParticipants` fonksiyonu, kendisine geçirilen filtreleme fonksiyonuna göre katılımcıları yazdırmalıdır. Bu işlemde **fonksiyon işaretçisi** kullanılmalıdır.

```c
int isStudent(Participant *p);
int isCompanyRepresentative(Participant *p);
void listFilteredParticipants(Participant *head, int (*filter)(Participant *));
```

- `isStudent` → katılımcı türü **"Student"** olanları tanımlamalıdır.
- `isCompanyRepresentative` → katılımcı türü **"Company Representative"** olanları tanımlamalıdır.

---

## 9. Belleği Serbest Bırakma Fonksiyonu

`freeParticipants` fonksiyonu program sonunda katılımcı listesi için kullanılan belleği serbest bırakmalıdır.

---

## 10. Menü Yapısı

`menu` fonksiyonu program seçeneklerini ekrana yazdırmalıdır. Program, kullanıcı çıkış seçeneğini seçene kadar menü üzerinden çalışmaya devam etmelidir.

```
--- DEMO DAY EVENT PARTICIPATION SYSTEM ---
1 - Add participant
2 - List participants
3 - Search by participant ID
4 - Calculate participant count recursively
5 - List students
6 - List company representatives
7 - Exit
```
