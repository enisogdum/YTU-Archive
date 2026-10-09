#include <stdio.h>
int main()
{
	int i,j,*p;
	int ar[2][3]={{0,1,2},{3,4,5}};
	for (i=0;i<2;i++)
		for (j=0;j<3;j++)
			printf("adrs:%p value:%d\n",&ar[i][j],ar[i][j]);
  
  	for (i=0;i<2;i++)
		for (j=0;j<3;j++)
			printf("%d %d %d\n",ar[i][j],*(ar[i]+j),*(*(ar+i)+j));

	printf("%p %p %p %p %d",ar,ar[0],&ar[0],&ar[0][0],ar[0][0]);
	
	return 0;
}
