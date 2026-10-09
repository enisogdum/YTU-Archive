#include <stdio.h>
#include <string.h>
#define MAX_WORDS 50 
#define LAST_LANG 2 
											 
int main()
{
	char *dict[LAST_LANG] [MAX_WORDS] = {{ "abhor", "able", "abort", "about", NULL } , 
										 { "absurde" , "accepter", "accord", "achat" , NULL } }; 

	char **z; 
	char str[10];
	int diff=-1,language,j=0;
	printf("which language 0-1 for E-F");
	scanf("%d",&language);	
	printf("type the word");
	scanf("%s",str);
	z=&(dict[language][0]); 
	
	while ((*z) && (diff < 0)) 
	{
		diff = strcmp(*z,str);   //ilk kelime buyukse 1,eþitlerse 0, ikinci kelime buyukse -1
		z++;
	}
	
	if (diff==0)
		printf("match\n");
	else
	{
		z--;	
		printf("best match:%s\n",*z);
	}
	




//	DENEYIN BAKALIM
/*	z=&(dict[language][0]); 
	printf("%c\n",**z);
	printf("%s\n",*(z+1));
	printf("%c\n",*(*(z+1)+1));
*/	
}
