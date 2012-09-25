#include<stdio.h>
#define DEBUG

void swap(int *num1,int *num2){
	int temp;
	temp=*num1;
	*num1=*num2;
	*num2=temp;
}

int *min(int *num1,int *num2){
	return *num1<*num2 ? num1 : num2;
}

void selectSort(int *arr,int size) {//First select the minest in array,then put it to the first location,and so on;
	int times,*minest,i;
	for (times=0 ; times<size ; times++) {
		minest = arr + times;
		for (i=times ; i<size ; i++)//Find the minest in array,then put it to arr[times]
			minest = min(minest, arr+i);
		swap(minest, arr+times);
	}
}

#ifdef DEBUG
void main(){
	int arr[100]={-100,10,4,2,342,2111,0,-2,31121,3131,1,212,12,313,423,54,8658,4,54,32,-223,424,-535,-555,-33,34,5,3,0,33,5332,-3333333,333333,434,532225,5600,33232,53333,-3323,0,0,22332,3235532,44,45,46,47,48,49,50,4142,3213,21213,12,2424,532,-343,31232,1233214,421245,3232432,1231312,42,0,42,4222,3,-424242424,4222,78900,776,72,73,74,454,64343,2234,113,1244,242,4333553,23432,83,49902,3323,-2324,-42442,-323,89,90,3333,323,44,2,2222,323,97,98,99,100};
	int j;
	selectSort(arr,100);
	for (j=0;j<100;j++)
		printf("%d\n",*(arr+j));
}
#endif
