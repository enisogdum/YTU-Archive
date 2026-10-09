#include <stdio.h>
#include <string.h>
int main(){
	char metin[30]="ince memed. yasar Kemal";
	char *str="beyaz gemi Cengiz Aytmatov";
	char *pChar=metin;
	int i=0;
	int u=0;
	int v=strlen(metin);
	while(metin[i]!='\0'){
		//u++; unnecassary
		i++;
	}
	while(*pChar!='\0'){
		pChar++;
		u++;
	}
	
	printf("%d %d %d",i,u,v);
	
	for(pChar=metin;*pChar!='\0';pChar++){
		if(*pChar=='.'){
			pChar+=2;
			*pChar-='a'-'A';
		}
		
	}
	printf("\n%s\n",metin);
	for(i=0;i<strlen(str);i++){

			printf("%c",str[i]);

	}
	for(pChar=&str[0];*pChar!='\0';pChar++){

			printf("%c",*pChar);

	}
	printf("\n%s",str);
}
