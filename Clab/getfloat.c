#include<stdio.h>

float getfloat()
{
float result=0,deep=0.1;
char c;
int sign=1;	//sign represent whether number is positive or negative.
while (!isdigit(c=getchar()))
	{
	if (c==EOF)
		return EOF;
	sign=1;/*if '-'is not followed by digit.*/
	if (c == '-')
		sign=-1;
	}
result=result*10+(c-'0');
while (1)
	{
	c=getchar();
	if (c=='.')
		{
		while (isdigit(c=getchar()))
			{
			result=result+(c-'0')*deep;
			deep*=0.1;
			}
		return result*sign;
		}
	else if (isdigit(c))
		result=result*10+(c-'0');
	else
		return result*sign;
	}
}

void main()
{
float a;
while ((a=getfloat()) != EOF)
	printf("Float is %.5f\n",a);
}


