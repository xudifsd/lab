#include<stdio.h>
#include<string.h>
#define MAX 1000
/*该程序最重要的函数是arr2i函数！*/
/*该程序接收数字参数用于控制输出的行数*/
int getlines(char *space)/*在linux里已有getline所以用getlines这名字*/
{
    char c;
    if ((c=getchar()) == EOF)
        return EOF;
    *space=c;
    space++;
    while ((c=getchar()) !='\n' && c!= EOF)
        {
            *space=c;
            space++;
            }
    *space='\0';
    return 1;
    }

int arr2i(char *arr)
{
int sum=0;
for (;*arr!='\0';arr++)
	{
	sum=sum*10+((*arr)-48);
	}
return sum;
}

void main(int argc,char *argv[])
{
    char string[MAX];
    int lineCount=atoi(argv[1]);
    while ( (getlines(string)) != EOF && lineCount>0)
        {
            printf("%s\n",string);
            lineCount--;
            }
    }
