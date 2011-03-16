#include<stdio.h>
#include<string.h>
/*该程序用于将已排好序的字符串列进行整合，并在原字符串前输出字符串出现的次数*/
#define MAX 1000
#define DEBUG

int getword(char *space)
{
    char c;
    if ((c=getchar()) == EOF)
        return EOF;
    *space=c;
    space++;
    while (!isspace(c=getchar()) && c!= EOF)
        {
            *space=c;
            space++;
            }
    *space='\0';
    return 1;
    }

#ifdef DEBUG
int main()
{
    char arr1[MAX],arr2[MAX];
    int count=1;
    if (getword(arr1) == EOF)
        return 0;
    while ((getword(arr2)) != EOF)
        {
            if (strcmp(arr1,arr2) == 0)
                count+=1;
            else
                {
                    printf("%d\t%s\n",count,arr1);
                    count=1;
                    strcpy(arr1,arr2);
                    }
            }
    printf("%d\t%s\n",count,arr1);
    }
#endif