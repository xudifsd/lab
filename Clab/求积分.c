#include<stdio.h>
#include<math.h>
#define DEBUG

double integral(double low,double up,double (*function)(double))
{
    double i,sum=0;
    for (i=low;i<up;i+=0.0001)
        {
            sum+=function(i)*0.0001;
            }
    return sum;
    }

#ifdef DEBUG
void main()
{
    double (*p)(double);
    double sum;
    p=sin;
    sum=integral(0,1,p);
    p=cos;
    sum+=integral(0,1,p);
    p=exp;
    sum+=integral(0,1,p);
    printf("%.3f\n",sum);
    }
#endif