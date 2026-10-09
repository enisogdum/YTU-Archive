#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define M 3
#define K 2
#define N 3
int A [M][K] = { {1,4}, {2,5}, {3,6} };
int B [K][N] = { {8,7,6}, {5,4,3} };
int C [M][N];
struct v {
   int i; /* row */
   int j; /* column */
};
pthread_t tid[M*N];
void *threadedMult(void *param); /* the thread */
int main() {
   int i,j, count = 0;
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         struct v *data = (struct v *) malloc(sizeof(struct v));
         data->i = i;
         data->j = j;
         pthread_create(&tid[count],NULL,threadedMult,(void*)data);
         count++;
      }
   }
   for(i = 0; i < M*N; i++) 
   		pthread_join(tid[i], NULL); 
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         printf("%d ", C[i][j]);
      }
      printf("\n");
   }
}
void *threadedMult(void *param) {
   struct v *data = (struct v *)param; // the structure that holds our data
   int n, sum = 0; //the counter and sum
   for(n = 0; n< K; n++){
      sum += A[data->i][n] * B[n][data->j];
   }
   C[data->i][data->j] = sum;
   pthread_exit(0);
}
void sequentialMult()
{
	int sum=0;
	int i,j,k;
	for (i = 0; i < M; i++) {
      for (j = 0; j < N; j++) {
        for (k = 0; k < K; k++) {
          sum = sum + A[i][k]*B[k][j];
        }
        C[i][j] = sum;
        sum = 0;
      }
    }
}
