#include <stdio.h>
#define CHECK( a, b ) \
if((a)!=(b)) \
fail( a, b, __FILE__, __LINE__)
#define X 2



void fail(int a, int b, char* p, int line)
{
printf( "Check failed in file %s at line %d: received %d, expected %d\n", p, line, a, b );
} 

int main()
{
	CHECK(3,4);
	
	#if X==1 
	printfvv("use printfvv");
	#elif X==2 
	printf("use printf");
	#endif
	
	
		
	#ifdef X
	printf("\nX is defined");
	#else
	printf("\nX is not defined");
	#endif
	
	return 0;
}

