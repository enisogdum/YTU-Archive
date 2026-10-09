#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/*
Bir robotu bir oyun alaninda gezdirelim
Gezilen hücreler 1 olarak deðiþtirilsin
matris dýþýna çýkamasýn istersek?
*/
int main()
{
	srand(time(NULL));  
	int r;
	int x,y;
	static int m[10][10];
	int adim,j,i,n,dim;
	printf("matris boyutunu ve adim sayisini veriniz\n");
	scanf("%d %d",&dim,&n);
	x=y=dim/2;
	// 1-4 aralýðýnda yon üretelim 
	// Yapýlmasý gereken indis güncellemelerini bir matriste tutalým

	int adimMat[4][2];
	adimMat[0][0]=0;	adimMat[0][1]=1;	//sag
	adimMat[1][0]=0;	adimMat[1][1]=-1;	//sol
	adimMat[2][0]=-1;	adimMat[2][1]=0;	//yukari
	adimMat[3][0]=+1;	adimMat[3][1]=0;	//asagi
	
	for (adim=0;adim<n;adim++)
	{
		r = rand()%4;
		printf("rand:%d\n",r);
		if (((x+adimMat[r][0])<dim) && ((y+adimMat[r][1])<dim) && ((y+adimMat[r][1])>=0) && ((y+adimMat[r][1])>=0))
		{
			x+=adimMat[r][0];
			y+=adimMat[r][1];
			m[x][y]	= 1;
			for (i=0;i<dim;i++)
			{
				for (j=0;j<dim;j++)
					printf("%d ",m[i][j]);
				printf("\n");
			}
			printf("\n");
		}
		else
		{
			printf("out of bourders");
		}
	}
	return 0;
}
