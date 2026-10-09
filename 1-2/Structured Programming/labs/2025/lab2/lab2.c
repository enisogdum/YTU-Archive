#include <stdio.h>
#include <stdlib.h>

int volume_calculator(int *matrix);
int **matrix_newsize(int **matrix, int number_boxes);
int compare(int total_area, int *total_volume, int *matrix);
int compare_v2(int *box, int *matrix);
void free_matrix(int **matrix, int number_boxes);
void PrintMatrix(int *box);

int main()
{
    int **matrix;
    int total_area;
    int total_volume = 0;
    int number_boxes = 1;

    // Initially we only have the garage
    matrix = calloc(1, sizeof(int *));

    if (matrix == NULL)
    {
        printf("Not enough memory!\n");
        return 1;
    }

    // Create garage row
    matrix[0] = calloc(4, sizeof(int));

    if (matrix[0] == NULL)
    {
        free(matrix);
        return 1;
    }

    // Garage dimensions
    printf("Enter the size of the garage:\n");
    scanf("%d %d %d",
          &matrix[0][0],
          &matrix[0][1],
          &matrix[0][2]);

    // Garage itself = 1
    matrix[0][3] = 1;

    total_area = matrix[0][0]
               * matrix[0][1]
               * matrix[0][2];

    while (1)
    {
        int *box;
        int flag = 0;

        box = calloc(4, sizeof(int));

        if (box == NULL)
        {
            printf("Not enough memory!\n");
            break;
        }

        printf("Enter the size of product and pieces:\n");

        scanf("%d %d %d %d",
              &box[0],
              &box[1],
              &box[2],
              &box[3]);

        /*
         * First check whether this new box can fit.
         * We do NOT increase number_boxes yet because
         * we haven't actually added the box.
         */
        if (!compare(total_area, &total_volume, box))
        {
            printf("\nYou used your all limit!\n");
            printf("Total Volume: %d\n\n", total_volume);

            free(box);
            break;
        }

        /*
         * Search existing boxes.
         * matrix[0] is the garage,
         * so start from 1.
         */
        for (int i = 1; i < number_boxes; i++)
        {
            if (compare_v2(box, matrix[i]))
            {
                printf("There is a same size box! Added.\n");

                matrix[i][3] += box[3];

                flag = 1;
                break;
            }
        }

        /*
         * No same-size box was found.
         * Therefore create a new row.
         */
        if (!flag)
        {
            number_boxes++;

            matrix = matrix_newsize(matrix, number_boxes);

            if (matrix == NULL)
            {
                printf("Not enough memory!\n");
                free(box);
                return 1;
            }

            for (int k = 0; k < 4; k++)
            {
                matrix[number_boxes - 1][k] = box[k];
            }
        }

        free(box);
    }

    printf("\nFinal Matrix:\n");

    for (int i = 0; i < number_boxes; i++)
    {
        PrintMatrix(matrix[i]);
    }
    printf("Total Volume : %d\n",total_volume);

    free_matrix(matrix, number_boxes);

    return 0;
}


int volume_calculator(int *matrix)
{
    return matrix[0]
         * matrix[1]
         * matrix[2]
         * matrix[3];
}


int **matrix_newsize(int **matrix, int number_boxes)
{
    int **temp;

    /*
     * Increase the number of row pointers.
     */
    temp = realloc(matrix, number_boxes * sizeof(int *));

    if (temp == NULL)
    {
        return NULL;
    }

    matrix = temp;

    /*
     * Create ONLY the new row.
     */
    matrix[number_boxes - 1] = calloc(4, sizeof(int));

    if (matrix[number_boxes - 1] == NULL)
    {
        free(matrix);
        return NULL;
    }

    return matrix;
}


int compare(int total_area, int *total_volume, int *matrix)
{
    int volume;

    volume = volume_calculator(matrix);

    if (*total_volume + volume <= total_area)
    {
        *total_volume += volume;
        return 1;
    }

    return 0;
}


int compare_v2(int *box, int *matrix)
{
    for (int j = 0; j < 3; j++)
    {
        if (box[j] != matrix[j])
        {
            return 0;
        }
    }

    return 1;
}


void free_matrix(int **matrix, int number_boxes)
{
    for (int i = 0; i < number_boxes; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
}


void PrintMatrix(int *box)
{
    printf("Width: %d - Length: %d - Depth: %d - Pieces: %d\n",
           box[0],
           box[1],
           box[2],
           box[3]);
}