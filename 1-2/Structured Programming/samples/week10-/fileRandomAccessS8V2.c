#include <stdio.h>
#include <stdlib.h>
#define NAME_LEN 20

typedef struct
{ 
 	int dyil;
	int puan;
	char isim[NAME_LEN]; 
	char soyisim[NAME_LEN];
} OGRENCI; 

void printf_file(char filename[])
{
	int nb,i,day,month,year;
	OGRENCI ogr;
	FILE *fs=fopen (filename,"w");
	if (fs==NULL)
	{
		printf("not opened\n");
		exit(0);
	}
	
	printf("kac kayit var\n");
	scanf("%d",&nb);
	printf("bilgilerini veriniz\n");
	for (i=0;i<nb;i++)
	{
		scanf("%d %d %s %s",&ogr.dyil,&ogr.puan, ogr.isim, ogr.soyisim);
		fprintf(fs,"%d %d %s %s\n",ogr.dyil,ogr.puan, ogr.isim, ogr.soyisim);
	}
	fclose(fs);
}

void list_file(FILE *fs)
{
	OGRENCI ogr;
	int i;
	printf("\nkisi listesi:\n");
	while (fscanf(fs,"%d %d %s %s",&ogr.dyil,&ogr.puan, ogr.isim, ogr.soyisim)==4)
	{
		printf("%d %d %s %s\n",ogr.dyil,ogr.puan, ogr.isim, ogr.soyisim);
    }
}

int main()
{
	char filename[20],file[20];
	FILE *data_file; 
	int k=0,nb,yil,puan;
	long offset=0,boyut;
	OGRENCI ogr;
	printf("dosya ismi veriniz\n");
	scanf( "%s", file); 
	sprintf(filename, "%s.txt", file);
    printf_file(filename);
	data_file = fopen( filename, "r+" ); 
	if (data_file == NULL) 
	{ 
		printf( "Error opening file %s.\n", filename ); 
		exit ( 1 ); 
	}
	list_file(data_file);
	return 0;
}
