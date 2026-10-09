#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct Yazar {
    char ad[50];
    char soyad[50];
    int sira;
    struct Yazar* next;
} YAZAR;

typedef struct Ogrenci {
    char ad[50];
    char soyad[50];
    int puan;
    int id;
    struct Ogrenci* next;
    struct Ogrenci* prev;
} OGRENCI;

typedef struct KitapOrnek {
    char ornekID[30];
    char durum[50]; // "RAFTA", "ODUNC"
    struct KitapOrnek* next;
} KITAPORNEK;

typedef struct Kitap {
    char ad[100];
    char ISBN[20];
    int adet;
    KITAPORNEK* ornekler;
    struct Kitap* next;
} KITAP;

typedef struct KitapYazar {
    char ISBN[20]; 
    int yazarID;
    struct KitapYazar* next;
} KITAPYAZAR;

typedef struct KitapIslem {
    int ogrenciID;
    char kitapEtiketKod[30];
    int islemTuru; 
    char tarih[20]; 
    struct KitapIslem* next;
} KITAPISLEM;

// FONKSİYONLAR
void load_writers_from_file(FILE **writer_file, YAZAR **head);
void writer_add(FILE **writer_file, YAZAR **head);
void writer_remove(FILE **writer_file, YAZAR **head, KITAPYAZAR **ky_head, FILE **book_author_file);
void writer_update(FILE **writer_file, YAZAR **head);
void writer_display(FILE **writer_file, YAZAR **head);

void load_students_from_file(FILE **student_file, OGRENCI **head);
void student_add(FILE **student_file, OGRENCI **head);
void student_delete(FILE **student_file, OGRENCI **head);
void student_update(FILE **student_file, OGRENCI **head);
void student_display(FILE **student_file, OGRENCI **head);

void load_book_from_file(FILE **book_file, KITAP **head);
void add_book(FILE **book_file, KITAP **head); 
void book_remove(FILE **book_file, KITAP **head); 
void book_update(FILE **book_file, KITAP **head);
void book_display(FILE **book_file, KITAP **head);
void bubble_sort_books(KITAP **head);


void book_author_link(FILE **book_author_file, KITAPYAZAR **ky_head, KITAP *book_head, YAZAR *author_head, FILE **book_file_ref, FILE **author_file_ref);


void load_kitap_islemleri_from_file(FILE **islem_file, KITAPISLEM **islem_head);
void update_book_copy_statuses_on_load(KITAP *book_head, KITAPISLEM *islem_head);

void book_student1(FILE **book_student_file, KITAPISLEM **head_islem, KITAP **head_kitap, FILE **book_file, FILE **student_file, OGRENCI **head_ogrenci);

void display_not_delivered_book(KITAPISLEM *islem_head, OGRENCI *student_list_head);
OGRENCI* find_student_by_id(OGRENCI *head, int id);
int count_active_loans_for_student(KITAPISLEM *islem_head, int student_id); 
void free_student_list(OGRENCI *head); 

void negative_point(FILE **student_file, OGRENCI **head);
void book_shelf(FILE **book_file, KITAP **head);
struct tm string_to_date(char* date_str);
int calculate_days_difference(char* date1_str, char* date2_str); 
void get_current_date(char* date_str) ;
// find_student_by_id already declared
void list_overdue_books(FILE **book_student_file, KITAPISLEM **islem_head, OGRENCI *main_student_head); 


KITAPORNEK* create_book_copies(char* isbn, int count);
void free_book_copies(KITAPORNEK* head);

int main(){
    srand(time(NULL));
    int choice1, choice2;
    int system_running = 1;
    
    YAZAR *head_yazar = NULL;
    FILE *writer_list = fopen("Yazarlar.csv", "a+");
    if (writer_list == NULL) {
        printf("Yazarlar dosyası açılamadı!\n");
        return 1;
    }
    load_writers_from_file(&writer_list, &head_yazar);


    OGRENCI *head_ogrenci = NULL;
    FILE *student_list = fopen("Ogrenciler.csv", "a+");
    if (student_list == NULL) {
        printf("Öğrenciler dosyası açılamadı!\n");
        fclose(writer_list);
        return 1;
    }
    load_students_from_file(&student_list, &head_ogrenci);

    KITAP *head_kitap = NULL;
    FILE *book_list = fopen("Kitaplar.csv", "a+");
    if (book_list == NULL) {
        printf("Kitaplar dosyası açılamadı!\n");
        fclose(writer_list);
        fclose(student_list);
        return 1;
    }
    load_book_from_file(&book_list, &head_kitap);


    KITAPYAZAR *head_kitapyazar=NULL;
    FILE *book_author_list=fopen("KitapYazar.csv","a+");
    if (book_author_list == NULL) {
        printf("KitapYazar dosyası açılamadı!\n");
        fclose(writer_list);
        fclose(student_list);
        fclose(book_list);
        return 1;
    }


    KITAPISLEM *head_kitapislem=NULL;
    FILE *book_student_operations_file=fopen("KitapOdunc.csv","a+");
    if (book_student_operations_file==NULL)
    {
        printf("KitapOdunc dosyası açılamadı!\n");
        fclose(writer_list);
        fclose(student_list);
        fclose(book_list);
        fclose(book_author_list);
        return 1;
    }
    load_kitap_islemleri_from_file(&book_student_operations_file, &head_kitapislem);
    update_book_copy_statuses_on_load(head_kitap, head_kitapislem);


    while (system_running) {
        rewind(book_list); 
        load_book_from_file(&book_list, &head_kitap);
        rewind(book_student_operations_file);
        load_kitap_islemleri_from_file(&book_student_operations_file, &head_kitapislem); 
        update_book_copy_statuses_on_load(head_kitap, head_kitapislem); 
        rewind(student_list);
        load_students_from_file(&student_list, &head_ogrenci);

        rewind(writer_list);
        load_writers_from_file(&writer_list, &head_yazar);


        printf("\n=== KÜTÜPHANE YÖNETİM SİSTEMİ ===\n");
        
        printf("\n=== ÖĞRENCİ İŞLEMLERİ ===\n");
        printf("1  - Öğrenci Ekle, Sil, Güncelle\n");
        printf("2  - Öğrenci Bilgisi Görüntüleme\n");
        printf("3  - Kitap Teslim Etmemiş Öğrencileri Listele\n"); 
        printf("4  - Cezalı Öğrencileri Listele\n"); 
        printf("5  - Kitap Ödünç Al / Teslim Et\n");
        
        printf("\n=== KİTAP İŞLEMLERİ ===\n");
        printf("6  - Kitap Ekle, Sil, Güncelle\n");
        printf("7  - Kitap Bilgisi Görüntüleme\n");
        printf("8  - Raftaki Kitapları Listele\n");
        printf("9  - Zamanında Teslim Edilmeyen Kitapları Listele\n"); 
        
        printf("\n=== YAZAR İŞLEMLERİ ===\n");
        printf("10 - Yazar Ekle, Sil, Güncelle\n");
        printf("11 - Yazar Bilgisi Görüntüleme\n");
        
        printf("\n=== KİTAP-YAZAR İŞLEMLERİ ===\n");
        printf("12 - Kitap-Yazar Eşleştir\n");
        
        printf("\n0  - ÇIKIŞ\n");
        printf("\nSeçiminiz: ");
        scanf("%d", &choice1);
        
        switch (choice1) {
            case 0:
                system_running = 0;
                printf("Program sonlandırılıyor...\n");
                break;
                
            case 1:
                printf("\n--- Öğrenci İşlemleri ---\n");
                printf("1 - Öğrenci Ekle\n");
                printf("2 - Öğrenci Sil\n");
                printf("3 - Öğrenci Güncelle\n");
                printf("Seçiminiz: ");
                scanf("%d", &choice2);
                
                switch (choice2) {
                    case 1: student_add(&student_list, &head_ogrenci); break;
                    case 2: student_delete(&student_list, &head_ogrenci); break;
                    case 3: student_update(&student_list, &head_ogrenci); break;
                    default: printf("Geçersiz seçim.\n"); break;
                }
                break;
                
            case 2:
                student_display(&student_list, &head_ogrenci);
                break;
                
            case 3:
                display_not_delivered_book(head_kitapislem, head_ogrenci);
                break;
                
            case 4:
                negative_point(&student_list, &head_ogrenci);
                break;
                
            case 5:
                book_student1(&book_student_operations_file, &head_kitapislem, &head_kitap, &book_list, &student_list, &head_ogrenci);
                load_book_from_file(&book_list, &head_kitap); 
                load_kitap_islemleri_from_file(&book_student_operations_file, &head_kitapislem); 
                update_book_copy_statuses_on_load(head_kitap, head_kitapislem); 
                break;
                
            case 6:
                printf("\n--- Kitap İşlemleri ---\n");
                printf("1 - Kitap Ekle\n");
                printf("2 - Kitap Sil\n");
                printf("3 - Kitap Güncelle\n");
                printf("Seçiminiz: ");
                scanf("%d", &choice2);
                
                switch (choice2) {
                    case 1: add_book(&book_list, &head_kitap); break;
                    case 2: book_remove(&book_list, &head_kitap); break;
                    case 3: book_update(&book_list, &head_kitap); break;
                    default: printf("Geçersiz seçim.\n"); break;
                }
                break;
                
            case 7:
                book_display(&book_list, &head_kitap);
                break;
                
            case 8:
                book_shelf(&book_list, &head_kitap);
                break;
                
            case 9:
                list_overdue_books(&book_student_operations_file, &head_kitapislem, head_ogrenci);
                break;
                
            case 10:
                printf("\n--- Yazar İşlemleri ---\n");
                printf("1 - Yazar Ekle\n");
                printf("2 - Yazar Sil\n");
                printf("3 - Yazar Güncelle\n");
                printf("Seçiminiz: ");
                scanf("%d", &choice2);
                
                switch (choice2) {
                    case 1: writer_add(&writer_list, &head_yazar); break;
                    case 2: writer_remove(&writer_list, &head_yazar,&head_kitapyazar,&book_author_list); break;
                    case 3: writer_update(&writer_list, &head_yazar); break;
                    default: printf("Geçersiz seçim.\n"); break;
                }
                break;
                
            case 11:
                writer_display(&writer_list, &head_yazar);
                break;
                
            case 12:
                book_author_link(&book_author_list, &head_kitapyazar, head_kitap, head_yazar, &book_list, &writer_list);
                break;
            default:
                printf("Geçersiz seçim! (0-12 arası)\n");
                break;
        }
    }
    
    // Cleanup
    YAZAR *temp_yazar;
    while (head_yazar != NULL) {
        temp_yazar = head_yazar;
        head_yazar = head_yazar->next;
        free(temp_yazar);
    }
    
    OGRENCI *temp_ogrenci;
    while (head_ogrenci != NULL) {
        temp_ogrenci = head_ogrenci;
        head_ogrenci = head_ogrenci->next;
        // Doubly linked list might need careful freeing if prev pointers are used in complex ways
        free(temp_ogrenci);
    }
    
    KITAP *temp_kitap;
    while (head_kitap != NULL) {
        temp_kitap = head_kitap;
        head_kitap = head_kitap->next;
        free_book_copies(temp_kitap->ornekler);
        free(temp_kitap);
    }

    KITAPYAZAR *temp_ky;
    while(head_kitapyazar != NULL){
        temp_ky = head_kitapyazar;
        head_kitapyazar = head_kitapyazar->next;
        free(temp_ky);
    }

    KITAPISLEM *temp_ki;
    while(head_kitapislem != NULL){
        temp_ki = head_kitapislem;
        head_kitapislem = head_kitapislem->next;
        free(temp_ki);
    }
    
    fclose(writer_list);
    fclose(student_list);
    fclose(book_list);
    fclose(book_author_list);
    fclose(book_student_operations_file);
    
    return 0;
}

