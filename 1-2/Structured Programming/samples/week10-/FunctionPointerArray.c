# include <stdio.h>
# include <stdlib.h>
// int (*)() refers to a pointer to a function that returns an int
// int (*)[10] refers to a pointer to an array of 10 integers.
int main()
{
	int sum,sub;
	int addInt(int, int);
	int subInt(int, int);
    /*int (**foo_ptr_array)();
    foo_ptr_array = calloc( 2, sizeof( int (*)() ) );*/
	
	/* or */
	int (**foo_ptr_array)() = (int (**)())calloc( 2, sizeof( int (*)() ) );
	
	/* or */
	// int (*foo_ptr_array[2])();  
	
	foo_ptr_array[0] = addInt;
	foo_ptr_array[1] = subInt;
	sum=(*foo_ptr_array[0])( 1,2 );
	sub=foo_ptr_array[1]( 1,2 );
	
	printf("sum:%d sub:%d\n",sum,sub);
}

int addInt(int n, int m) {
    return n+m;
}

int subInt(int n, int m) {
    return n-m;
}


