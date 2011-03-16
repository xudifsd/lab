#include<stdio.h>
#include<string.h>
/*该程序用于将连续文本分开成单词格式，输出时每个单词占一行*/
#define MAX 1000
#define DEBUG

int getword(char *space)
{
    char c;
    while (!isdigit( c=getchar() ) && !isalpha(c) && c!=EOF )//skip space
    {}
    if (c == EOF)
        return EOF;
    *space=c;
    space++;
    while ( ( isdigit(c=getchar()) ||isalpha(c) ) && c!= EOF)
        {
            *space=c;
            space++;
            }
    *space='\0';
    return 1;
    }

#ifdef DEBUG
void main()
{
    char arr[MAX];
    while ((getword(arr)) != EOF)
        printf("%s\n",arr);
    }
#endif