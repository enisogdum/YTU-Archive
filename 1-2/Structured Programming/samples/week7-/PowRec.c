#include <stdio.h>  
/* n = O(n) */
int powRv1(int x,int y)
{
	if (y==0)
		return 1;
	else
		return x*powRv1(x,y-1);		
}
/* logn+2 = O(logn)*/
int powRv2(int x, unsigned int y)
{
    int temp;
    if( y == 0)
        return 1;
    temp = powRv2(x, y/2);
    
    if (y%2 == 0)
        return temp*temp;
    else
        return x*temp*temp;
}
/*
P(x,0) -> 1
P(x,1) -> P(x,0) ->x*1*1=x
P(x,2) -> P(x,1) ->x*x = x^2
P(x,5) -> P(x,2) ->x*x^2*x^2 =x^5
*/
/* 2n-1 = O(n) */
/* if you not use temp variable, the complexity will be O(n)*/
int powRv3(int x, unsigned int y)
{
    int temp;
    if( y == 0)
        return 1;
    if (y%2 == 0)
        return powRv2(x, y/2)*powRv2(x, y/2);
    else
        return x*powRv2(x, y/2)*powRv2(x, y/2);
}
int main()
{
	int x=2,y=7;
	printf("%d\n",powRv1(x,y));
	printf("%d\n",powRv2(x,y));
	printf("%d\n",powRv3(x,y));
}

