#include <stdio.h>
union doub
{
	unsigned char c[2];
	unsigned int val;
};

union u
{
	struct{
	char f1,f2;
	short f3;	
	}s;
	unsigned char f4[6];
	
};

int main()
{
	int j,i;
	char ch;
	union doub d;
	// int ii:4;    böyle bir bit field olmaz
	for (j=0;j<2;j++)
		scanf("%d",&d.c[j]);	//1 2		
								//00000001 00000010
	printf("val1:%d\n",d.val);	//513
	//little endian: least-significant byte at the smallest address
	//Intel CPUs are little-endian, while Motorola 680x0 CPUs are big-endian
								//00000010 00000001
	printf("c1_1:%d c2_1:%d\n",d.c[0],d.c[1]);
	
	d.c[0]=0;
	
	printf("val2:%d\n",d.val);	//512
	printf("c1_2:%d c2_2:%d\n",d.c[0],d.c[1]);//0 2
	printf("ad1:%p ad2:%p\n",&d.c[0],&d.c[1]);
	
	return 0;
}
