#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIZI_SIZE 100

typedef struct service {
    char *name;
} SERVICE;

typedef struct member {
    char *name;
    int age;
    SERVICE *services[2];
    int serviceCount;
    struct member *next;
} MEMBER;

void add_member(MEMBER **head, char* name, int age, char** services, int service_count);
void search_member(MEMBER *head, char *name);
void remove_member(MEMBER **head, char *name);
void list_tasks(MEMBER *head);
void free_members(MEMBER *head);

int main() {
    MEMBER *head = NULL;
    int game_running;
    int choice;
    char *name;
    char **service_name;
    int age;
    int count;
    int i;

    game_running = 1;

    name = (char*)malloc(DIZI_SIZE * sizeof(char));
    service_name = (char**)malloc(2 * sizeof(char*));
    for (i = 0; i < 2; i++) {
        *(service_name + i) = (char*)malloc(DIZI_SIZE * sizeof(char));
    }

    while (game_running) {
        printf("Yapacağınız işlemi seçin:\n");
        printf("1-Üye ekleme\n2-Üye arama\n3-Üye silme\n4-Listeleme\n5-Çıkış\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("İsminizi ve yaşınızı giriniz\n");
                scanf("%s %d", name, &age);

                do {
                    printf("Kaç adet servis istersiniz? 1-2\n");
                    scanf("%d", &count);
                    if (count != 1 && count != 2) {
                        printf("Yalnızca 1 veya 2 seçim yapabilirsiniz!\n");
                    }
                } while (count != 1 && count != 2);
                
                printf("servisler:\n");
                printf("1-yüzme\n2-gym\n3-tenis\n4-yoga\n5-beslenme\n");
                
                if (count == 1) {
                    printf("1 adet hizmet giriniz\n");
                    scanf("%s", *(service_name + 0));
                } else {
                    do {
                        printf("1. servisi giriniz\n");
                        scanf("%s", *(service_name + 0));
                        printf("2. servisi giriniz\n");
                        scanf("%s", *(service_name + 1));
                        if (strcmp(*(service_name + 0), *(service_name + 1)) == 0) {
                            printf("Lütfen farklı servisler giriniz!\n");
                        }
                    } while (strcmp(*(service_name + 0), *(service_name + 1)) == 0);
                }

                add_member(&head, name, age, service_name, count);
                break;

            case 2:
                printf("aranacak kişinin ismini girin:\n");
                scanf("%s", name);
                search_member(head, name);
                break;

            case 3:
                printf("silinecek kişinin ismini girin:\n");
                scanf("%s", name);
                remove_member(&head, name);
                break;

            case 4:
                list_tasks(head);
                break;

            case 5:
                game_running = 0;
                break;

            default:
                printf("Hatalı giriş yaptınız. Tekrar deneyin!\n");
                break;
        }
    }
    
    free_members(head);
    free(name);
    for (i = 0; i < 2; i++) {
        free(*(service_name + i));
    }
    free(service_name);
    
    return 0;
}

void add_member(MEMBER **head, char* name, int age, char** services, int service_count) {
    int i;
    MEMBER *new_node = (MEMBER*)malloc(sizeof(MEMBER));
    MEMBER *current;

    current = *head;
    *(new_node->services + 0) = malloc(sizeof(SERVICE));
    if (service_count == 2) {
        *(new_node->services + 1) = malloc(sizeof(SERVICE));
    }

    (*(new_node)).name = (char*)malloc(strlen(name) + 1);
    strcpy((*(new_node)).name, name);
    (*(new_node)).age = age;
    (*(new_node)).serviceCount = service_count;

    for (i = 0; i < service_count; i++) {
        (*(*(new_node->services + i))).name = (char*)malloc(strlen(*(services + i)) + 1);  
        strcpy((*(*(new_node->services + i))).name, *(services + i)); 
    }

    if ((*head) == NULL) {
        (*(new_node)).next = *head;  
        *head = new_node;
        return;
    }
    
    while ((*(current)).next != NULL) {
        current = (*(current)).next;
    }
    
    (*(new_node)).next = (*(current)).next;
    (*(current)).next = new_node;
}

void search_member(MEMBER *head, char *name) {
    int count = 0;
    MEMBER *current;

    current = head;

    while (current != NULL && strcmp((*(current)).name, name) != 0) {
        current = (*(current)).next;
        count++;
    }

    if (current != NULL && strcmp((*(current)).name, name) == 0) {
        printf("istenen kişi %d.sırada bulundu\n", count + 1);
    } else {
        printf("istenen kişi bulunamadı!\n");
    }
}

void remove_member(MEMBER **head, char *name) {
    if (*head == NULL) {
        printf("Liste boş\n");
        return;
    }
    
    MEMBER *current = *head;
    MEMBER *previous = NULL;

    while (current != NULL && strcmp((*(current)).name, name) != 0) {
        previous = current;
        current = (*(current)).next;
    }

    if (current == NULL) {
        printf("Görev bulunamadı\n");
        return;
    }

    if (previous == NULL) {
        *head = (*(current)).next;
    } else {
        (*(previous)).next = (*(current)).next;
    }

    free((*(current)).name);
    
    for (int i = 0; i < (*(current)).serviceCount; i++) {
        free((*(*(current->services + i))).name);
        free(*(current->services + i));
    }
    
    free(current);
    printf("Görev silindi: %s\n", name);
}

void list_tasks(MEMBER *head) {
    if (head == NULL) {
        printf("Liste boş\n");
        return;
    }
    
    MEMBER *temp = head;
    while (temp != NULL) {
        printf("%s %d\n", (*(temp)).name, (*(temp)).age);
        
        
        printf("Servisler: ");
        for (int i = 0; i < (*(temp)).serviceCount; i++) {
            printf("%s ", (*(*(temp->services + i))).name);
        }
        printf("\n");
        
        temp = (*(temp)).next;
    }
}

void free_members(MEMBER *head) {
    MEMBER *temp;

    while (head != NULL) {
        temp = head;
        head = (*(head)).next;

        free((*(temp)).name);

        for (int i = 0; i < (*(temp)).serviceCount; i++) {
            free((*(*(temp->services + i))).name);
            free(*(temp->services + i));
        }

        free(temp);
    }
}