void load_writers_from_file(FILE **writer_file, YAZAR **head) {
    if (ftell(*writer_file) > 0) rewind(*writer_file); // File position indicator başa al
    
    char *line = (char*)malloc(200 * sizeof(char));
    if (line == NULL) {
        printf("Bellek hatası (line)!\n");
        return;
    }
    
    YAZAR *temp_node;
    
    // Mevcut listeyi temizle
    while (*head != NULL) {
        temp_node = *head;
        *head = (*head)->next;
        free(temp_node);
    }
    
    // Dosyadan oku - sizeof(line) yerine 200 kullan
    while (fgets(line, 200, *writer_file) != NULL) {
        line[strcspn(line, "\r\n")] = 0;
        
        if (strlen(line) >= 3) {  // Sadece geçerli satırları işle
            YAZAR *new_node = (YAZAR*)malloc(sizeof(YAZAR));
            if (new_node == NULL) {
                printf("Bellek hatası (Yazar)!\n");
                free(line);
                return;
            }
            char *token = strtok(line, ",");
            if (token != NULL) {
                new_node->sira = atoi(token);
                
                token = strtok(NULL, ",");
                if (token != NULL) {
                    strcpy(new_node->ad, token);
                    
                    token = strtok(NULL, ",");
                    if (token != NULL) {
                        strcpy(new_node->soyad, token);
                        
                        new_node->next = NULL;
                        
                        if (*head == NULL) {
                            *head = new_node;
                        } else {
                            YAZAR *current = *head;
                            while (current->next != NULL) {
                                current = current->next;
                            }
                            current->next = new_node;
                        }
                    } else {
                        free(new_node);
                    }
                } else {
                    free(new_node);
                }
            } else {
                free(new_node);
            }
        }
    }
    
    free(line);
}

void writer_add(FILE **writer_file, YAZAR **head) {
  
    int count = 0;
    int max_sira = 0;
    YAZAR *temp = *head;
    while (temp != NULL) {
        if (temp->sira > max_sira) {
            max_sira = temp->sira;
        }
        count++;
        temp = temp->next;
    }
    
    YAZAR *new_node = (YAZAR*)malloc(sizeof(YAZAR));
    if (new_node == NULL) {
        printf("Bellek hatası!\n");
        return;
    }
    
    printf("Yazarın adını girin: ");
    scanf("%49s", new_node->ad);
    
    printf("Yazarın soyadını girin: ");
    scanf("%49s", new_node->soyad);
    
    new_node->sira = max_sira + 1;
    new_node->next = NULL;
    
    if (*head == NULL) {
        *head = new_node;
    } else {
        temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    
    fclose(*writer_file); 
    *writer_file = fopen("Yazarlar.csv", "a"); 
     if (*writer_file == NULL) {
        printf("Yazarlar.csv dosyası tekrar açılamadı (append)!\n");
        return;
    }
    fprintf(*writer_file, "%d,%s,%s\n", new_node->sira, new_node->ad, new_node->soyad);
    fflush(*writer_file);
    fclose(*writer_file);
    *writer_file = fopen("Yazarlar.csv", "a+"); 
     if (*writer_file == NULL) {
        printf("Yazarlar.csv dosyası tekrar açılamadı (a+)!\n");
    }

    printf("Yazar başarıyla eklendi. Sira No: %d\n", new_node->sira);
}
void writer_remove(FILE **writer_file, YAZAR **head, KITAPYAZAR **ky_head, FILE **book_author_file) {
    if (*head == NULL) {
        printf("Henüz dosyada yazar yok!\n");
        return;
    }

    int choice_sira;
    printf("Mevcut yazarlar:\n");
    YAZAR *display = *head;
    while (display != NULL) {
        printf("%d - %s %s\n", display->sira, display->ad, display->soyad);
        display = display->next;
    }

    printf("Silinecek yazarın sıra numarası: ");
    scanf("%d", &choice_sira);

    YAZAR *temp = *head, *previous = NULL;
    while (temp != NULL && temp->sira != choice_sira) {
        previous = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Bu sıra numarasında yazar bulunamadı!\n");
        return;
    }

    if (previous == NULL) {
        *head = temp->next;
    } else {
        previous->next = temp->next;
    }

    printf("Yazar %s %s (Sıra: %d) silindi.\n", temp->ad, temp->soyad, temp->sira);
    free(temp);

    // Sıra numaralarını güncelle
    int count = 1;
    YAZAR *temp1 = *head;
    while (temp1 != NULL) {
        temp1->sira = count++;
        temp1 = temp1->next;
    }

    // Yazarlar.csv dosyasını güncelle
    fclose(*writer_file);
    *writer_file = fopen("Yazarlar.csv", "w");
    if (*writer_file == NULL) {
        printf("Yazarlar.csv dosyası yazılamadı!\n");
        *writer_file = fopen("Yazarlar.csv", "a+");
        return;
    }

    YAZAR *current_write = *head;
    while (current_write != NULL) {
        fprintf(*writer_file, "%d,%s,%s\n", current_write->sira, current_write->ad, current_write->soyad);
        current_write = current_write->next;
    }
    fflush(*writer_file);
    fclose(*writer_file);
    *writer_file = fopen("Yazarlar.csv", "a+");
    if (*writer_file == NULL) printf("Yazarlar.csv dosyası a+ modunda tekrar açılamadı!\n");

    // KitapYazar eşleşmelerini kontrol et
    KITAPYAZAR *ky_ptr = *ky_head;
    int degisiklik_var = 0;
    while (ky_ptr != NULL) {
        if (ky_ptr->yazarID == choice_sira) {
            ky_ptr->yazarID = -1;  // Yazar silindiyse ID -1 yap
            degisiklik_var = 1;
        }
        ky_ptr = ky_ptr->next;
    }

    if (degisiklik_var) {
        // KitapYazar.csv dosyasını baştan yaz
        fclose(*book_author_file);
        *book_author_file = fopen("KitapYazar.csv", "w");
        if (*book_author_file == NULL) {
            printf("KitapYazar.csv dosyası güncelleme için açılamadı!\n");
            return;
        }

        KITAPYAZAR *ky_write = *ky_head;
        while (ky_write != NULL) {
            fprintf(*book_author_file, "%s,%d\n", ky_write->ISBN, ky_write->yazarID);
            ky_write = ky_write->next;
        }

        fflush(*book_author_file);
        fclose(*book_author_file);
        *book_author_file = fopen("KitapYazar.csv", "a+");
        if (*book_author_file == NULL) printf("KitapYazar.csv dosyası a+ modunda tekrar açılamadı.\n");
    }

    printf("Dosya(lar) güncellendi.\n");
}

void writer_update(FILE **writer_file, YAZAR **head) {
 
    if (*head == NULL) {
        printf("Henüz dosyada yazar yok!\n");
        return;
    }
    
    int choice_sira, field_choice;
    printf("Mevcut yazarlar:\n");
    YAZAR *display = *head;
    while (display != NULL) {
        printf("%d - %s %s\n", display->sira, display->ad, display->soyad);
        display = display->next;
    }
    
    printf("Güncellenecek yazarın sıra numarası: ");
    scanf("%d", &choice_sira);
    
    YAZAR *temp = *head;
    while (temp != NULL && temp->sira != choice_sira) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Bu sıra numarasında yazar bulunamadı!\n");
        return;
    }
    
    printf("Hangi bilgiyi değiştirmek istiyorsunuz? (Yazar: %s %s)\n", temp->ad, temp->soyad);
    printf("1 - İsim\n2 - Soyisim\nSeçiminiz: ");
    scanf("%d", &field_choice);
    
    char buffer[50];
    if (field_choice == 1) {
        printf("Yeni isim: ");
        scanf("%49s", buffer);
        strcpy(temp->ad, buffer);
    } else if (field_choice == 2) {
        printf("Yeni soyisim: ");
        scanf("%49s", buffer);
        strcpy(temp->soyad, buffer);
    } else {
        printf("Geçersiz seçim!\n");
        return;
    }
    
    fclose(*writer_file);
    *writer_file = fopen("Yazarlar.csv", "w");
    if (*writer_file == NULL) {
        printf("Yazarlar.csv dosyası yazılamadı!\n");
        *writer_file = fopen("Yazarlar.csv", "a+");
        return;
    }
    
    YAZAR *current_write = *head;
    while (current_write != NULL) {
        fprintf(*writer_file, "%d,%s,%s\n", current_write->sira, current_write->ad, current_write->soyad);
        current_write = current_write->next;
    }
    fflush(*writer_file);
    fclose(*writer_file);
    *writer_file = fopen("Yazarlar.csv", "a+");
     if (*writer_file == NULL) printf("Yazarlar.csv dosyası a+ modunda tekrar açılamadı!\n");

    printf("Yazar bilgileri güncellendi.\n");
}

