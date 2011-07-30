#include <stdio.h>
#include <time.h>
#include "splaytree.h"

void main()
{
    double start,finsih;//统计运行时间
    struct root *root;
    struct toparr *i;	//used for print result
    char word[MAX];
    int maxdepth = 0;
	int temp;
	start=(double)clock();
    root=creat();
    while((getword(word))!=EOF) {
		temp = insert(root,word);
		if (temp > maxdepth)
			maxdepth = temp;
	}
    //printall(root->next); //this is for test useage
    gettop10(root->next);	//this function add data in top10 ,top10 is global variable declare in splaytree.c
	sort(top10);
    for(i=top10;i<=top10+9;i++) {
        printf("%s\t",i->word);
        printf("%d\n",i->count);
	}
    printf("There are %d words.\n",root->sum);
    finsih=(double)clock();
    printf("Run time is %.2f ms\n",(finsih-start)/1000);
    printf("Max depth is %d\n", maxdepth);
}
