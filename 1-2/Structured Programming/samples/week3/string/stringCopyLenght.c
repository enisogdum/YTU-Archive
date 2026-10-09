void myStrcpyV3(char*,char*);
#include <stdio.h>
int main()
{
	char str1[20] = "anne"; 
	char str2[10];
	int i,n;
	// string uzunlugu bulma
	i=0;
	while (str1[i])	//	while (str1[i]!='\0')
			i++;
	n=i++;
	printf("string uzunlugu %d\n",n);

	// bir string'i digerine kopyalama
	for (i=0;str1[i];i++)
		str2[i]=str1[i];
	str2[i]='\0';
	printf("kopyalanan string:%s\n",str2);
	
	// bir string'i digerine kopyalama v2
	for (i=0;*(str1+i);i++)
		*(str2+i)=*(str1+i);
	*(str2+i)='\0'; //str2[i]='\0';
	printf("kopyalanan string:%s\n",str2);
	
	// bir string'i digerine kopyalama v3
	char str3[10];
	myStrcpyV3(str1,str3);
	printf("kopyalanan string:%s\n",str3);
	
	return 0;
}

void myStrcpyV3(char *str1,char *str2)
{
	//An assignment expression has the value of the left operand after the assignment
	// * ++ right to left
	//	=
	while(*str2++=*str1++); //anne
	//while(*++str2=*++str1);	//?
}

/*
strcpy()
strncpy() //Copies the first num characters of source to destination.
strcat()  //Appends a copy of the source string to the destination string
strncat() //Appends the first num characters of source to destination
strcmp()  
strncmp()
strchr()  //Locate first occurrence of character in strin
strcspn()
strpbrk()
strrchr()
strspn()
strstr()
strtok()
strerror() //A pointer to the error string describing error errnum.
strlen()
*/
