// This program calculates the transpose of a given matrix
#include <stdio.h>
#include <stdlib.h>
// TranspozeMat takes two matrices and fills the second one
// Passing matrices to functions is performed by call by reference 
// The addresses of the matrices are sent. Main function and TranspozeMat function access to the same address 
// Changes that maked by TranspozeMat function affect the matrix at main function side.
void TranspozeMat(int **,int **,int , int );
void PrintMat(int **, int , int );
void TranspozeMat(int **mat,int **transpozeM,int dim1, int dim2)
{
	int i,j;
	for (i=0;i<dim1;i++)
		for (j=0;j<dim2;j++)
			transpozeM[j][i]=mat[i][j];
}

void PrintMat(int **mat, int dim1, int dim2)
{
	int sum=0,i,j;
	for (i=0;i<dim1;i++)
	{
		for (j=0;j<dim2;j++)
			printf("%d ",mat[i][j]);
		printf("\n");
	}
			
}
int main()
{
	//We allocated space for two 50 by 50 matrices
	int **mat,**transpozeM,i,j,n,m;
	//Ask user for the row and column numbers until proper ones are provided 
	do
	{
		printf("Give row and column numbers of the matrix:\n");
		scanf("%d %d",&n,&m);
	}while ((n>50) || (m>50));

	//allocate space for matrix
	mat=(int **) calloc (n,sizeof(int*));
	for (i=0;i<n;i++)
		mat[i]=(int*) calloc (m, sizeof(int));

	//Ask user for the elements
	printf("Give the elements\n");
	for (i=0;i<n;i++)
		for (j=0;j<m;j++)
			scanf("%d",&mat[i][j]);
	
	//allocate space for transpose matrix
	transpozeM=(int **) calloc (m,sizeof(int*));
	for (i=0;i<m;i++)
		transpozeM[i]=(int*) calloc (n, sizeof(int));

	//Call the function which calculates the tranpose
    TranspozeMat(mat,transpozeM,n,m);
    
    //Print the transpose matrix
	PrintMat(transpozeM,m,n);
	return 0;
		
}



