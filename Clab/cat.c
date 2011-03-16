#include<stdio.h>
/*该程序用于将参数中的文件打开并输出其内容*/
void main(int argc,char *argv[])
{
    FILE *fp;
    char c;
    int i=1;
    while (argc>1)
        {
        fp=fopen(*(argv+i),"r");
        while((c=fgetc(fp)) !=EOF )
            putchar(c);
        fclose(fp);
        argc--;i++;
		puts("\n");
            }
    }