// MATRIX IN FUNCTION
#include <stdio.h>
#include <stdlib.h>
float toplaMatv1(float **,int,int);
float **dynamicMemoryAllocate(int,int);
void freeMat (float **,int);

int main()
{
	int row,column,i,j;
	float **matrix,*p;
	printf("1-9 araliginda olmak uzere satir ve sutun sayisini veriniz\n");
	scanf("%d %d",&row,&column);

	matrix=dynamicMemoryAllocate(row,column);
	
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			matrix[i][j]=i+(float)j/10;

	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
			printf("%f ", matrix[i][j]);
		printf("\n");
	}	
	printf("toplamv1:%f\n",toplaMatv1(matrix,row,column)); 
	//cast yapmasaniz da calisir ancak warning alirsiniz
	
	for(i=0;i<row;i++)
		printf("\tadr:%p \t value:%p\n",&matrix[i],matrix[i]);
	
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
			printf("\tadr:%p \t value:%f", &matrix[i][j],matrix[i][j]);
		printf("\n");
	}	
	
	freeMat (matrix, row);
	return 0;
		
}

float** dynamicMemoryAllocate(int row, int column)
{
	int i;
	float **matrix=(float **) calloc (row,sizeof(float*));
	for (i=0;i<row;i++)
		matrix[i]=(float*) calloc (column, sizeof(float));
	return matrix;
}

float toplaMatv1 (float **mat, int dim1, int dim2)
{
	float topla=0;
	int i,j;
	for (i=0;i<dim1;i++)
		for (j=0;j<dim2;j++)
			//topla=topla+*((float *)mat+i*dim2+j); //illegal kullanim i ve i+1. satýr elemanlarý ardýþýk deðil
			//topla=topla+*(*(mat+i)+j);  			//legal
			topla=topla+mat[i][j];
	return topla;	
}

void freeMat (float **mat, int dim1)
{
	int i;
	for(i = 0; i < dim1; i++)  
		free(mat[i]);
	free(mat);
}

