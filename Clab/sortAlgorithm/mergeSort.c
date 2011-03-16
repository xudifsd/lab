#include<stdio.h>
#define DEBUG 1

void mergeSort(int *arr1,int *arr2,int *space)	//arr1 and arr2 must ended with '\0',the result is also ended with '\0'
{
while ( ((*arr1) != '\0') && ((*arr2) != '\0'))
	{
	if ( (*arr1) < (*arr2) )
		{
		*space=*arr1;
		arr1++;space++;
		}
	else
		{
		*space=*arr2;
		arr2++;space++;
		}
	}
if ( (*arr1) == '\0' )
	{
	while ( (*arr2) != '\0' )
		{
		*space=*arr2;
		arr2++;space++;
		}
	}
else
	{
	while ( (*arr1) != '\0' )
		{
		*space=*arr1;
		arr1++;space++;
		}
	}
*space='\0';
}

#ifdef DEBUG
void main(void)
{
int a1[]={1,4,6,8,9,33,43,533,3223,'\0'};
int a2[]={2,3,4,5,6,33,343,455,3322,'\0'};
int result[20]={0};
int i;
mergeSort(a1,a2,result);
for (i=0;result[i] != '\0';i++)
		printf("%d\n",result[i]);
}
#endif
