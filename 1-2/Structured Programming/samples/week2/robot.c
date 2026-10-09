#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/*
Bir robotu bir oyun alaninda gezdirelim
Gezilen hücreler 1 olarak deðiþtirilsin
*/
int main()
{
	srand(time(NULL));  
	int r;
	int x,y;
	static int m[11][11];
	int adim,j,i,n=205;
	x=5;
	y=5;
	
	for (adim=0;adim<n;adim++)
	{
		r = rand()%4;
		switch (r)
		{
		case 0: //sag
			y=y+1;
			break;
		case 1: //sol
			y=y-1;
			break;
		case 2: //yukari
			x=x-1;
			break;
		case 3: //asagi
			x=x+1;
			break;
		}
		m[x][y]	= 1;
			
		for (i=0;i<11;i++)
		{
			for (j=0;j<11;j++)
				printf("%d ",m[i][j]);
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}
