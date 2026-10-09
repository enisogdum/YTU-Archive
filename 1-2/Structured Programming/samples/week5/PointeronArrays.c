#include <stdio.h>
void printArray(double [], int);
void printArrayv2(double *arr, int);
void foov2(double [], int);
void foo(double *, int);
void foov3(double *, int);
int main(){
	double d[5]={1,2,3,4,5}, *dp;
	int i;
	printf("%p %p %p\n",d,&d,&d[0]); //000000000062FE20 000000000062FE20 000000000062FE20
	dp = d; // dp= &d[0]
	*(dp+3) = 50;
	printf("%d\n",sizeof(double)); //8
	printf("%p %lf %lf\n",dp+3, *dp+3, *(dp+3)); //000000000062FE38 4.000000 50.000000
	printArray(d,5); //1.000000 2.000000 3.000000 50.000000 5.000000
	printArrayv2(d,5);//1.000000 2.000000 3.000000 50.000000 5.000000
	foo(d,5);
	printArrayv2(d,5);//7.000000 7.000000 7.000000 7.000000 7.000000
	foov2(d,5);
	printArrayv2(d,5);//2.000000 2.000000 2.000000 2.000000 2.000000
	foov3(d,5);
	printArrayv2(d,5);//9.000000 9.000000 9.000000 7.000000 9.000000
	/*for(i = 0;i<5;i++){ // illegal
		d++;
	}*/
	return 0;
}

void printArray(double arr[], int n){
	int i;
	for(i=0;i<n;++i){
		printf("%lf ",arr[i]);
	}
	printf("\n");
}

void printArrayv2(double *arr, int n){
	int i;
	for(i=0;i<n;++i){
		//printf("%lf ",*(arr+i));
		printf("%lf ",arr[i]);
	}
	printf("\n");
}

void foo(double *arr, int n){ //arr: call by ref/pointer
	int i;
	for(i=0;i<n;++i){
		*(arr+i) = 7;
	}

}

void foov2(double arr[], int n){ // arr: call by ref/pointer
	int i;
	for(i=0;i<n;++i){
		arr[i] = 2;
	}

}

void foov3(double *arr, int n){ // arr: call by ref/pointer
	int i;
	double *p = arr;
	for(i=0;i<n;++i){
		*arr = 9;
		arr++;
	}
	*(p+3) = 7;
	*(arr+3) = 7;
}
