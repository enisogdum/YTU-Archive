#include <stddef.h>
#include <stdio.h> 
#define FAIL 0 
#define SUCCESS 1 
#define LINESIZE 100
int copyfileLinebyLine(char * infile, char * outfile)
{ 
	FILE *fp1, *fp2; 
	char line [LINESIZE] ; 
	int lineNum=0;
	if ((fp1 = fopen( infile, "r"  ))== NULL) return FAIL; 
	if ((fp2 = fopen( outfile, "w" )) == NULL)
	{ 
		fclose ( fp1 ); 
		return FAIL; 
	}
	//fgets() newline veya end-of-file ile karsilasana kadar ya da en fazla LINESIZE-1 karakter okur
	//fgets() line[] icerisine ekledigi karakterlerin sonuna NULL ekler
	//dosya sonuna olastiya NULL, aksi takdirde okudugu char* 'i dondurur
	//LINESIZE 10 olsaydý ne olurdu?
	//yine düzgün kopyalardý. Ama kopyalamada daha hala döngüde biterdi
	while (fgets( line, LINESIZE-1, fp1 ) != NULL) 
	{
		fputs( line, fp2 ); // function writes a string to the specified stream up to but not including the null character.
		lineNum++;
	}
	fprintf(fp2,"dosyada %d line var\n",lineNum);
	fclose( fp1 ); 
	fclose( fp2 ); 
	return SUCCESS; 
}

int copyfileCharbyChar(char * infile, char * outfile)
{ 
	FILE *fp1, *fp2; 
	char ch,ch2; 
	int charNum=0;
	if ((fp1 = fopen( infile, "r"  ))== NULL) return FAIL; 
	if ((fp2 = fopen( outfile, "a" )) == NULL)   // w modda açýlsaydi ayni kopya bir daha olusurdu. a modda acilirsa altina yazar
	{ 
		fclose ( fp1 ); 
		return FAIL; 
	}
	fscanf(fp1,"%c",&ch2);					// burada tek char okundugu icin ikinci dosyaya ilk char yazilamaz
	ch=getc(fp1);						
	while (!feof(fp1))   //dosya sonu ise non-zero, degilse zero
	{
		putc(ch,fp2);   //or fputc(ch,fp2);
		ch=getc(fp1);   //or ch=fgetc(fp1); 
		charNum++;
	}

	fclose( fp1 ); 
	fprintf(fp2,"dosyada %d char var\n",charNum);
	fclose( fp2 ); 
	return SUCCESS; 
}


int writeformat(char * infile, char * outfile)
{ 
	FILE *fp1, *fp2; 
	char ch,ch2; 
	int num;
	char isim1[50],isim2[50];
	int charNum=0;
	if ((fp1 = fopen( infile, "r"  ))== NULL) return FAIL; 
	if ((fp2 = fopen( outfile, "a" )) == NULL)   // w modda açýlsaydi ayni kopya bir daha olusurdu. a modda acilirsa altina yazar
	{ 
		fclose ( fp1 ); 
		return FAIL; 
	}
	fscanf(fp1,"%d %s %s",&num,isim1,isim2);			
	while (!feof(fp1))   //dosya sonu ise non-zero, degilse zero
	{
		printf("%d %s %s\n",num,isim1,isim2);
		fscanf(fp1,"%d %s %s",&num,isim1,isim2);				
	}

	fclose( fp1 ); 
	fprintf(fp2,"dosyada %d char var\n",charNum);
	fclose( fp2 ); 
	return SUCCESS; 
}

int main()
{
	char file1[20],file2[20];
	printf("input ve output dosyalarini veriniz\n");
	scanf("%s %s",file1,file2);
	//writeformat(file1,file2);
	
    if (copyfileLinebyLine(file1,file2)==SUCCESS) 
		printf("dosya line line kopyalandi\n");
	else
		printf("dosya kopyalanamadi\n");

	if (copyfileCharbyChar(file1,file2)==SUCCESS)
		printf("dosya char char kopyalandi\n");
	else
		printf("dosya kopyalanamadi\n");

	return 0;
}