void writer_display(FILE **writer_file, YAZAR **head) {

    if (*head == NULL) {
        printf("Henüz dosyada yazar yok!\n");
        return;
    }

    printf("\n=== YAZAR LİSTESİ ===\n");
    printf("%-10s %-20s %-20s\n", "Sıra No", "Ad", "Soyad");
    printf("---------------------------------------------------\n");
    YAZAR *display = *head;
    while (display != NULL) {
        printf("%-10d %-20s %-20s\n", display->sira, display->ad, display->soyad);
        display = display->next;
    }
    printf("---------------------------------------------------\n");
}

void load_students_from_file(FILE **student_file, OGRENCI **head) {
    if (ftell(*student_file) > 0) rewind(*student_file);
    
    char line[200];
    OGRENCI *temp_node;
    while (*head != NULL) {
        temp_node = *head;
        *head = (*head)->next;
        free(temp_node);
    }
    
    OGRENCI *tail = NULL; 

   while (fgets(line, sizeof(line), *student_file) != NULL) {
   line[strcspn(line, "\r\n")] = 0;
   
   if (strlen(line) >= 5) {
       OGRENCI *new_node = (OGRENCI*)malloc(sizeof(OGRENCI));
       if (new_node == NULL) {
           printf("Bellek hatası (Ogrenci)!\n");
           return;
       }
       
       char *token = strtok(line, ",");
       if (token) {
           new_node->id = atoi(token);
           
           token = strtok(NULL, ",");
           if (token) {
               strcpy(new_node->ad, token);
               
               token = strtok(NULL, ",");
               if (token) {
                   strcpy(new_node->soyad, token);
                   
                   token = strtok(NULL, ",");
                   if (token) {
                       new_node->puan = atoi(token);
                       
                       new_node->next = NULL;
                       new_node->prev = NULL;
                       
                       if (*head == NULL) {
                           *head = new_node;
                           tail = new_node;
                       } else {
                           tail->next = new_node;
                           new_node->prev = tail;
                           tail = new_node;
                       }
                   } else {
                       free(new_node);
                   }
               } else {
                   free(new_node);
               }
           } else {
               free(new_node);
           }
       } else {
           free(new_node);
       }
   }
}
}

void student_add(FILE **student_file, OGRENCI **head) {

    OGRENCI *new_node = (OGRENCI*)malloc(sizeof(OGRENCI));
    if (new_node == NULL) {
        printf("Bellek hatası!\n");
        return;
    }
    
    printf("Öğrencinin adını girin: ");
    scanf("%49s", new_node->ad);
    
    printf("Öğrencinin soyadını girin: ");
    scanf("%49s", new_node->soyad);
    
    int max_id = 0;
    OGRENCI* temp_id_check = *head;
    while(temp_id_check != NULL){
        if(temp_id_check->id > max_id) max_id = temp_id_check->id;
        temp_id_check = temp_id_check->next;
    }
    if (max_id == 0) max_id = 10000000; 
    new_node->id = max_id + (rand() % 100) + 1; 

    new_node->puan = 100; // Default Puan
    new_node->next = NULL;
    new_node->prev = NULL;
    
    if (*head == NULL) {
        *head = new_node;
    } else {
        OGRENCI *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
    }
    
    fclose(*student_file);
    *student_file = fopen("Ogrenciler.csv", "a");
     if (*student_file == NULL) { printf("Ogrenciler.csv dosyası append için açılamadı!\n"); return; }
    fprintf(*student_file, "%d,%s,%s,%d\n", new_node->id, new_node->ad, new_node->soyad, new_node->puan);
    fflush(*student_file);
    fclose(*student_file);
    *student_file = fopen("Ogrenciler.csv", "a+");
     if (*student_file == NULL) printf("Ogrenciler.csv dosyası a+ modunda tekrar açılamadı!\n");
    
    printf("Öğrenci başarıyla eklendi. ID: %d\n", new_node->id);
}

void student_delete(FILE **student_file, OGRENCI **head) {

    if (*head == NULL) {
        printf("Henüz dosyada öğrenci yok!\n");
        return;
    }

    int choice_id;
    printf("Mevcut öğrenciler:\n");
    OGRENCI *temp_disp = *head;
    while (temp_disp != NULL) {
        printf("ID: %d - %s %s (Puan: %d)\n", temp_disp->id, temp_disp->ad, temp_disp->soyad, temp_disp->puan);
        temp_disp = temp_disp->next;
    }

    printf("Silinecek öğrencinin ID'si: ");
    scanf("%d", &choice_id);

    OGRENCI *temp_del = *head;
    while (temp_del != NULL && temp_del->id != choice_id) {
        temp_del = temp_del->next;
    }

    if (temp_del == NULL) {
        printf("Bu ID'ye sahip öğrenci bulunamadı!\n");
        return;
    }

    if (temp_del->prev == NULL) { 
        *head = temp_del->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } else {
        temp_del->prev->next = temp_del->next;
        if (temp_del->next != NULL) {
            temp_del->next->prev = temp_del->prev;
        }
    }

    printf("Öğrenci %s %s (ID: %d) silindi.\n", temp_del->ad, temp_del->soyad, temp_del->id);
    free(temp_del);

    fclose(*student_file);
    *student_file = fopen("Ogrenciler.csv", "w");
    if (*student_file == NULL) {
        printf("Ogrenciler.csv dosyası yazılamadı!\n");
        *student_file = fopen("Ogrenciler.csv", "a+"); return;
    }

    OGRENCI *current_write = *head;
    while (current_write != NULL) {
        fprintf(*student_file, "%d,%s,%s,%d\n", current_write->id, current_write->ad, current_write->soyad, current_write->puan);
        current_write = current_write->next;
    }
    fflush(*student_file);
    fclose(*student_file);
    *student_file = fopen("Ogrenciler.csv", "a+");
    if (*student_file == NULL) printf("Ogrenciler.csv dosyası a+ modunda tekrar açılamadı!\n");

    printf("Dosya güncellendi.\n");
}

