// NESTED STRUCTURES
#include <stdio.h>
#include <stdlib.h>
/*
typedef struct{
 char gun;
 char ay;
 char yil;	
} TARIH;	//typedef ile tanimlandigi icin tarih tipi baska structure lar icinde de kullanilabilir

typedef struct{
 char isim[30];
 int maas; 
 TARIH tarih;
}CALISAN; 
*/

/*
typedef struct {
 char isim[30];
 int maas; 
 struct {
 	char gun;
 	char ay;
 	char yil;
 }tarih;		// sadece bir kez kullanilabilir
  
}CALISAN; 
*/


struct CALISAN{
 char isim[30];
 int maas; 
 struct {
 	char gun;
 	char ay;
 	char yil;
 }tarih;		// sadece bir kez kullanilabilir
}; 

/*
  //ILLEGAL KULLANIM (tarih struct'indan bir deðiþken uretilmeli)
struct CALISAN{
 char isim[30];
 int maas; 
 struct tarih{
 	char gun;
 	char ay;
 	char yil;
 };		
};
*/

int main()
{
	//CALISAN calisan2={"ali",7000,{11,10,90}}; //typedef ile tanimlanmissa
	//CALISAN calisan1;							//typedef ile tanimlanmissa
	struct CALISAN calisan1;
	calisan1.tarih.ay=2;
	calisan1.tarih.gun=12;
	calisan1.tarih.yil=98;
	printf("%d %d %d\n",calisan1.tarih.ay,calisan1.tarih.gun,calisan1.tarih.yil);
	struct CALISAN calisan2={"ali",7000,{11,10,90}}; 
	printf("%s %d %d %d %d\n",calisan2.isim,calisan2.maas,calisan2.tarih.ay,calisan2.tarih.gun,calisan2.tarih.yil);
	return 0;
}

