#include <string.h>
#include <stdio.h>
int main()
{
char array[10]="hello";  //initialization
char *ptr="world";		 //string literal
char str[]="imagine";	 //initialization

char *p="a";			//two bytes allocated
char ch='a';			//one byte allocated

//array = "not OK"; 	//not OK. assignment to expression with array type
//array='d';			//not OK. assignment to expression with array type
array[3] = 'A';
printf("%s\n",array); 	//helAo
ptr="hi";				//not uniformly supported
//ptr[1] = 'B';     	//syntax hatasý vermez runtime hatasý alabilirsin
printf("%s\n",ptr);		//hi

char *ptr2;
// *ptr2 = "not OK";	//type mismatch
ptr2="prime";			//not uniformly supported
printf("%s\n",ptr2);  	//prime

//*array="c";  			//illegal
*array='c'; 			 
*(array+1)='m';  		//parantez konmazsa *'in onceligi oldugu için syntax hatasý verir
printf("%s\n",array);   //cmlAo

//         0 1 2 3 4 5 6 
// str  -> i m a g i n e
char *i=str+2;
printf("%c\n",*i); 		//a
printf("%s\n",i); 		//agine

/*
//	ptr2 bu sekilde tanimlandigi için string literaldir ve memory'de read only bir þekilde tutulur
//	String literallarda degisiklik yapilmasý c de tanýmlý deðildir
//	bu yüzden aþaðýdaki gibi bir karakter degiþikliði yapilamaz
//	ptr2[0]='c';   //segmentation fault verir
//	aþaðidaki tanýmlanýrsa deðiþtirilebilir
*/
char ptr3[]="prime"; 
ptr3[0]='c';
printf("%s\n",ptr3);

}
