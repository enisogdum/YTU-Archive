# Lab 4 — Dijital Müzik Platformu: Dinleme Kayıtları Sistemi

**Süre:** 65 dk + 5 dk yükleme

---

## Problem Tanımı

Bir dijital müzik platformu, kullanıcıların dinleme kayıtlarını dijital ortamda takip etmek istemektedir. Sağlanan metin dosyasının her satırı, aşağıdaki bilgileri içermektedir:

| Alan | Açıklama |
|------|----------|
| `streamID` | Benzersiz yayın kimliği |
| `username` | Kullanıcı adı |
| `songTitle` | Şarkı başlığı |
| `genre` | Müzik türü |
| `status` | Oynatma durumu (`Liked`, `Skipped`, `Replay`) |

---

## Programın Özellikleri

1. **Struct tanımlama** — Müzik oynatma kayıtlarını temsil eden bir yapı oluşturunuz.

2. **Dosyadan okuma ve sıralı bağlı liste** — `songs.txt` dosyasından kayıtları okuyarak `streamID` değerine göre **artan sırada** sıralanmış bir bağlı liste oluşturunuz.

3. **Ekrana yazdırma** — Sıralı bağlı listeyi ekrana yazdırınız.

4. **`skipped.txt` dosyası oluşturma** — Oynatma durumu `"Skipped"` olan kayıtları `skipped.txt` adlı dosyaya yazınız.

5. **İkili dosyaya yazma** — Bağlı listedeki tüm kayıtları `songs.dat` adlı **ikili (binary)** dosyaya yazınız.

6. **Rastgele erişim ile güncelleme** — Kullanıcıdan bir `streamID` değeri alınız. İkili dosyada bu kimliğe sahip kaydı **rastgele erişim** yöntemiyle bulunuz ve oynatma durumunu `"Liked"` olarak güncelleyiniz.

7. **`fread`, `fwrite`, `fseek` kullanımı** — Güncelleme işleminde bu fonksiyonlar kullanılmalıdır.

8. **İkili dosyadan okuma** — Güncellemeden sonra ikili dosyadaki tüm kayıtları ekrana yazdırınız.

---

## Örnek Girdi Dosyası (`songs.txt`)

```
205 Mert Believer Rock Liked
201 Elif ShapeOfYou Pop Skipped
220 Can BlindingLights Pop Replay
210 Zeynep Numb Rock Skipped
215 Emir CountingStars Indie Liked
```

---

## Oluşturulan Dosya (`skipped.txt`)

```
201 Elif ShapeOfYou Pop Skipped
210 Zeynep Numb Rock Skipped
```

---

## Örnek Program Çıktısı

**Sıralı Liste:**
```
201 Elif ShapeOfYou Pop Skipped
205 Mert Believer Rock Liked
210 Zeynep Numb Rock Skipped
215 Emir CountingStars Indie Liked
220 Can BlindingLights Pop Replay
```

**Güncelleme:**
```
Enter stream ID to Update: 210
```

**İkili Dosya Kayıtları (Güncellemeden Sonra):**
```
201 Elif ShapeOfYou Pop Skipped
205 Mert Believer Rock Liked
210 Zeynep Numb Rock Liked
215 Emir CountingStars Indie Liked
220 Can BlindingLights Pop Replay
```

> **Not:** Binary dosyanın da sıralı (streamID'ye göre artan) şekilde tutulması beklenmektedir.
