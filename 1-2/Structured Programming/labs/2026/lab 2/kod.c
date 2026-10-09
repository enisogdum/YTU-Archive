#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int no;
    char name[30];
    float gpa;
    int interview;
    int english;
    int disciplinary;
} Candidate;

bool eligible_for_internship(Candidate c);
void add_candidate(Candidate **array, int *n, int *capacity, Candidate new_candidate);
int best_candidate(Candidate *array, int n);
int borderline_candidate_count(Candidate *array, int n);

int main(void)
{
    int n = 0;
    int capacity = 2;

    Candidate *array = malloc(capacity * sizeof(Candidate));

    if (array == NULL)
    {
        return 1;
    }

    while (true)
    {
        Candidate candidate;

        // First, read only the candidate number.
        printf("Enter candidate number (-1 to finish): ");

        if (scanf("%d", &candidate.no) != 1)
        {
            free(array);
            return 1;
        }

        // Do not ask for other information when number is -1.
        if (candidate.no == -1)
        {
            break;
        }

        printf("Enter name, GPA, interview, English, disciplinary: ");

        if (scanf("%29s %f %d %d %d",
                  candidate.name,
                  &candidate.gpa,
                  &candidate.interview,
                  &candidate.english,
                  &candidate.disciplinary) != 5)
        {
            free(array);
            return 1;
        }

        if (eligible_for_internship(candidate))
        {
            add_candidate(&array, &n, &capacity, candidate);
        }
    }

    int best = best_candidate(array, n);

    if (best != -1)
    {
        printf("Best candidate: %d\n", best);
    }
    else
    {
        printf("No best candidate!\n");
    }

    printf("Borderline Control Number: %d\n",
           borderline_candidate_count(array, n));

    free(array);
    return 0;
}

void add_candidate(Candidate **array, int *n, int *capacity, Candidate new_candidate)
{
    if (*n == *capacity)
    {
        *capacity *= 2;

        Candidate *temp = realloc(*array, *capacity * sizeof(Candidate));

        if (temp == NULL)
        {
            free(*array);
            exit(EXIT_FAILURE);
        }

        *array = temp;
    }

    (*array)[*n] = new_candidate;
    (*n)++;
}

bool eligible_for_internship(Candidate c)
{
    return c.disciplinary == 0 &&
           c.interview >= 70 &&
           (c.gpa >= 2.50 || c.english >= 80);
}

int best_candidate(Candidate *array, int n)
{
    if (n == 0)
    {
        return -1;
    }

    int best_index = 0;

    for (int i = 1; i < n; i++)
    {
        if (array[i].interview > array[best_index].interview ||
            (array[i].interview == array[best_index].interview &&
             array[i].gpa > array[best_index].gpa) ||
            (array[i].interview == array[best_index].interview &&
             array[i].gpa == array[best_index].gpa &&
             array[i].english > array[best_index].english))
        {
            best_index = i;
        }
    }

    return array[best_index].no;
}

int borderline_candidate_count(Candidate *array, int n)
{
    int candidate_count = 0;

    for (int i = 0; i < n; i++)
    {
        if (array[i].gpa >= 2.50 && array[i].english >= 80)
        {
            candidate_count++;
        }
    }

    return candidate_count;
}