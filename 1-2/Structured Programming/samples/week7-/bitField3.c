// BIT FIELDS
// store gender, age and name of people using bitfiels
// allocate space for n people ,get information from user 
// write a function that returns the name and age of oldest woman

#include <stdio.h>
#include <stdlib.h>
typedef struct 
{
	unsigned int gender:1;	//0-1
	unsigned int age:7;		//0-127 :)
	char name[30];
}PERSON;
char* findOldestWoman(PERSON*, int, int*);
int main()
{
	int gender_t,age_t,i,n,maxAge=0;
	PERSON *personArray;
	printf("give the number of the people\n");
	scanf("%d",&n);
	personArray=(PERSON *)calloc(n, sizeof(PERSON));
	for (i=0;i<n;i++)
	{
		printf("give gender (0-male, 1-female), age and name\n");
		scanf("%d %d %s",&gender_t,&age_t,personArray[i].name);
		personArray[i].gender=gender_t;
		personArray[i].age=age_t;
	}
	printf("name:%s \n", findOldestWoman(personArray,n,&maxAge));
	printf("age:%d \n",maxAge);

	return 0;
}

char* findOldestWoman(PERSON *array, int n, int* max)
{
	int i,loc;
	for (i=0;i<n;i++)
	{
		if ((array[i].gender==1) && (array[i].age>*max))
		{
			*max=array[i].age;
			loc=i;
		}
	}
	return array[loc].name;
}
