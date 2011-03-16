#include<stdio.h>
#define DEBUG
//似乎这个函数有点慢啊……可能哪有问题吧

void shellSort(int *arr,int size)
{
int gapsequence[]={1,4,10,23,57,132,301,701,1750},gap;	//此gapsequense是已知最好的
int *first,*edge,*point,temp;
for (gap=8;gapsequence[gap]>=size;gap--)	//选择最大步长
	{}
for (;gapsequence[gap]>=1;gap--)	//步长逐渐减小
	for (first=arr ; first<arr+gapsequence[gap] ; first++)
		for ( edge=point=first ; edge<arr+size  ; point=(edge+=gapsequence[gap]) )	//在edge前面的数可认为已排好序，该for循环即插入排序
			{
				temp=*point;
				for ( ;(point != first) && ((*(point-gapsequence[gap])) > temp); point-=gapsequence[gap] )
						*point=*(point-gapsequence[gap]);	//当前面的数比要移动的数更大，就将前面的数后移
				*point=temp;
			}
}

#ifdef DEBUG
void main()
{
int a[100]={-100,10,4,2,342,2111,0,-2,31121,3131,1,212,12,313,423,54,8658,4,54,32,-223,424,-535,-555,-33,34,5,3,0,33,5332,-3333333,333333,434,532225,5600,33232,53333,-3323,0,0,22332,3235532,44,45,46,47,48,49,50,4142,3213,21213,12,2424,532,-343,31232,1233214,421245,3232432,1231312,42,0,42,4222,3,-424242424,4222,78900,776,72,73,74,454,64343,2234,113,1244,242,4333553,23432,83,49902,3323,-2324,-42442,-323,89,90,3333,323,44,2,2222,323,97,98,99,100};
int i;
shellSort(a,100);
for ( i=0 ; i<100 ;i++ )
		printf("%d\n",a[i]);
}
#endif
