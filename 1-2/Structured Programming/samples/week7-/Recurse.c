#include <stdio.h>
int main( )
{ 
	Recurse();
	printf("\n");
	Recursev2(1);
	return 0;
} 

void Recurse()
{ 
	static int n=1;
	if (n<=3) 
	{
		printf("%d ",n);
		n++;
		Recurse();
	}
} 


void Recursev2(int n)
{ 
	if (n<=3) 
	{
		printf("%d ",n);
		n++;
		Recursev2(n);
	}
} 


