#define MUL_BY_TWO(a) ((a)+(a))
#define FIND_MIN(a,b) ((a)<(b)?(a):(b))
#define FIND_MINOFALL(a,b,c) ((a)<(b)?     ((a)<(c)?(a):(c))   :    ((c)<(b)?(c):(b))     )

#define FIND_MIN_V2(x, y)                                  \
({                                                         \
    if ((x) < (y))                              		   \
        printf("%d\n",x);                                  \
    else                                                   \
        printf("%d\n",y);                                  \
})

#include <stdio.h>
int main()
{
	int y;
	float z;
	y=MUL_BY_TWO(2.4);
	z=MUL_BY_TWO(2.4);
	printf("%d %f\n",y,z);
	printf("FIND_MIN:%d\n",FIND_MIN(3,5));
	printf("FIND_MINOFALL:%d\n",FIND_MINOFALL(1,11,2));
	printf("%d\n", (3>5));
	#define false 1
	#define false 0
	#if !false 
	# define false 1
	#endif
	printf("false:%d\n",false);
	FIND_MIN_V2(2,4);
	int a=1, b=5 ,c;
	c=FIND_MIN(++a,b);
	printf("FIND_MIN:%d\n",c);
}
