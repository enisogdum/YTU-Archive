# include <stdio.h>
int addInt(int, int);
int main()
{
    int (*functionPtr)(); 	//int (*functionPtr)(int,int); il also legal
    						/* functionPtr is a pointer to a function returning an int */ 

	int sum;
	
	functionPtr = addInt;
	//sum = functionPtr(12, 3); 
	sum = (*functionPtr)(12, 3); 
	printf("sum:%d\n",sum);
}

int addInt(int n, int m) {
    return n+m;
}

