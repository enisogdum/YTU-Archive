#include <stdio.h>


int main()
{
register int i;
	printf("Current line :%d\nFilename : %s\n\n", __LINE__, __FILE__); //Filename: line_example.c
	#line 13
	printf("Current line :%d\nFilename : %s\n\n", __LINE__, __FILE__); // Filename: line_example.c
	#line 6 "new name"
	printf("Current line :%d\nFilename : %s\n\n", __LINE__, __FILE__); //Filename: new name
	
	return 0;
}

