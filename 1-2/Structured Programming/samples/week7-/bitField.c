#include <stdio.h>
typedef struct 
{
	unsigned int day:5;
	unsigned int month:4;
	unsigned int year:11;
}DATE;

int main()
{
	int tarih1,tarih2,tarih3,i;
	DATE dizi[3];
	for (i=0;i<3;i++)
	{
		printf("give day, month and year\n");
		scanf("%d %d %d",&tarih1,&tarih2,&tarih3);
		dizi[i].day=tarih1;
		dizi[i].month=tarih2;
		dizi[i].year=tarih3;
	}
	
	//scanf("%d %d %d",&dizi[0].day,&tarih2,&tarih3);    //illegal
	printf("%d",dizi[0].day+5);
}
