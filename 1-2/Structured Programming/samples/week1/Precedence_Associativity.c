//All non-zero values are interpreted as TRUE, including negative values. 
//Precedence and Associativity Rules:
#include <stdio.h>
int main()
{
	int  j=0, m=1, n=-1, x1=2;	
	float x=2.5, y=0.0;
	/*
	++ -- !			right to left
	* / %			left to right
	+ -				left to right
	>>  <<			left to right
	< > <= >=		left to right
	&&				left to right
	||				left to right
	= += -= 		right to left
		*/
	printf("1:%d\n",j && m);				//0
	printf("2:%d\n",j < m && n < m );		//T && T
	printf("3:%d\n",++j < m && n < m );		//F && T
	printf("4:%d\n", x1*7%2 && 1 || (m / n));	// (((x1*7)%2) && 1) || (m / n)
											//	(14%2) && 1) || -1
											//	(0	   && 1) ||  T
											//	1
	printf("5:%d\n",!++n && !n && m + n );	//	1	&&  1  &&  1
}