void student_update(FILE **student_file, OGRENCI **head) {

    if (*head == NULL) {
        printf("Henüz dosyada öğrenci yok!\n");
        return;
    }

    int choice_id;
    printf("Mevcut öğrenciler:\n");
    OGRENCI *temp_disp = *head;
    while (temp_disp != NULL) {
        printf("ID: %d - %s %s (Puan: %d)\n", temp_disp->id, temp_disp->ad, temp_disp->soyad, temp_disp->puan);
        temp_disp = temp_disp->next;
    }

    printf("Güncellenecek öğrencinin ID'si: ");
    scanf("%d", &choice_id);

    OGRENCI *temp_upd = *head;
    while (temp_upd != NULL && temp_upd->id != choice_id) {
        temp_upd = temp_upd->next;
    }

    if (temp_upd == NULL) {
        printf("Bu ID'ye sahip öğrenci bulunamadı!\n");
        return;
    }

    int field_choice;
    char buffer[50];
    printf("Hangi bilgiyi değiştirmek istiyorsunuz? (Öğrenci: ID %d, %s %s)\n", temp_upd->id, temp_upd->ad, temp_upd->soyad);
    printf("1 - Ad\n2 - Soyad\n3 - Puan (Dikkatli kullanın!)\nSeçiminiz: ");
    scanf("%d", &field_choice);

    if (field_choice == 1) {
        printf("Yeni ad: ");
        scanf("%49s", buffer);
        strcpy(temp_upd->ad, buffer);
    } else if (field_choice == 2) {
        printf("Yeni soyad: ");
        scanf("%49s", buffer);
        strcpy(temp_upd->soyad, buffer);
    } else if (field_choice == 3) {
        printf("Yeni puan: ");
        int new_puan;
        scanf("%d", &new_puan);
        temp_upd->puan = new_puan;
    }else {
        printf("Geçersiz seçim!\n");
        return;
    }

    printf("Öğrenci bilgileri güncellendi: ID %d, %s %s, Puan %d\n", temp_upd->id, temp_upd->ad, temp_upd->soyad, temp_upd->puan);

    fclose(*student_file);
    *student_file = fopen("Ogrenciler.csv", "w");
     if (*student_file == NULL) {
        printf("Ogrenciler.csv dosyası yazılamadı!\n");
        *student_file = fopen("Ogrenciler.csv", "a+"); return;
    }

    OGRENCI *current_write = *head;
    while (current_write != NULL) {
        fprintf(*student_file, "%d,%s,%s,%d\n", current_write->id, current_write->ad, current_write->soyad, current_write->puan);
        current_write = current_write->next;
    }
    fflush(*student_file);
    fclose(*student_file);
    *student_file = fopen("Ogrenciler.csv", "a+");
    if (*student_file == NULL) printf("Ogrenciler.csv dosyası a+ modunda tekrar açılamadı!\n");
    printf("Dosya güncellendi.\n");
}

void student_display(FILE **student_file, OGRENCI **head) {

    if (*head == NULL) {
        printf("Henüz dosyada öğrenci yok!\n");
        return;
    }

    printf("\n=== ÖĞRENCİ LİSTESİ ===\n");
    printf("%-10s %-20s %-20s %-10s\n", "ID", "Ad", "Soyad", "Puan");
    printf("------------------------------------------------------------------\n");
    OGRENCI *current = *head;
    while (current != NULL) {
        printf("%-10d %-20s %-20s %-10d\n", 
               current->id, current->ad, current->soyad, current->puan);
        current = current->next;
    }
    printf("------------------------------------------------------------------\n");
}


KITAPORNEK* create_book_copies(char* isbn, int count) {
    KITAPORNEK* head_copy = NULL; 
    KITAPORNEK* tail = NULL;
    
    for (int i = 1; i <= count; i++) {
        KITAPORNEK* new_copy = (KITAPORNEK*)malloc(sizeof(KITAPORNEK));
        if (new_copy == NULL) {
            printf("Bellek hatası (KitapOrnek)!\n");
            while(head_copy != NULL){
                KITAPORNEK *temp_del = head_copy;
                head_copy = head_copy->next;
                free(temp_del);
            }
            return NULL; 
        }
        
        sprintf(new_copy->ornekID, "%s_%d", isbn, i);
        strcpy(new_copy->durum, "RAFTA"); // Default status
        new_copy->next = NULL;
        
        if (head_copy == NULL) {
            head_copy = new_copy;
            tail = new_copy;
        } else {
            tail->next = new_copy;
            tail = new_copy;
        }
    }
    return head_copy;
}

void free_book_copies(KITAPORNEK* head_copy) { 
    KITAPORNEK* temp;
    while (head_copy != NULL) {
        temp = head_copy;
        head_copy = head_copy->next;
        free(temp);
    }
}


void load_book_from_file(FILE **book_file, KITAP **head) {
    if (ftell(*book_file) > 0) rewind(*book_file);
    
    char line[300];
    KITAP *temp_node;
    while (*head != NULL) {
        temp_node = *head;
        *head = (*head)->next;
        free_book_copies(temp_node->ornekler);
        free(temp_node);
    }
    
    KITAP *tail = NULL;

    while (fgets(line, sizeof(line), *book_file) != NULL) {
   line[strcspn(line, "\r\n")] = 0;
   
   if (strlen(line) >= 5) {
       KITAP *new_node = (KITAP*)malloc(sizeof(KITAP));
       if (new_node == NULL) {
           printf("Bellek hatası (Kitap)!\n");
           return;
       }
       
       char *token = strtok(line, ",");
       if (token) {
           strcpy(new_node->ad, token);
           
           token = strtok(NULL, ",");
           if (token) {
               strcpy(new_node->ISBN, token);
               
               token = strtok(NULL, ",");
               if (token) {
                   new_node->adet = atoi(token);
                   
                   new_node->ornekler = create_book_copies(new_node->ISBN, new_node->adet);
                   new_node->next = NULL;
                   
                   if (*head == NULL) {
                       *head = new_node;
                       tail = new_node;
                   } else {
                       tail->next = new_node;
                       tail = new_node;
                   }
               } else {
                   free(new_node);
               }
           } else {
               free(new_node);
           }
       } else {
           free(new_node);
       }
   }
}
}

