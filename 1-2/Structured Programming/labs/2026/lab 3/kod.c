#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct Participant
{
    int id;
    char name[50];
    char institution[50];
    int type;
    struct Participant *next;
} Participant;

void menu(void);
Participant *createParticipant(char name[], char institution[], int id, int type);
void addParticipant(Participant *new_participant, Participant **head);
void listParticipants(Participant *head);
void printType(Participant current);
Participant *searchParticipant(Participant *head, int id);
int countParticipantsRecursive(Participant *current);
int isStudent(Participant *p);
int isCompanyRepresentative(Participant *p);
void listFilteredParticipants(Participant *head, int (*filter)(Participant *));
void freeParticipants(Participant **head);

int main()
{
    int flag = 1;
    Participant *head = NULL;

    printf("--- DEMO DAY EVENT PARTICIPATION SYSTEM ---\n");

    while (flag)
    {
        int choice;
        menu();
        scanf("%d", &choice);

        if (choice == 1)
        {
            char name[MAX_SIZE];
            char institution[MAX_SIZE];
            int id;
            int type;

            printf("Enter name!\n");
            scanf("%49s", name); // Prevents overflow of Participant.name

            printf("Enter institution!\n");
            scanf("%49s", institution); // Prevents overflow of Participant.institution

            printf("Enter id!\n");
            scanf("%d", &id);

            printf("Enter type!\n");
            scanf("%d", &type);

            Participant *new_participant =
                createParticipant(name, institution, id, type);

            if (new_participant != NULL) // Do not add if malloc fails
            {
                addParticipant(new_participant, &head);
            }
        }
        else if (choice == 2)
        {
            if (head == NULL)
            {
                printf("No participant!\n");
            }
            else
            {
                listParticipants(head);
            }
        }
        else if (choice == 3)
        {
            int id;
            Participant *search_participant;

            printf("Enter the ID\n");
            scanf("%d", &id);

            search_participant = searchParticipant(head, id);

            if (search_participant != NULL) // Participant may not exist
            {
                printf("Name : %s\n", search_participant->name);
            }
            else
            {
                printf("No user!\n");
            }
        }
        else if (choice == 4)
        {
            int total_participant = countParticipantsRecursive(head);
            printf("%d\n", total_participant);
        }
        else if (choice == 5)
        {
        }
        else if (choice == 6)
        {
        }
        else if (choice == 7)
        {
            flag = 0;
            freeParticipants(&head);
        }
    }

    return 0;
}

void menu(void)
{
    printf("1 - Add participant\n"
           "2 - List participants\n"
           "3 - Search by participant ID\n"
           "4 - Calculate participant count recursively\n"
           "5 - List students\n"
           "6 - List company representatives\n"
           "7 - Exit\n");
}

Participant *createParticipant(char name[], char institution[], int id, int type)
{
    Participant *new_participant = malloc(sizeof(Participant));

    if (new_participant == NULL)
    {
        printf("Memory error!\n");
        return NULL; // Function returns a Participant pointer
    }

    strcpy(new_participant->name, name);
    strcpy(new_participant->institution, institution);
    new_participant->id = id;
    new_participant->type = type;
    new_participant->next = NULL;

    return new_participant; // Return allocated node, not a copy
}

void addParticipant(Participant *new_participant, Participant **head)
{
    if (*head == NULL)
    {
        *head = new_participant;
        return;
    }

    Participant *current = *head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = new_participant;
}

void listParticipants(Participant *head)
{
    Participant *current = head;

    while (current != NULL)
    {
        printf("Name: %s-- Id: %d-- Institution: %s\n",
               current->name, current->id, current->institution);
        printType(*current);
        current = current->next;
    }
}

void printType(Participant current)
{
    switch (current.type)
    {
        case 1:
            printf("Type: Student\n");
            break;
        case 2:
            printf("Type: Graduate\n");
            break;
        case 3:
            printf("Type: Company Representative\n");
            break;
        default:
            printf("Type: Unknown\n");
    }
}

Participant *searchParticipant(Participant *head, int id)
{
    Participant *current = head;

    while (current != NULL)
    {
        if (current->id == id) // Required: search by ID
        {
            return current;
        }

        current = current->next;
    }

    return NULL; // Participant was not found
}

int countParticipantsRecursive(Participant *current)
{
    if (current == NULL)
    {
        return 0; // Base case
    }

    return 1 + countParticipantsRecursive(current->next);
}

void freeParticipants(Participant **head)
{
    Participant *current = *head;

    while (current != NULL)
    {
        Participant *next = current->next; // Save next before free
        free(current);
        current = next;
    }

    *head = NULL; // List no longer points to freed memory
}