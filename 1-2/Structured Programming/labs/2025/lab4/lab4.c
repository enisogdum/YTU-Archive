#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct data {
    int ID;
    char name[50];
    char city1[50];
    char day[50];
    char situation[50];
    struct data *next;
} DATA;

// FUNCTIONS

void linked_add(DATA **head,char line[150]);
void sort_ascending(DATA **head);
void print_list(DATA *head);
void writer_list(DATA *head);
void waited_people(DATA *head);
void raport(DATA *head) ;
void free_list(DATA *head);


int main(){
    FILE *fp;
    DATA *head = NULL; // Başlangıçta NULL olarak başlat
    char buffer[150];


fp=fopen("kargolar.txt","r");

if (fp==NULL)
{
    printf("dosya açılamadı!\n");
}

while (fgets(buffer,150,fp)!=NULL)
{
    linked_add(&head,buffer);
}

fclose(fp); // Dosyayı kapat

sort_ascending(&head);
print_list(head);
writer_list(head);
waited_people(head);
raport(head);

free_list(head); // Belleği serbest bırak



    return 0;
}
// İlk olarak elemanları sırasız olarak linked liste ekle
void linked_add(DATA **head,char line[150]){
    DATA *new_node;
    DATA *current;
    int ID;
    char name[50];
    char city1[50];
    char day[50];
    char situation[50];



    // Parse et 
    if (sscanf(line, "%d %s %s %s %s", 
               &ID, name, city1, day, situation) != 5) {
        printf("Warning: Could not parse line: %s", line);
        return;
    }

    new_node = (DATA*)malloc(sizeof(DATA));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    new_node->ID=ID;
    strcpy(new_node->name,name);
    strcpy(new_node->city1,city1);
    strcpy(new_node->day,day);
    strcpy(new_node->situation,situation);
    new_node->next=NULL;



    if (*head == NULL) {
        *head = new_node;
        return;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void sort_ascending(DATA **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; 
    }

    int swapped;
    DATA *current;
    DATA temp;
// bubble-sort ile sırala
    do {
        swapped = 0;
        current = *head;

        while (current->next != NULL) {
            if (current->ID > current->next->ID) {
                
                temp.ID = current->ID;
                strcpy(temp.name, current->name);
                strcpy(temp.city1, current->city1);
                strcpy(temp.day, current->day);
                strcpy(temp.situation, current->situation);

                current->ID = current->next->ID;
                strcpy(current->name, current->next->name);
                strcpy(current->city1, current->next->city1);
                strcpy(current->day, current->next->day);
                strcpy(current->situation, current->next->situation);

                current->next->ID = temp.ID;
                strcpy(current->next->name, temp.name);
                strcpy(current->next->city1, temp.city1);
                strcpy(current->next->day, temp.day);
                strcpy(current->next->situation, temp.situation);

                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

void print_list(DATA *head){
    if (head == NULL) {
        printf("Liste boş.\n");
        return;
    }
    
    while (head != NULL) {
        printf("%d\t%-15s\t%-15s\t%s\t%s\n", 
               head->ID, head->name, head->city1, head->day, 
               head->situation);
        head = head->next;
    }
}

void writer_list(DATA *head){


    if (head==NULL)
    {
        printf("Liste boş!\n");
        exit(1);
    }
DATA *current;
FILE *out;
current=head;

char file_name[100];

while (current!=NULL)
{
    strcpy(file_name,current->name);
    out=fopen(file_name,"w");

            fprintf(out, "%s adlı göndericiye ait %d kodlu kargo,%s günü %s şehrine gönderildi.\nDurum:%s.", 
                current->name,current->ID,current->day, current->city1,
                current->situation);
        
        fclose(out);
        current = current->next;
    

}

}

void waited_people(DATA *head){

     if (head==NULL)
    {
        printf("dosya boş!\n");
        exit(1);
    }
DATA *current;
FILE *out;
current=head;

out = fopen("bekleyenler.txt", "w"); 

while (current!=NULL)
{
    if (strcmp("Beklemede",current->situation)==0)
    {
        fprintf(out,"%d %s %s %s %s\n",current->ID,current->name, current->city1,current->day,
                current->situation);
    }

        current = current->next;
}

fclose(out); 


}

void raport(DATA *head) {
    if (head == NULL) {
        printf("dosya boş!\n");
        exit(1);
    }

    FILE *out = fopen("rapor.txt", "w");
    if (out == NULL) {
        printf("Dosya açılamadı!\n");
        exit(1);
    }

    char cities[100][50];
    int delivered[100] = {0};
    int waited[100] = {0};
    int city_count = 0;

    DATA *current = head;
    while (current != NULL) {
        int found_index = -1;

        for (int i = 0; i < city_count; i++) {
            if (strcmp(cities[i], current->city1) == 0) {
                found_index = i;
            }
        }

        if (found_index == -1) {
            strcpy(cities[city_count], current->city1);
            found_index = city_count;
            city_count++;
        }

        if (strcmp(current->situation, "TeslimEdildi") == 0) {
            delivered[found_index]++;
        } else if (strcmp(current->situation, "Beklemede") == 0) {
            waited[found_index]++;
        }

        current = current->next;
    }

    for (int i = 0; i < city_count; i++) {
        fprintf(out, "%s -> TeslimEdildi: %d, Beklemede: %d\n", cities[i], delivered[i], waited[i]);
    }

    fclose(out);
}

void free_list(DATA *head) {
    DATA *current = head;
    DATA *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}