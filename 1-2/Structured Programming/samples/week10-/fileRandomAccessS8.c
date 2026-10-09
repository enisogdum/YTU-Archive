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
	FILE *fs=fopen (filename,"wb");
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
		fwrite (&ogr,sizeof(ogr),1,fs);	
	}
	fclose(fs);
}

void list_file(FILE *fs)
{
	OGRENCI ogr;
	printf("\nkisi listesi:\n");
	fseek( fs, 0, SEEK_SET);
	fread(&ogr,sizeof(OGRENCI),1,fs);
	while(!feof(fs))	//end of file flag okunmadan dosya sonuna geldiðini anlayamaz
	{
	printf("%d %d %s %s\n",ogr.dyil,ogr.puan, ogr.isim, ogr.soyisim);
	fread(&ogr,sizeof(OGRENCI),1,fs);
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
	data_file = fopen( filename, "rb+" ); 
	if (data_file == NULL) 
	{ 
		printf( "Error opening file %s.\n", filename ); 
		exit ( 1 ); 
	}
	list_file(data_file);
	fseek( data_file, 0, SEEK_END);
 	nb=ftell(data_file)/sizeof(OGRENCI); // ftell: offset from the end of the file. herbiri 48 byte olmak üzere 3 kayýt varsa, 48*3=144 döndürür
 	fseek( data_file, 0, SEEK_SET);
	/*
	bu þekilde okuyabilmek için ilk iki int field in ardarda geldiðinden emin olmanýz gerekir? Emin olabilir miyiz? 
	2 byte þýk objeler çift numaralý adreslerde, 4 bytelýk objeler 4'e bölünebilen adreserde bulunuyorsa sorun yok
	*/
	
	while(k<nb)
    {
		fread (&yil,sizeof(int),1,data_file);	
		if (yil>2000)
		{
			fread (&puan,sizeof(int),1,data_file);	
			puan=puan+10;
			fseek( data_file, -sizeof(int), SEEK_CUR);
			fwrite (&puan,sizeof(int),1,data_file);	
		}
		offset=offset+sizeof(OGRENCI);
		fseek( data_file, offset, SEEK_SET);
		k++;
	}
	
	
	//yerleþiminden emin olmadýðýmýz bir structure varsa her structure elemaný bütün olarak okumak gerekir
	/*	
	fread (&ogr,sizeof(OGRENCI),1,data_file);
	while(k<nb)		
    {
		printf("%d\n",ogr.dyil);
		if (ogr.dyil>2000)
		{
			ogr.puan=ogr.puan+10;
			fseek( data_file, -sizeof(OGRENCI), SEEK_CUR);
			fwrite (&ogr,sizeof(OGRENCI),1,data_file);	
		}
		offset=offset+sizeof(OGRENCI);
		fseek( data_file, offset, SEEK_SET);
		fread (&ogr,sizeof(OGRENCI),1,data_file);	
		k++;
	}
	*/
	list_file(data_file);
	return 0;
}
