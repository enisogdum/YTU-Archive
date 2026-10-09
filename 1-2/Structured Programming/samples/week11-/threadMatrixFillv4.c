#include <pthread.h>
#include <stdio.h>
#define N 10
#define M 10
int A [N][M];
int step=0;
void *runner()
{
   int m;
   int core=step++;
   for(m = 0; m< M; m++)
      A[core][m]=m+1;
   pthread_exit(0);
}
int main()
{
	int i=0,j;
	pthread_t tid[N]; 
	//void (*functionPtr)();
    //functionPtr=runner;
	for(i = 0; i < N; i++) {
         /* Now create the thread passing it data as a parameter */
         pthread_attr_t attr; //Set of thread attributes
         //Get the default attributes
         pthread_attr_init(&attr);
         //Create the thread
         //pthread_create(&tid,&attr,(void *)&runner,NULL); // or
         //pthread_create(&tid,&attr,functionPtr,NULL);
         pthread_create(&tid[i],&attr,runner,NULL);
    }
	//Make sure the parent waits for current thread to complete
   for(i = 0; i < N; i++) 
    	pthread_join(tid[i], NULL);
   //Print out the resulting matrix
   for(i = 0; i < N; i++) {
      for(j = 0; j < M; j++) 
         printf("%d ", A[i][j]);
      printf("\n");
   }
}

