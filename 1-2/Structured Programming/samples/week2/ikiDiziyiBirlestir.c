#include <stdio.h>
int main()
{
	int dizi1[10],dizi2[10];
	int merged[20],*p;
	int n,m,i,j,k;
	scanf ("%d %d",&n,&m);
	for (i=0;i<n;i++)
		scanf("%d",&dizi1[i]);
		
	for (i=0;i<m;i++)
		scanf("%d",&dizi2[i]);
	i=j=k=0;	
		
	// Merge the two arrays
    while (i < n && j < m) {
        if (dizi1[i] < dizi2[j]) {
            merged[k++] = dizi1[i++];
        } else {
            //merged[k++] = dizi2[j++];
            merged[k++] = *(dizi2+j++); //*dizi2+j++ ??
           
        }
    }
    
    // Copy any remaining elements from arr1
    while (i < n) {
        merged[k++] = dizi1[i++];
    }
    
    // Copy any remaining elements from arr2
    while (j < m) {
        merged[k++] = dizi2[j++];
    }	
		
	p=merged; 
	for (i=0;i<k;i++)
	{
		//printf("\n%d ",merged[i]);
		printf("\n%d ",*p);
		p++;
	}
	return 0;	
}
