// this program counts the spaces within a given phrase
// the program keeps getting characters from the user until the enter key is pressed
// WITHOUT USING IF OR SWITCH STATEMENT
#include <stdio.h>
int main()
{
	char ch;
	int numofSpace=0;
	int charCounts[128]={};
	// DO - WHILE VERSION
	do
	{
		scanf("%c",&ch);	//ch=getchar(); is useful too
		charCounts[ch]++;
			
	}while (ch!='\n');		// '\n' is new line character
	printf("Number of spaces (do-while):%d\n",charCounts[' ']);
	
	return 0;
}
