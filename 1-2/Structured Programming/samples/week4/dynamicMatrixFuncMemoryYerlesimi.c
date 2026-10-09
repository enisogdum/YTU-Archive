#include <stdio.h>
#include <stdlib.h>
int main()
{
	int row,column,i,j;
	char **matrix,*p,x='a';
	printf("1-9 araliginda olmak uzere satir ve sutun sayisini veriniz\n");
	scanf("%d %d",&row,&column);
	matrix=(char **) calloc (row,sizeof(char*));
	
	for (i=0;i<row;i++)
		matrix[i]=(char*) calloc (column, sizeof(char));

	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			matrix[i][j]=x++;

	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
			printf("%c", matrix[i][j]);
		printf("\n");
	}	
	printf("adress of mat and    value of mat:\n");
	printf("adr:%p value:%p\n",&matrix,matrix);
	
	printf("adress of mat[i] and value of mat[i]:\n");
	for(i=0;i<row;i++)
		printf("adr:%p value:%p\n",&matrix[i],matrix[i]);
	
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
			printf("adr:%p value:%c ", &matrix[i][j],matrix[i][j]);
		printf("\n");
	}	
	
	for(i = 0; i < row; i++)  
		free(matrix[i]);
	free(matrix);
	return 0;
		
}

