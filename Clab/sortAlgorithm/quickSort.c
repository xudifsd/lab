#include<stdio.h>
#define DEBUG

void swap(int *p1,int *p2)
{
int temp;
temp=*p1;
*p1=*p2;
*p2=temp;
}

int quickSort(int *arr, int size)
{
int *pivot=arr+size-1;
int *start=arr,*end=arr+size-2;
if (size<2)
	return 0;
while (start<end)
	{
	if ( *start<*pivot)
			start++;
	else
		{
			swap(start,end);
			end--;
		}
	}
	if (*start<=*pivot)	//一定要有=否则在对两个相等数排序会死循环
		{
		start++;
		swap(start,pivot);

		quickSort(arr,start-arr);
		quickSort(start,size-(start-arr));
		}
	else
		{
		swap(start,pivot);

		quickSort(arr,start-arr);
		quickSort(start,size-(start-arr));
		}
return 1;
}

#ifdef DEBUG
void main()
{
int i;
int a[100]={-100,10,4,2,342,2111,0,-2,31121,3131,1,212,12,313,423,54,8658,4,54,32,-223,424,-535,-555,-33,34,5,3,0,33,5332,-3333333,333333,434,532225,5600,33232,53333,-3323,0,0,22332,3235532,44,45,46,47,48,49,50,4142,3213,21213,12,2424,532,-343,31232,1233214,421245,3232432,1231312,42,0,42,4222,3,-424242424,4222,78900,776,72,73,74,454,64343,2234,113,1244,242,4333553,23432,83,49902,3323,-2324,-42442,-323,89,90,3333,323,44,2,2222,323,97,98,99,100};
quickSort(a,100);
for (i=0;i<100;i++)
		printf("%d\n",a[i]);
}
#endif
