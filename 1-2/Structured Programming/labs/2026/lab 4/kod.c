#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct music
{
    int StreamId;
    char username[MAX_SIZE];
    char songTitle[MAX_SIZE];
    char genre[MAX_SIZE];
    char status[MAX_SIZE];
    struct music *next;
}MUSIC;


void InputRead(MUSIC **head, FILE *input);
void AddNode(MUSIC **head, int StreamId, char username[MAX_SIZE], char songTitle[MAX_SIZE], char genre[MAX_SIZE], char status[MAX_SIZE]);
void PrintScreen(MUSIC *head);
void Ascended(MUSIC **head);
void PrintSkipped(MUSIC *head);
void PrintDat(MUSIC *head);
void FindDat(MUSIC **head);
void PrintDatScreen();


int main()
{
    FILE *input = fopen("songs.txt", "r");


    if (input == NULL)
    {
        printf("The File coudnt opened!\n");
        return 0;
    }
    MUSIC *head = NULL;

    InputRead(&head, input);
    fclose(input);
    Ascended(&head);
    PrintScreen(head);
    PrintSkipped(head);
    PrintDat(head);
    FindDat(&head);
    PrintDatScreen();
    
    return 0;
}

void InputRead(MUSIC **head, FILE *input)
{
    char line[MAX_SIZE];
    int StreamId;
    char username[MAX_SIZE];
    char songTitle[MAX_SIZE];
    char genre[MAX_SIZE];
    char status[MAX_SIZE];

    while (fgets(line, MAX_SIZE, input) != NULL)
    {
        sscanf(line,"%d %s %s %s %s", &StreamId, username, songTitle, genre, status);
        AddNode(head, StreamId, username, songTitle, genre, status);
    }
    
}

void AddNode(MUSIC **head, int StreamId, char username[MAX_SIZE], char songTitle[MAX_SIZE], char genre[MAX_SIZE], char status[MAX_SIZE])
{
    MUSIC *current = *head;
    MUSIC *NewNode = malloc(sizeof(MUSIC));
    NewNode->next = NULL;
    NewNode->StreamId = StreamId;
    strcpy(NewNode->username, username);
    strcpy(NewNode->songTitle, songTitle);
    strcpy(NewNode->genre, genre);
    strcpy(NewNode->status, status);

    if (current == NULL)
    {
        *head = NewNode;
    }
    else
    {

        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = NewNode;
    }
    
}

void Ascended(MUSIC **head)
{
    MUSIC *current = *head;

    if (current == NULL || current->next == NULL)
    {
        return;
    }
    
    int swapped = 1;
    MUSIC temp;
    while (swapped)
    {
       swapped = 0;
       current = *head;
       while (current->next != NULL)
       {
         if (current->StreamId > current->next->StreamId)
         {
            swapped = 1;
            temp.StreamId = current->StreamId;
            strcpy(temp.username, current->username);
            strcpy(temp.status, current->status);
            strcpy(temp.songTitle, current->songTitle);
            strcpy(temp.genre, current->genre);

            current->StreamId = current->next->StreamId;
            strcpy(current->username, current->next->username);
            strcpy(current->status, current->next->status);
            strcpy(current->songTitle, current->next->songTitle);
            strcpy(current->genre, current->next->genre);
    
            current->next->StreamId = temp.StreamId;
            strcpy(current->next->username, temp.username);
            strcpy(current->next->status, temp.status);
            strcpy(current->next->songTitle, temp.songTitle);
            strcpy(current->next->genre, temp.genre);

         }
         current = current->next;

       }

    }
    
    
}

void PrintScreen(MUSIC *head)
{
    MUSIC *current = head;

    if (current == NULL)
    {
        printf("No list!\n");
        return;
    }
    
    while (current != NULL)
    {
        printf("%d %s %s %s %s\n", current->StreamId, current->username, current->songTitle, current->genre, current->status);
        current = current->next;
    }
    printf("\n");
    printf("\n");
}

void PrintSkipped(MUSIC *head)
{
    MUSIC *current = head;

    if (current == NULL)
    {
        printf("No list!\n");
        return;
    }

    FILE *skipped = fopen("skipped.txt", "w");

    if (skipped == NULL)
    {
        printf("File couldnt be opened!\n");
        return;
    }

while (current != NULL)
{
    if (strcmp(current->status, "Skipped") == 0)
    {
        fprintf(skipped, "%d %s %s %s %s\n",
        current->StreamId,
        current->username,
        current->songTitle,
        current->genre,
        current->status);
    }

    current = current->next;
}
    fclose(skipped);
    
}

void PrintDat(MUSIC *head)
{
    MUSIC *current = head;

    if (current == NULL)
    {
        printf("No list!\n");
        return;
    }
    
    FILE *dat = fopen("songs.dat", "wb");

    if (dat == NULL)
    {
        printf("File couldnt be opened!\n");
        return;
    }

    while (current != NULL)
    {
        fwrite(&current->StreamId, sizeof(current->StreamId), 1, dat);
        fwrite(current->username, sizeof(current->username), 1, dat);
        fwrite(current->songTitle, sizeof(current->songTitle), 1, dat);
        fwrite(current->genre, sizeof(current->genre), 1, dat);
        fwrite(current->status, sizeof(current->status), 1, dat);

        current = current->next;
    }
    fclose(dat);
}

void FindDat(MUSIC **head)
{
    FILE *dat = fopen("songs.dat","rb");

    if (dat == NULL)
    {
        printf("File couldnt opened!\n");
        return;
    }

    int StreamIdBackUp;
    int StreamId;
    char line[MAX_SIZE];
    char username[MAX_SIZE];
    char songTitle[MAX_SIZE];
    char genre[MAX_SIZE];
    char status[MAX_SIZE];

    printf("Enter a streamid!\n");
    scanf("%d", &StreamIdBackUp);

    MUSIC *current = *head;
    while (current != NULL)
    {
        if (current->StreamId == StreamIdBackUp)
        {
            strcpy(current->status, "Liked");
            PrintDat(*head);
            PrintDatScreen();
            fclose(dat);
            return;
        }
        current = current->next;
            
    }
    fclose(dat);
}

void PrintDatScreen()
{
    FILE *dat = fopen("songs.dat","rb");

    if (dat == NULL)
    {
        printf("File couldnt opened!\n");
        return;
    }

    char line[MAX_SIZE];
    int StreamId;
    char username[MAX_SIZE];
    char songTitle[MAX_SIZE];
    char genre[MAX_SIZE];
    char status[MAX_SIZE];
    
    while (fread(&StreamId, sizeof(StreamId), 1, dat) == 1)
    {
        fread(username, sizeof(username), 1, dat);
        fread(songTitle, sizeof(songTitle), 1, dat);
        fread(genre, sizeof(genre), 1, dat);
        fread(status, sizeof(status), 1, dat);
        
        printf("%d %s %s %s %s\n",
           StreamId, username, songTitle, genre, status);
    }
    
    fclose(dat);
}