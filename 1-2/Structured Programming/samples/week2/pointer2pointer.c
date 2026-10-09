#include <stdio.h>
int main()
{
	int a=20;
	int *b=&a;
	int **c=&b;
	printf(" %p %d\n %p %d\n %p %d\n",&a,a,&b,*b,&c,**c);
	printf(" %d %p %p",a,b,c);

	return 0;
}
