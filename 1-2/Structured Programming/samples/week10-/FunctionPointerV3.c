#include <stdio.h>
// Two simple functions
void fun1(int,int);
void fun2(int,int);
int fun3(int);
void (*wrapper(int,int))();


void fun1(int a,int b)
{
	printf("Fun1:%d\n",a-b);  //Quick Sort 
	
}

void fun2(int a,int b)
{ 
	printf("Fun2:%d\n",b-a); //Merge Sort
}

int fun3(int a)
{ 
	return a*a*a;
}

// wrapper() receives two integers and
// returns a function pointer

//void (*wrapper(int a,int b))(int a,int b)  //also legal
void (*wrapper(int a,int b))()
{
	if (a>b)		//the code detecting the optimum sorting algorithm
		return fun1;
	else
		return fun2;
}

// wrapper2() receives two integers as parameters
// and calls fun1() and fun2() functions
void wrapper2(int a,int b)
{
	if (a>b)		//the code detecting the optimum sorting algorithm
		fun1(a,b);
	else
		fun2(a,b);
}

int (*wrapper3(int a))
{
	return fun3;
}

int main()
{
	// 17 and 12 is the parameters for wrapper whereas 10 and 20 are parameters for fun1 or fun2
	wrapper(17,12)(10,20);					//legal
	(*wrapper(17,12))(10,20);				//legal
	wrapper2(10,20);
	int (*fp)();
	fp=wrapper3(4);
	printf("%d",fp(4));
	return 0;
}
