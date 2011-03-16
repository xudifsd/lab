#include<time.h>
#include<stdio.h>
#include"list.h"

void main() {
    double start,finsih;//统计运行时间
    root *root;
//    struct toparr *i;	//used for print result
    char word[MAX];
    int r;/*test weather getword() return EOF.*/
	start=(double)clock();
    root=ListInit();
    while((r=getword(word))!=EOF){
    	ListInsert(root,word);
    }
    ListPrintall(root); //this is for test useage
    finsih=(double)clock();
    printf("Run time is %.2f ms\n",(finsih-start)/1000);
}
