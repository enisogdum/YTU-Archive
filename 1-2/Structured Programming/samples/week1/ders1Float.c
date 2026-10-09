#include <stdio.h>

int main(int argc, char *argv[]){
	float ondalikli = 700.555;	
	printf("     dbl \t%f\n",ondalikli);
	printf("     dbl \t%.3f\n",ondalikli);
	printf(" lng.dbl \t%lf\n",ondalikli);
	printf("     exp \t%e\n",ondalikli);
	if (ondalikli==700.554993)
		printf("oldu");
    system("PAUSE");	
    return 0;
}


