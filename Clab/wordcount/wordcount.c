#include<stdio.h>
#include<time.h>
#include"getword.c"
#include"splaytree.c"

void main()
{
    double start,finsih;//统计运行时间
    struct root *root;
    struct toparr *i;	//used for print result
    char word[MAX];
    int r;/*test weather getword() return EOF.*/
    int memoryenough=1; /*if memoryenough==0,memory is not enough.*/
	start=(double)clock();
    root=creat();
    while((r=getword(word))!=EOF)
    {
		memoryenough=insert(root,word);
        if (memoryenough==0)
            break;
        }
    //printall(root->next); //this is for test useage
    gettop10(root->next);	//this function add data in top10 ,top10 is global variable declare in splaytree.c
	sort(top10);
    for(i=top10;i<=top10+9;i++)
    {
        printf("%s\t",i->word);
        printf("%d\n",i->count);
        }
    printf("There are %d words.\n",root->sum);
    finsih=(double)clock();
    printf("Run time is %.2f ms\n",(finsih-start)/1000);
        if (memoryenough==0)
            printf("The memory is not enough,wordcounter is not complete!\n");
}
