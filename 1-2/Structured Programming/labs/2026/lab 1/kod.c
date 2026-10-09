#include <stdio.h>
#include <stdlib.h>


int main()
{
    int n;
    int** matrix;
    int total_sum = 0;


    printf("Enter the dimension of matrix!\n");
    scanf("%d", &n);

    matrix = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        *(matrix + i) = calloc(n, sizeof(int));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d",&(*(*(matrix + (i) ) + j)));
        }
        
    }
    

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int flag = 1;
            while (flag)
            {
                if ((i - 1) >= 0 && *(*(matrix + (i - 1) ) + j) >= *(*(matrix + (i) ) + j))
                {
                    flag = 0;
                }else if ((j - 1) >= 0 && *(*(matrix + (i) )+ (j - 1)) >= *(*(matrix + (i) ) + j))
                {
                    flag = 0;
                }else if ((j + 1) < n && *(*(matrix + (i) )+ (j + 1)) >= *(*(matrix + (i) ) + j))
                {
                    flag = 0;
                }else if ((i + 1) < n && *(*(matrix + (i + 1) )+ j) >= *(*(matrix + (i)) + j))
                {
                    flag = 0;
                }

                if (flag)
                {
                    flag = 0;
                    total_sum += *(*(matrix + (i) ) + j);
                    printf("Value: %d ,Location: (%d,%d)\n",*(*(matrix + (i)) + j), i, j);
                }
                
                
            }
            
        }
        
    }
    
    printf("Total Value : %d\n", total_sum);

  for (int i = 0; i < n; i++)
   {
     free(matrix[i]);
   }
   free(matrix);  // free the array of row pointers itself
    


    return 0;
}