#include <stdio.h>
////////////////////////////////
//forward referencing
struct s1{
 	int a;
  	struct s2 *ps2;
}; 

struct s2{
 	int b;
  	struct s1 *ps1;
}; 
////////////////////////////////

struct s
{
	int a,b;
	float c;
	struct s* pointer_to_S;
};

// typedef ile forward referencing yapilamaz
/*
typedef struct;
{
	int a,b;
	float c;
	Sr* pointer_to_Sr;
}Sr;
*/
///////////////////////////////
/*
struct s
{
	int a,b;
	float c;
	struct s* pointer_to_S;
};
*/
int main()
{
	struct s S1={1,2,1.2,NULL};
	struct s S2={3,4,5.6,NULL};
	
	S1.pointer_to_S=&S2;
	S2.pointer_to_S=&S1;
	
	
	printf("%d-%d\n",(S1.pointer_to_S)->a,(S1.pointer_to_S)->b); //3 4
	printf("%d-%d\n",(S2.pointer_to_S)->a,(S2.pointer_to_S)->b); //1 2 
	//	printf("%d-%d\n",(*(S2.pointer_to_S)).a,(S2.pointer_to_S)->b);
	
	struct s z,t;
	
	z.pointer_to_S=&t;
		
	return 0;
}