void add_book(FILE **book_file, KITAP **head) {

    KITAP *new_node = (KITAP*)malloc(sizeof(KITAP));
    if (new_node == NULL) {
        printf("Bellek hatası!\n");
        return;
    }
    
    printf("Kitap adını girin (max 99 karakter): ");
    getchar(); 
    fgets(new_node->ad, sizeof(new_node->ad), stdin);
    new_node->ad[strcspn(new_node->ad, "\n")] = 0; 
    
  // Rastgele ISBN üret (13 haneli)
for (int i = 0; i < 13; i++) {
    new_node->ISBN[i] = '0' + rand() % 10;
}
new_node->ISBN[13] = '\0'; // null terminator
    // Check if ISBN already exists
    KITAP *check_isbn = *head;
    while(check_isbn != NULL) {
        if(strcmp(check_isbn->ISBN, new_node->ISBN) == 0) {
            printf("Bu ISBN numarası zaten mevcut: %s (%s)\n", check_isbn->ISBN, check_isbn->ad);
            free(new_node);
            return;
        }
        check_isbn = check_isbn->next;
    }
    
    printf("Kitap adet sayısını girin: ");
    scanf("%d", &new_node->adet);
    if (new_node->adet < 0) {
        printf("Adet negatif olamaz.\n");
        free(new_node);
        return;
    }
    
    new_node->ornekler = create_book_copies(new_node->ISBN, new_node->adet);
    new_node->next = NULL;
    
    if (*head == NULL) {
        *head = new_node;
    } else {
        KITAP *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    
    fclose(*book_file);
    *book_file = fopen("Kitaplar.csv", "a");
    if (*book_file == NULL) { printf("Kitaplar.csv dosyası append için açılamadı!\n"); return; }
    fprintf(*book_file, "%s,%s,%d\n", new_node->ad, new_node->ISBN, new_node->adet);
    fflush(*book_file);
    fclose(*book_file);
    *book_file = fopen("Kitaplar.csv", "a+");
    if (*book_file == NULL) printf("Kitaplar.csv dosyası a+ için tekrar açılamadı!\n");
    
    printf("Kitap başarıyla eklendi: %s\n", new_node->ad);
}

void book_remove(FILE **book_file, KITAP **head) {

    if (*head == NULL) {
        printf("Henüz dosyada kitap yok!\n");
        return;
    }

    printf("Mevcut kitaplar:\n");
    KITAP *display = *head;
    int index = 1;
    while (display != NULL) {
        printf("%d - %s (ISBN: %s, Adet: %d)\n", index, display->ad, display->ISBN, display->adet);
        display = display->next;
        index++;
    }

    char *isbn_to_delete;
isbn_to_delete=(char*)malloc(20*sizeof(char));
    printf("Silinecek kitabın ISBN numarasını girin: ");
    scanf("%19s", isbn_to_delete);

    KITAP *temp = *head, *previous = NULL;
 int book=atoi(temp->ISBN);
int book2=atoi(isbn_to_delete);
    while(temp != NULL && book!=book2) {
        printf("kontrol edilen ID %s ---%s\n",temp->ISBN,isbn_to_delete);
        temp=previous;
        temp = temp->next;
         book=atoi(temp->ISBN);
    }

    if (temp == NULL) {
        printf("Bu ISBN'de kitap bulunamadı: %s!\n", isbn_to_delete);
        return;
    }

    FILE *ky_file = fopen("KitapYazar.csv", "r");
    FILE *temp_ky_file = fopen("temp_ky.csv", "w");
    if (ky_file && temp_ky_file) {
char *line = (char*)malloc(200 * sizeof(char));
char *temp_isbn_check = (char*)malloc(20 * sizeof(char));

if (line == NULL || temp_isbn_check == NULL) {
   printf("Bellek hatası!\n");
   if (line) free(line);
   if (temp_isbn_check) free(temp_isbn_check);
   return;
}
        int temp_yazarid_check;
        while(fgets(line, sizeof(line), ky_file)){
            line[strcspn(line, "\r\n")] = 0;
            char *token_isbn = strtok(line, ",");
            char *token_yazarid = strtok(NULL, ",");
            if(token_isbn && token_yazarid){
                if(strcmp(token_isbn, temp->ISBN) != 0){
                     fprintf(temp_ky_file, "%s,%s\n", token_isbn, token_yazarid);
                } else {
                    printf("KitapYazar.csv'den %s için bağlantı kaldırılıyor.\n", temp->ISBN);
                }
            }
        }
        fclose(ky_file);
        fclose(temp_ky_file);
        remove("KitapYazar.csv");
        rename("temp_ky.csv", "KitapYazar.csv");
    } else {
        if(ky_file) fclose(ky_file);
        if(temp_ky_file) fclose(temp_ky_file);
        printf("KitapYazar.csv güncellenemedi.\n");
    }


    if (previous == NULL) { 
        *head = temp->next;
    } else {
        previous->next = temp->next;
    }

    printf("Kitap %s (ISBN: %s) silindi.\n", temp->ad, temp->ISBN);
    free_book_copies(temp->ornekler);
    free(temp);

    fclose(*book_file);
    *book_file = fopen("Kitaplar.csv", "w");
    if (*book_file == NULL) {
        printf("Kitaplar.csv dosyası yazılamadı!\n");
        *book_file = fopen("Kitaplar.csv", "a+"); return;
    }
    KITAP *current_write = *head;
    while (current_write != NULL) {
        fprintf(*book_file, "%s,%s,%d\n", current_write->ad, current_write->ISBN, current_write->adet);
        current_write = current_write->next;
    }
    fflush(*book_file);
    fclose(*book_file);
    *book_file = fopen("Kitaplar.csv", "a+");
     if (*book_file == NULL) printf("Kitaplar.csv dosyası a+ için tekrar açılamadı!\n");

    printf("Kitaplar.csv dosyası güncellendi.\n");
}

void book_update(FILE **book_file, KITAP **head) {

    if (*head == NULL) {
        printf("Henüz dosyada kitap yok!\n");
        return;
    }

    printf("Mevcut kitaplar:\n");
    KITAP *display = *head;
    int index = 1;
    while (display != NULL) {
        printf("%d - %s (ISBN: %s, Adet: %d)\n", index, display->ad, display->ISBN, display->adet);
        display = display->next;
        index++;
    }
    
   char *isbn_to_update = (char*)malloc(20 * sizeof(char));

if (isbn_to_update == NULL) {
   printf("Bellek hatası!\n");
   return;
}

    printf("Güncellenecek kitabın ISBN numarasını girin: ");
    scanf("%19s", isbn_to_update);
    getchar(); // \n karakterini kaldır

    KITAP *temp = *head;
  int book=atoi(temp->ISBN);
int book2=atoi(isbn_to_update);
    while(temp != NULL && book!=book2) {
        printf("kontrol edilen ID %s ---%s\n",temp->ISBN,isbn_to_update);
        temp = temp->next;
         book=atoi(temp->ISBN);
    }

    if (temp == NULL) {
        printf("Bu ISBN'de kitap bulunamadı: %s!\n", isbn_to_update);
        return;
    }

    int choice2;
    printf("Hangi bilgiyi değiştirmek istiyorsunuz (Kitap: %s, ISBN: %s)?\n", temp->ad, temp->ISBN);
    printf("1 - Kitap Adı\n2 - ISBN (Dikkat: Bağlantıları etkileyebilir!)\n3 - Adet Sayısı\nSeçiminiz: ");
    scanf("%d", &choice2);
    getchar(); 

    char buffer[100];
    if (choice2 == 1) {
        printf("Yeni kitap adı: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(temp->ad, buffer);
    } else if (choice2 == 2) {
        printf("Yeni ISBN: ");
        scanf("%19s", buffer);
        getchar(); 

        KITAP *check_isbn = *head;
        while(check_isbn != NULL) {
            if(check_isbn != temp && strcmp(check_isbn->ISBN, buffer) == 0) {
                printf("Bu ISBN numarası zaten başka bir kitaba ait: %s (%s)\n", check_isbn->ISBN, check_isbn->ad);
                return; 
            }
            check_isbn = check_isbn->next;
        }

        free_book_copies(temp->ornekler);
        strcpy(temp->ISBN, buffer); 
        temp->ornekler = create_book_copies(temp->ISBN, temp->adet); 
        
    } else if (choice2 == 3) {
        int new_count;
        printf("Yeni adet sayısı: ");
        scanf("%d", &new_count);
        getchar(); 
        if (new_count < 0) {
            printf("Adet negatif olamaz.\n");
            return;
        }

        free_book_copies(temp->ornekler);
        temp->adet = new_count;
        temp->ornekler = create_book_copies(temp->ISBN, temp->adet);
    } else {
        printf("Geçersiz seçim!\n");
        return;
    }

    fclose(*book_file);
    *book_file = fopen("Kitaplar.csv", "w");
    if (*book_file == NULL) {
        printf("Kitaplar.csv dosyası yazılamadı!\n");
         *book_file = fopen("Kitaplar.csv", "a+"); return;
    }
    KITAP *current_write = *head;
    while (current_write != NULL) {
        fprintf(*book_file, "%s,%s,%d\n", current_write->ad, current_write->ISBN, current_write->adet);
        current_write = current_write->next;
    }
    fflush(*book_file);
    fclose(*book_file);
    *book_file = fopen("Kitaplar.csv", "a+");
    if (*book_file == NULL) printf("Kitaplar.csv a+ modunda açılamadı.\n");

    printf("Kitap bilgileri güncellendi.\n");
}

void book_display(FILE **book_file, KITAP **head) {

    if (*head == NULL) {
        printf("Henüz dosyada kitap yok!\n");
        return;
    }

    printf("\n=== KİTAP LİSTESİ ===\n");
    KITAP *current = *head;
    int index = 1;
    while (current != NULL) {
        printf("%d. %s\n", index, current->ad);
        printf("   ISBN: %s\n", current->ISBN);
        printf("   Toplam Adet: %d\n", current->adet);
        
        printf("   Örnekler (Durum):\n");
        KITAPORNEK *copy = current->ornekler;
        if (copy == NULL) {
            printf("     Bu kitaba ait örnek bulunmamaktadır (veya adet 0).\n");
        }
        while (copy != NULL) {
            printf("     - %s : %s\n", copy->ornekID, copy->durum);
            copy = copy->next;
        }
        printf("\n");
        current = current->next;
        index++;
    }
}

void bubble_sort_books(KITAP **head) {

    if (*head == NULL || (*head)->next == NULL) {
        return; 
    }
    int swapped;
    KITAP *ptr1;
    KITAP *lptr = NULL; 

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->ad, ptr1->next->ad) > 0) { 
                // Swap data
                char temp_ad[100]; strcpy(temp_ad, ptr1->ad);
                char temp_isbn[20]; strcpy(temp_isbn, ptr1->ISBN);
                int temp_adet = ptr1->adet;
                KITAPORNEK *temp_ornekler = ptr1->ornekler;

                strcpy(ptr1->ad, ptr1->next->ad);
                strcpy(ptr1->ISBN, ptr1->next->ISBN);
                ptr1->adet = ptr1->next->adet;
                ptr1->ornekler = ptr1->next->ornekler;

                strcpy(ptr1->next->ad, temp_ad);
                strcpy(ptr1->next->ISBN, temp_isbn);
                ptr1->next->adet = temp_adet;
                ptr1->next->ornekler = temp_ornekler;
                
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("Kitaplar ada göre sıralandı (Bubble Sort).\n");
}

void book_author_link(FILE **book_author_file, KITAPYAZAR **ky_head, KITAP *book_head, YAZAR *author_head, FILE **book_file_ref, FILE **author_file_ref) {

    if (book_head == NULL) {
        printf("Kitap listesi boş. Önce kitap ekleyin.\n");
        return;
    }
    if (author_head == NULL) {
        printf("Yazar listesi boş. Önce yazar ekleyin.\n");
        return;
    }

    printf("\nMevcut Kitaplar:\n");
    KITAP *ptr_k = book_head;
    int k_idx = 1;
    while(ptr_k != NULL){
        printf("%d. ISBN: %s - Ad: %s\n", k_idx++, ptr_k->ISBN, ptr_k->ad);
        ptr_k = ptr_k->next;
    }

    char target_isbn[20];
    printf("Yazarını eşleştirmek istediğiniz kitabın ISBN'ini girin: ");
    scanf("%19s", target_isbn);

    KITAP *selected_book = book_head;
int book=atoi(selected_book->ISBN);
int book2=atoi(target_isbn);
    while(selected_book != NULL && book!=book2) {
        printf("kontrol edilen ID %s ---%s\n",selected_book->ISBN,target_isbn);
        selected_book = selected_book->next;
         book=atoi(selected_book->ISBN);
    }
    if(selected_book == NULL){
        printf("ISBN %s ile kitap bulunamadı.\n", target_isbn);
        return;
    }

    printf("\nMevcut Yazarlar:\n");
    YAZAR *ptr_y = author_head;
    while(ptr_y != NULL){
        printf("Sıra: %d - Ad: %s Soyad: %s\n", ptr_y->sira, ptr_y->ad, ptr_y->soyad);
        ptr_y = ptr_y->next;
    }
    int target_yazar_sira;
    printf("Seçilen kitaba (%s) atanacak yazarın Sıra Numarasını girin: ", selected_book->ad);
    scanf("%d", &target_yazar_sira);

    YAZAR *selected_author = author_head;
    while(selected_author != NULL && selected_author->sira != target_yazar_sira){
        selected_author = selected_author->next;
    }
    if(selected_author == NULL){
        printf("Sıra No %d ile yazar bulunamadı.\n", target_yazar_sira);
        return;
    }

    KITAPYAZAR *check_ky = *ky_head;
    while(check_ky != NULL) {
        if(strcmp(check_ky->ISBN, selected_book->ISBN) == 0 && check_ky->yazarID == selected_author->sira) {
            printf("Bu kitap-yazar eşleşmesi zaten mevcut.\n");
            return;
        }
        check_ky = check_ky->next;
    }


    KITAPYAZAR *new_link = (KITAPYAZAR*)malloc(sizeof(KITAPYAZAR));
    if(new_link == NULL){
        printf("Bellek hatası (KitapYazar)!\n");
        return;
    }
    strcpy(new_link->ISBN, selected_book->ISBN);
    new_link->yazarID = selected_author->sira;
    new_link->next = NULL;

    if(*ky_head == NULL){
        *ky_head = new_link;
    } else {
        KITAPYAZAR *temp_ky = *ky_head;
        while(temp_ky->next != NULL){
            temp_ky = temp_ky->next;
        }
        temp_ky->next = new_link;
    }

    fclose(*book_author_file); 
    *book_author_file = fopen("KitapYazar.csv", "a"); 
    if (*book_author_file == NULL) {
        printf("KitapYazar.csv dosyası append için açılamadı!\n");
        *book_author_file = fopen("KitapYazar.csv", "a+"); 
        return;
    }
    fprintf(*book_author_file, "%s,%d\n", new_link->ISBN, new_link->yazarID);
    fflush(*book_author_file);
    fclose(*book_author_file);
    *book_author_file = fopen("KitapYazar.csv", "a+"); 
    if (*book_author_file == NULL) printf("KitapYazar.csv a+ modunda tekrar açılamadı.\n");

    printf("Kitap '%s' (ISBN: %s) ile yazar '%s %s' (ID: %d) başarıyla eşleştirildi.\n",
           selected_book->ad, selected_book->ISBN, selected_author->ad, selected_author->soyad, selected_author->sira);
}

void load_kitap_islemleri_from_file(FILE **islem_file, KITAPISLEM **islem_head) {
    if (ftell(*islem_file) > 0) rewind(*islem_file);

    KITAPISLEM *temp_node;
    while (*islem_head != NULL) {
        temp_node = *islem_head;
        *islem_head = (*islem_head)->next;
        free(temp_node);
    }

 char *line = (char*)malloc(200 * sizeof(char));

if (line == NULL) {
   printf("Bellek hatası!\n");
   return;
}

    KITAPISLEM *tail = NULL;
  while (fgets(line, 200, *islem_file) != NULL) {
   line[strcspn(line, "\r\n")] = 0;
   
   if (strlen(line) >= 10) {
       KITAPISLEM *new_node = (KITAPISLEM*)malloc(sizeof(KITAPISLEM));
       if (new_node == NULL) {
           printf("Bellek hatası (KitapIslem)!\n");
           return;
       }

       char *token = strtok(line, ",");
       if (token) {
           strcpy(new_node->kitapEtiketKod, token);
           
           token = strtok(NULL, ",");
           if (token) {
               new_node->ogrenciID = atoi(token);
               
               token = strtok(NULL, ",");
               if (token) {
                   new_node->islemTuru = atoi(token);
                   
                   token = strtok(NULL, ",");
                   if (token) {
                       strcpy(new_node->tarih, token);
                       
                       new_node->next = NULL;

                       if (*islem_head == NULL) {
                           *islem_head = new_node;
                           tail = new_node;
                       } else {
                           tail->next = new_node;
                           tail = new_node;
                       }
                   } else {
                       free(new_node);
                   }
               } else {
                   free(new_node);
               }
           } else {
               free(new_node);
           }
       } else {
           free(new_node);
       }
   }
}
}

void update_book_copy_statuses_on_load(KITAP *book_head, KITAPISLEM *islem_head) {
    KITAPISLEM *islem_ptr = islem_head;
    
    while (islem_ptr != NULL) {
        if (islem_ptr->islemTuru == 0) { 
            int returned = 0;
            KITAPISLEM *check_return = islem_head;

            while (check_return != NULL && !returned) {
                if (check_return->ogrenciID == islem_ptr->ogrenciID &&
                    strcmp(check_return->kitapEtiketKod, islem_ptr->kitapEtiketKod) == 0 &&
                    check_return->islemTuru == 1 &&
                    calculate_days_difference(islem_ptr->tarih, check_return->tarih) >= 0) {
                    returned = 1;
                }
                check_return = check_return->next;
            }
            
            if (!returned) { 
                KITAP *kitap_ptr = book_head;
                int found = 0;
                
                while (kitap_ptr != NULL && !found) {
                    KITAPORNEK *ornek_ptr = kitap_ptr->ornekler;
                    
                    while (ornek_ptr != NULL && !found) {
                        if (strcmp(ornek_ptr->ornekID, islem_ptr->kitapEtiketKod) == 0) {
                            strcpy(ornek_ptr->durum, "ODUNC");
                            found = 1;
                        }
                        ornek_ptr = ornek_ptr->next;
                    }
                    kitap_ptr = kitap_ptr->next;
                }
            }
        }
        islem_ptr = islem_ptr->next;
    }
}

void book_student1(FILE **book_student_file, KITAPISLEM **head_islem, KITAP **head_kitap, FILE **book_file_ref, FILE **student_file_ref, OGRENCI **head_ogrenci) {
                  
    if (*head_kitap == NULL) {
        printf("Henüz dosyada kitap yok!\n");
        return;
    }
    if (*head_ogrenci == NULL) {
        printf("Henüz dosyada öğrenci yok!\n");
        return;
    }
    
    printf("\nMevcut Kitaplar (ve Örnek Durumları):\n");
    book_display(book_file_ref, head_kitap); 

    printf("\nMevcut Öğrenciler:\n");
    student_display(student_file_ref, head_ogrenci);
    
    int student_id_input;
    char *book_isbn_input = (char*)malloc(20 * sizeof(char));
    int islem_turu_choice;

    printf("\nİşlem türü seçin:\n0 - Kitap Ödünç Al\n1 - Kitap Teslim Et\nSeçiminiz: ");
    scanf("%d", &islem_turu_choice);
    getchar(); 

    printf("Öğrenci ID'sini girin: ");
    scanf("%d", &student_id_input);
    getchar(); 

    OGRENCI *selected_student = find_student_by_id(*head_ogrenci, student_id_input);
    if (selected_student == NULL) {
        printf("%d ID'li öğrenci bulunamadı!\n", student_id_input);
        free(book_isbn_input);
        return;
    }
    printf("%d id li öğrenci:%s \n", selected_student->id, selected_student->ad);

    printf("İşlem yapılacak kitabın ISBN numarasını girin: ");
    scanf("%19s", book_isbn_input);
    getchar();

    KITAP *selected_book = *head_kitap;
int book=atoi(selected_book->ISBN);
int book2=atoi(book_isbn_input);
    if (selected_book == NULL) {
        printf("%s ISBN'li kitap bulunamadı!\n", book_isbn_input);
        free(book_isbn_input);
        return;
    }

    KITAPORNEK *target_copy = NULL;

    if (islem_turu_choice == 0) { // Ödünç Alma
        if (selected_student->puan < 0) {
            printf("Öğrencinin puanı (%d) negatif olduğu için kitap alamaz!\n", selected_student->puan);
            free(book_isbn_input);
            return;
        }

        KITAPORNEK *copy_iter = selected_book->ornekler;
        while(copy_iter != NULL) {
            if (strcmp(copy_iter->durum, "RAFTA") == 0) {
                target_copy = copy_iter;
                copy_iter = NULL; // Döngüyü sonlandır
            } else {
                copy_iter = copy_iter->next;
            }
        }
        
        if (target_copy == NULL) {
            printf("'%s' adlı kitabın rafta boşta örneği bulunmamaktadır.\n", selected_book->ad);
            free(book_isbn_input);
            return;
        } 
        char number[20]; sprintf(number,"%d",selected_student->id);
        strcpy(target_copy->durum, number); 
        printf("Kitap '%s' (Örnek ID: %s), öğrenci '%s %s' (ID: %d) adına ödünç verildi.\n",
               selected_book->ad, target_copy->ornekID, selected_student->ad, selected_student->soyad, selected_student->id);

    } else if (islem_turu_choice == 1) { 
        printf("Öğrenci %s %s (ID: %d) tarafından ödünç alınmış olan '%s' kitabının örnekleri:\n",
            selected_student->ad, selected_student->soyad, selected_student->id, selected_book->ad);
        
        KITAPISLEM *islem_iter = *head_islem;
        KITAPORNEK **student_borrowed_copies = (KITAPORNEK**)malloc(selected_book->adet * sizeof(KITAPORNEK*));
        int borrowed_count = 0;

        while(islem_iter != NULL) {
            if(islem_iter->ogrenciID == selected_student->id && 
               strncmp(islem_iter->kitapEtiketKod, selected_book->ISBN, strlen(selected_book->ISBN)) == 0 && 
               islem_iter->islemTuru == 0) { 
                int is_active_loan = 1;
                KITAPISLEM *return_check_iter = *head_islem;
                
                while(return_check_iter != NULL) {
                    if( strcmp(return_check_iter->kitapEtiketKod, islem_iter->kitapEtiketKod) == 0 &&
                       return_check_iter->ogrenciID == selected_student->id &&
                       return_check_iter->islemTuru == 1 && 
                       calculate_days_difference(islem_iter->tarih, return_check_iter->tarih) >=0 ) { 
                       is_active_loan = 0;
                       return_check_iter = NULL; // Döngüyü sonlandır
                    } else {
                        return_check_iter = return_check_iter->next;
                    }
                }
                
                if(is_active_loan){
                     KITAPORNEK *copy_ptr = selected_book->ornekler;
                     int found_copy = 0;
                     while(copy_ptr != NULL && !found_copy){
                         if(strcmp(copy_ptr->ornekID, islem_iter->kitapEtiketKod) == 0){
                            printf("- Örnek ID: %s (Alış Tarihi: %s)\n", copy_ptr->ornekID, islem_iter->tarih);
                            student_borrowed_copies[borrowed_count++] = copy_ptr;
                            found_copy = 1;
                         }
                         copy_ptr = copy_ptr->next;
                     }
                }
            }
            islem_iter = islem_iter->next;
        }
        
        if (borrowed_count == 0) {
            printf("Öğrenci %s %s, '%s' adlı kitaptan aktif olarak ödünç alınmış bir örneğe sahip değil.\n",
                   selected_student->ad, selected_student->soyad, selected_book->ad);
            free(student_borrowed_copies);
            free(book_isbn_input);
            return;
        }

        char *etiket_to_return = (char*)malloc(30 * sizeof(char));
        printf("Teslim edilecek kitabın Örnek ID'sini girin: ");
        scanf("%29s", etiket_to_return);
        getchar();

        int found_target = 0;
        for(int i=0; i < borrowed_count && !found_target; ++i){
            if(strcmp(student_borrowed_copies[i]->ornekID, etiket_to_return) == 0){
                target_copy = student_borrowed_copies[i];
                found_target = 1;
            }
        }

        if (target_copy == NULL) {
            printf("Girilen Örnek ID (%s) öğrencinin aktif ödünç aldığı kopyalarla eşleşmiyor veya geçersiz.\n", etiket_to_return);
            free(etiket_to_return);
            free(student_borrowed_copies);
            free(book_isbn_input);
            return;
        }
        
        char *borrow_date_str = (char*)malloc(20 * sizeof(char));
        strcpy(borrow_date_str, "");
        islem_iter = *head_islem;
        
        while(islem_iter != NULL) {
            if(islem_iter->ogrenciID == selected_student->id && 
               strcmp(islem_iter->kitapEtiketKod, target_copy->ornekID) == 0 &&
               islem_iter->islemTuru == 0) {
                int is_latest_active_borrow = 1;
                KITAPISLEM *prev_borrow_check = *head_islem;
                
                while(prev_borrow_check != NULL && is_latest_active_borrow){
                    if( prev_borrow_check->ogrenciID == islem_iter->ogrenciID &&
                        strcmp(prev_borrow_check->kitapEtiketKod, islem_iter->kitapEtiketKod) == 0 &&
                        prev_borrow_check->islemTuru == 0 && 
                        calculate_days_difference(islem_iter->tarih, prev_borrow_check->tarih) > 0 
                        ){
                        int later_borrow_returned = 0;
                        KITAPISLEM *later_return_check = *head_islem;
                        
                        while(later_return_check != NULL && !later_borrow_returned){
                            if(strcmp(later_return_check->kitapEtiketKod, prev_borrow_check->kitapEtiketKod) == 0 &&
                               later_return_check->ogrenciID == prev_borrow_check->ogrenciID &&
                               later_return_check->islemTuru == 1 &&
                               calculate_days_difference(prev_borrow_check->tarih, later_return_check->tarih) >=0){
                                later_borrow_returned = 1;
                            }
                            later_return_check = later_return_check->next;
                        }
                        
                        if(!later_borrow_returned) { 
                           is_latest_active_borrow = 0;
                        }
                    }
                    if( prev_borrow_check->ogrenciID == islem_iter->ogrenciID &&
                        strcmp(prev_borrow_check->kitapEtiketKod, islem_iter->kitapEtiketKod) == 0 &&
                        prev_borrow_check->islemTuru == 1 && 
                        calculate_days_difference(islem_iter->tarih, prev_borrow_check->tarih) >= 0 
                    ){
                        is_latest_active_borrow = 0; 
                    }
                    prev_borrow_check = prev_borrow_check->next;
                }

                if(is_latest_active_borrow){
                    strcpy(borrow_date_str, islem_iter->tarih);
                    islem_iter = NULL; 
                } else {
                    islem_iter = islem_iter->next;
                }
            } else {
                islem_iter = islem_iter->next;
            }
        }

        if(strlen(borrow_date_str) == 0){
            printf("Bu kopya için aktif bir ödünç alma kaydı bulunamadı. Veri tutarsızlığı olabilir.\n");
            free(borrow_date_str);
            free(etiket_to_return);
            free(student_borrowed_copies);
            free(book_isbn_input);
            return;
        }

        char *current_date_str = (char*)malloc(20 * sizeof(char));
        get_current_date(current_date_str);
        int days_borrowed = calculate_days_difference(borrow_date_str, current_date_str);

        printf("Kitap '%s' (Örnek ID: %s), %s tarihinde alınmış. Bugün %s. %d gün geçmiş.\n",
               selected_book->ad, target_copy->ornekID, borrow_date_str, current_date_str, days_borrowed);

        if (days_borrowed > 15) {
            printf("Kitap 15 günden fazla (%d gün) süreyle tutulmuş. Ceza uygulanacak.\n", days_borrowed);
            selected_student->puan -= 10; 
            printf("Öğrencinin yeni puanı: %d\n", selected_student->puan);
        } else {
            printf("Kitap zamanında teslim edildi.\n");
        }
        strcpy(target_copy->durum, "RAFTA"); 
        printf("Kitap '%s' (Örnek ID: %s) teslim alındı.\n", selected_book->ad, target_copy->ornekID);
        
        free(current_date_str);
        free(borrow_date_str);
        free(etiket_to_return);
        free(student_borrowed_copies);
        
    } else {
        printf("Geçersiz işlem türü.\n");
        free(book_isbn_input);
        return;
    }

    KITAPISLEM *new_islem = (KITAPISLEM*)malloc(sizeof(KITAPISLEM));
    if (new_islem == NULL) {
        printf("Bellek hatası (KitapIslem)!\n");
        if(target_copy && islem_turu_choice == 0) strcpy(target_copy->durum, "RAFTA"); 
        if(target_copy && islem_turu_choice == 1) strcpy(target_copy->durum, "ODUNC"); 
        free(book_isbn_input);
        return;
    }
    new_islem->ogrenciID = selected_student->id;
    strcpy(new_islem->kitapEtiketKod, target_copy->ornekID);
    new_islem->islemTuru = islem_turu_choice;
    get_current_date(new_islem->tarih); 
    new_islem->next = NULL;

    if (*head_islem == NULL) {
        *head_islem = new_islem;
    } else {
        KITAPISLEM *temp_islem = *head_islem;
        while (temp_islem->next != NULL) {
            temp_islem = temp_islem->next;
        }
        temp_islem->next = new_islem;
    }

    fclose(*book_student_file); 
    *book_student_file = fopen("KitapOdunc.csv", "a");
    if(*book_student_file == NULL) {
        printf("KitapOdunc.csv dosyası append için açılamadı.\n");
        *book_student_file = fopen("KitapOdunc.csv", "a+");
        free(book_isbn_input);
        return;
    }
    fprintf(*book_student_file, "%s,%d,%d,%s\n", 
            new_islem->kitapEtiketKod, new_islem->ogrenciID, 
            new_islem->islemTuru, new_islem->tarih);
    fflush(*book_student_file);
    fclose(*book_student_file);
    *book_student_file = fopen("KitapOdunc.csv", "a+");
     if (*book_student_file == NULL) printf("KitapOdunc.csv a+ modunda tekrar açılamadı.\n");

    if (islem_turu_choice == 1) { 
        fclose(*student_file_ref);
        *student_file_ref = fopen("Ogrenciler.csv", "w");
        if (*student_file_ref != NULL) {
            OGRENCI *temp_s_write = *head_ogrenci;
            while (temp_s_write != NULL) {
                fprintf(*student_file_ref, "%d,%s,%s,%d\n", 
                        temp_s_write->id, temp_s_write->ad, temp_s_write->soyad, temp_s_write->puan);
                temp_s_write = temp_s_write->next;
            }
            fflush(*student_file_ref);
            fclose(*student_file_ref);
            *student_file_ref = fopen("Ogrenciler.csv", "a+");
            if (*student_file_ref == NULL) printf("Ogrenciler.csv a+ modunda tekrar açılamadı (güncelleme sonrası).\n");
        } else {
             printf("Ogrenciler.csv (w) puan güncelleme için açılamadı.\n");
             *student_file_ref = fopen("Ogrenciler.csv", "a+"); 
        }
    }
    printf("İşlem başarıyla kaydedildi.\n");
    free(book_isbn_input);
}

void display_not_delivered_book(KITAPISLEM *islem_head, OGRENCI *student_list_head) {
    if (islem_head == NULL) {
        printf("Henüz kitap işlemi kaydı bulunmamaktadır.\n");
        return;
    }
    if (student_list_head == NULL) {
        printf("Öğrenci listesi boş.\n");
        return;
    }

    printf("\n=== AKTİF ÖDÜNÇ ALINMIŞ KİTAPLAR (TESLİM EDİLMEMİŞ) ===\n");
    printf("%-12s %-20s %-20s %-25s %-15s\n", 
           "Öğrenci ID", "Ad", "Soyad", "Kitap Etiket Kodu", "Alış Tarihi");
    printf("-----------------------------------------------------------------------------------------------------\n");
    
    int found_active_loans = 0;
    KITAPISLEM *current_islem = islem_head;
    
    while (current_islem != NULL) {
        if (current_islem->islemTuru == 0) { 
            int delivered = 0;
            KITAPISLEM *check_delivery = islem_head;
            while (check_delivery != NULL) {
                if (check_delivery->ogrenciID == current_islem->ogrenciID &&
                    strcmp(check_delivery->kitapEtiketKod, current_islem->kitapEtiketKod) == 0 &&
                    check_delivery->islemTuru == 1 && 
                    calculate_days_difference(current_islem->tarih, check_delivery->tarih) >= 0) { 
                    delivered = 1;
                    break;
                }
                check_delivery = check_delivery->next;
            }
            
            if (!delivered) {
                OGRENCI *student = find_student_by_id(student_list_head, current_islem->ogrenciID);
                if (student != NULL) {
                    printf("%-12d %-20s %-20s %-25s %-15s\n",
                           current_islem->ogrenciID, student->ad, student->soyad,
                           current_islem->kitapEtiketKod, current_islem->tarih);
                } else {
                    printf("%-12d %-20s %-20s %-25s %-15s\n",
                           current_islem->ogrenciID, "Bilinmiyor", "Bilinmiyor",
                           current_islem->kitapEtiketKod, current_islem->tarih);
                }
                found_active_loans++;
            }
        }
        current_islem = current_islem->next;
    }
    
    if (found_active_loans == 0) {
        printf("Teslim edilmemiş (aktif ödünç alınmış) kitap bulunmamaktadır.\n");
    } else {
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("Toplam aktif ödünç alınmış kitap sayısı: %d\n", found_active_loans);
    }
    printf("\nDevam etmek için bir tuşa basın...");
    getchar(); 
    getchar(); 
}

OGRENCI* find_student_by_id(OGRENCI *head, int id) {
    OGRENCI *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void free_student_list(OGRENCI *head) { 
    OGRENCI *current = head;
    OGRENCI *next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

void negative_point(FILE **student_file, OGRENCI **head) {

    if (*head == NULL) {
        printf("Henüz dosyada öğrenci yok!\n");
        return;
    }
    
    int found = 0;
    printf("\n=== PUANI NEGATİF OLAN (CEZALI) ÖĞRENCİLER ===\n");
    printf("%-12s %-20s %-20s %-10s\n", "ID", "Ad", "Soyad", "Puan");
    printf("---------------------------------------------------------------\n");
    
    OGRENCI *current = *head;
    while (current != NULL) {
        if (current->puan < 0) {
            printf("%-12d %-20s %-20s %-10d\n", 
                   current->id, current->ad, current->soyad, current->puan);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Puanı negatif olan öğrenci bulunmamaktadır.\n");
    }
    printf("---------------------------------------------------------------\n");
}

void book_shelf(FILE **book_file, KITAP **head) {

    if (*head == NULL) {
        printf("Henüz dosyada kitap yok!\n");
        return;
    }
    
    printf("\n=== RAFTA OLAN KITAPLAR ===\n");
    printf("%-40s %-20s %-25s %-10s\n", "Kitap Adi", "ISBN", "Ornek ID", "Durum");
    printf("------------------------------------------------------------------------------------------\n");
    
    int found_on_shelf = 0;
    KITAP *current_book = *head;
    
    while (current_book != NULL) {
        KITAPORNEK *ornek = current_book->ornekler;
        while (ornek != NULL) {
            if (strcmp(ornek->durum, "RAFTA") == 0) {
                printf("%-40.39s %-20s %-25s %-10s\n", 
                       current_book->ad, 
                       current_book->ISBN, 
                       ornek->ornekID, 
                       ornek->durum);
                found_on_shelf++;
            }
            ornek = ornek->next;
        }
        current_book = current_book->next;
    }
    
    if (found_on_shelf == 0) {
        printf("Rafta uygun kitap bulunamadı.\n");
    } else {
        printf("------------------------------------------------------------------------------------------\n");
        printf("Toplam rafta olan kitap sayısı: %d\n", found_on_shelf);
    }
}

struct tm string_to_date(char* date_str) {
    struct tm tm_date = {0}; 
    if (sscanf(date_str, "%d.%d.%d", &tm_date.tm_mday, &tm_date.tm_mon, &tm_date.tm_year) == 3) {
    } 
    else if (sscanf(date_str, "%d/%d/%d", &tm_date.tm_mday, &tm_date.tm_mon, &tm_date.tm_year) == 3) {
    }
    else if (sscanf(date_str, "%d-%d-%d", &tm_date.tm_year, &tm_date.tm_mon, &tm_date.tm_mday) == 3) {
        tm_date.tm_year += 0;
    } else {
        printf("Geçersiz tarih formatı: %s. DD.MM.YYYY, DD/MM/YYYY veya YYYY-MM-DD bekleniyor.\n", date_str);
        tm_date.tm_year = 0; 
        tm_date.tm_mday = 0; 
        return tm_date;
    }

    tm_date.tm_mon -= 1; 
    if(tm_date.tm_year > 1900) tm_date.tm_year -= 1900; 
    else if (tm_date.tm_year < 70 && tm_date.tm_year !=0) tm_date.tm_year +=100; 
    
    if (tm_date.tm_mday < 1 || tm_date.tm_mday > 31 || tm_date.tm_mon < 0 || tm_date.tm_mon > 11 ) {
         tm_date.tm_year = 0; tm_date.tm_mday = 0; 
    }
    return tm_date;
}

int calculate_days_difference(char* date1_str, char* date2_str) {
    struct tm tm1 = string_to_date(date1_str);
    struct tm tm2 = string_to_date(date2_str);

    if (tm1.tm_mday == 0 || tm2.tm_mday == 0) {
        return -9999;
    }

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    
    if (time1 == -1 || time2 == -1) {
        return -9998; //  mktime failure
    }
    
    double difference = difftime(time2, time1); 
    return (int)(difference / (24 * 60 * 60)); 
}

void get_current_date(char* date_str) {
    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t); 
    sprintf(date_str, "%02d.%02d.%04d", tm_info.tm_mday, tm_info.tm_mon + 1, tm_info.tm_year + 1900);
}

void list_overdue_books(FILE **book_student_file, KITAPISLEM **islem_head_main, OGRENCI *student_list_head) {
    if (*islem_head_main == NULL) {
        printf("Henüz kitap işlemi (ödünç/teslim) kaydı bulunmamaktadır.\n");
        return;
    }

    if (student_list_head == NULL) {
        printf("Öğrenci listesi boş.\n");
        return;
    }

    char *current_date_str = (char*)malloc(20 * sizeof(char));
    get_current_date(current_date_str);
    int found_overdue = 0;

    printf("\n=== 15 GÜNÜ GEÇMİŞ TESLİM EDİLMEMİŞ (GECİKMİŞ) KİTAPLAR ===\n");
    printf("%-12s %-18s %-18s %-25s %-12s %-10s\n",
           "Öğrenci ID", "Ad", "Soyad", "Kitap Etiket Kodu", "Alış Tarihi", "Geçen Gün");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    KITAPISLEM *islem_ptr = *islem_head_main;
    while (islem_ptr != NULL) {
        if (islem_ptr->islemTuru == 0) {
            int delivered = 0;
            KITAPISLEM *return_check_ptr = *islem_head_main;
            
            while (return_check_ptr != NULL && !delivered) {
                if (return_check_ptr->ogrenciID == islem_ptr->ogrenciID &&
                    strcmp(return_check_ptr->kitapEtiketKod, islem_ptr->kitapEtiketKod) == 0 &&
                    return_check_ptr->islemTuru == 1 &&
                    calculate_days_difference(islem_ptr->tarih, return_check_ptr->tarih) >= 0) {
                    delivered = 1;
                }
                return_check_ptr = return_check_ptr->next;
            }
            if (!delivered) { 
                int days_passed = calculate_days_difference(islem_ptr->tarih, current_date_str);
                if (days_passed > 15) {
                    OGRENCI *student = find_student_by_id(student_list_head, islem_ptr->ogrenciID);
                    if (student != NULL) {
                        printf("%-12d %-18s %-18s %-25s %-12s %-10d\n",
                               islem_ptr->ogrenciID, student->ad, student->soyad,
                               islem_ptr->kitapEtiketKod, islem_ptr->tarih, days_passed);
                    } else {
                        printf("%-12d %-18s %-18s %-25s %-12s %-10d\n",
                               islem_ptr->ogrenciID, "Bilinmiyor", "Bilinmiyor",
                               islem_ptr->kitapEtiketKod, islem_ptr->tarih, days_passed);
                    }
                    found_overdue++;
                }
            }
        }
        islem_ptr = islem_ptr->next;
    }

    if (found_overdue == 0) {
        printf("15 günü geçmiş ve teslim edilmemiş kitap bulunmamaktadır.\n");
    } else {
        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("Toplam %d adet 15 gün üzeri gecikmiş kitap bulunmaktadır.\n", found_overdue);
    }

    free(current_date_str);
    
    printf("\nDevam etmek için bir tuşa basın...");
    getchar();
    getchar(); 
}