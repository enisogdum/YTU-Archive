#include <stdio.h>
#define MAXROW 10
#define MAXCOLUMN 10
void fillMatrix(char text[][MAXCOLUMN], int M, int N);
void search(char text[][MAXCOLUMN], int M, int N, char pattern[]);
int main(){
	char text[MAXROW][MAXCOLUMN];
	char pattern[MAXCOLUMN];
	
	int M, N;
	printf("Enter row value");
	scanf("%d",&M);
	printf("Enter column value");
	scanf("%d",&N);
	fillMatrix(text,M,N);
	
	printf("Enter pattern");
	scanf("%s",pattern);
	
	
	search(text, M, N, pattern);
	
}

void search(char text[][MAXCOLUMN], int M, int N, char pattern[]){
	int len=0;
	int r, i ,j;
	int c=0;
	int bound; 
	while(pattern[len]!='\0'){len++;}
	printf("Pattern length:%d",len);
	bound = N - len;
	for(r=0;r<M;r++){
		for(i=0;i<=bound;i++){
			j=0;
			while(j<len && text[r][i+j]==pattern[j]){
				j++;
			}
			if(j==len){
				c++;
				printf("Patter starts at %dth row and %dth col\n",r,i);
			}	
		}	
	}
	if(c==0){
		printf("not found!");
	}
	
}

void fillMatrix(char text[][MAXCOLUMN], int M, int N){
	int i,j;
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			text[i][j] = (char)(rand()%3 + 'A');
			printf("%2c",text[i][j]);
		}
		printf("\n");
	}
}




