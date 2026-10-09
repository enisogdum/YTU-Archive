// DYNAMIC MEMORY ALLOCATION
#include <stdio.h>
#include <stdlib.h>
int *YerGenislet (int *, int , int );
void OgrenciAl (int *, int, int );
float OrtalamaBul (int *, int );
void OgrListele (int *, int );


int main()
{
	int *OgrNotDizi,*OgrNotDizi2;
	int i,n,m;
	float ort;
	printf("Ogrenci sayisini veriniz\n");
	scanf("%d",&n);
	
	OgrNotDizi = (int *) calloc( n , sizeof(int) ); 
	/* 
		MALLOC ILE YER AYRILIRSA
		OgrNotDizi = (int *) malloc( n * sizeof(int) ); 
	
	*/
	OgrenciAl (OgrNotDizi,0,n);
    ort=OrtalamaBul (OgrNotDizi, n);
	printf("ortalama:%f\n",ort);
   	OgrListele (OgrNotDizi, n);
   	
	printf("Kac ogrenci eklemek istersiniz");
	scanf("%d",&m);
	OgrNotDizi2=YerGenislet(OgrNotDizi,n,m);
	if (OgrNotDizi2 == NULL)
		printf("yer genisletilemedi\n");
	else
		OgrenciAl (OgrNotDizi2,n,m);
	
	ort=OrtalamaBul (OgrNotDizi2, n+m);
	printf("yeni ortalama:%f\n",ort);
    OgrListele (OgrNotDizi2, n+m);
    free (OgrNotDizi2);
     
	return 0;
}

int *YerGenislet (int *ogrList, int n, int m)
{
	int *ogrListNew;
	ogrListNew = realloc(ogrList, (m+n)*sizeof(int) ); 
	return ogrListNew;
}


void OgrenciAl (int *ogrList, int basla, int sayi)
{
	int i;
	printf("ogrenci notlarini giriniz\n");
	for( i=basla; i < basla+sayi; i++) 
		scanf ( "%d", &ogrList[i] );
	
}
/*
// LOCAL OLARAK YER AYRILMIÞ BÝR DÝZÝYÝ RETURN ÝLE DÖNDÜREMEZSÝN
int* OgrenciALMA (int basla, int sayi)
{
	int i;
	int ogrList[30]
	printf("ogrenci notlarini giriniz\n");
	for( i=basla; i < basla+sayi; i++) 
		scanf ( "%d", &ogrList[i] );
	return ogrList;	//YANLIÞ KULLANIM
}
*/

float OrtalamaBul (int *ogrList, int n)
{
	int i,toplam=0;
	for( i=0; i < n; i++) 
		toplam+=*(ogrList + i);
	
	return (float)toplam/n;
}

void OgrListele (int *ogrList, int n)
{
	int i;
	for( i=0; i < n; i++) 
		printf ( "%d  ", ogrList[i] );
	printf("\n");
}



