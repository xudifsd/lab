#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define MAX 30
#define LEN sizeof(struct node)

struct toparr
{
    char word[MAX];
    int count;
    }top10[10];	//top10作为全局变量

struct toparr *min=top10;//递归调用的gettop10的每一次调用负责将min指向正确位置。
int i=1;

struct root
{
struct node *next;
int sum;
};

struct node
{
char word[MAX];
int count;
struct node *left;
struct node *right;
};

struct root *creat()
{
struct root *p;
p=(struct root *)malloc(sizeof(struct root));
p->next=NULL;
p->sum=0;
return p;
}

int insert(struct root *head,char *word)/*if memory is not enough return 0*/
{
    if (head->next == NULL)
    {
        head->next=(struct node *)malloc(LEN);
        strcpy(head->next->word,word);
        head->next->count=1;
        head->next->left=NULL;
        head->next->right=NULL;
        head->sum=1;
        return 1;
        }
    else
    {
        struct node *p;
        p=head->next;//make p point to the first node of tree.
        while(1)
        {
            if (strcmp(p->word,word)==0)
            {
             p->count+=1;
             head->sum+=1;
             return 1;   
                }
            else if (strcmp(p->word,word)>0)
            {
             if (p->left==NULL)
             {
              p->left=(struct node *)malloc(LEN);
			  if (p->left==NULL)//memory is not enough.
				  return 0;
			  p=p->left;
              strcpy(p->word,word);
              p->count=1;
              p->left=NULL;
              p->right=NULL;
              head->sum+=1;
              return 1;
                 }
              else{
                  p=p->left;
                  continue;
                  }
                }
            else if (strcmp(p->word,word)<0)
            {
             if (p->right==NULL)
             {
              p->right=(struct node *)malloc(LEN);
			  if (p->right==NULL)
				  return 0;
			  p=p->right;
              strcpy(p->word,word);
              p->count=1;
              p->left=NULL;
              p->right=NULL;
              head->sum+=1;
              return 1;
                 }
              else{
                  p=p->right;
                  continue;
                  }
                }
                }
            }
    }
void printall(struct node *p)	//for test useage
{
    if(p->left != NULL)
        printall(p->left);
    printf("%s\t",p->word);
    printf("%d\n",p->count);
    if (p->right != NULL)
        printall(p->right);
    }
    
struct toparr *min_of_top10()//只被gettop10调用
{
    struct toparr *p,*min=top10;
    for(p=top10+1;p<=top10+9;p++)
        {
            if (min->count > p->count)
                min=p;
            }
    return min;
    }

void gettop10(struct node *p)//并不打印，只是将值赋给全局变量top10[10]
{
    if (p->left != NULL)
        gettop10(p->left);
    if (i <= 10)//先填入10组数
        {
            strcpy(min->word,p->word);
            min->count=p->count;
            i++;
            min++;
            if (i == 11)
                min=min_of_top10();
            }
    else
        {
            if(min->count < p->count)
                {
                    strcpy(min->word,p->word);
                    min->count=p->count;
                    min=min_of_top10();
                    }
            }
    if (p->right != NULL)
        gettop10(p->right);
    }

void swaptop10(struct toparr *p1,struct toparr *p2)	//only called by sort function
{
struct toparr temp;
strcpy(temp.word,p1->word);
strcpy(p1->word,p2->word);
strcpy(p2->word,temp.word);

temp.count=p1->count;
p1->count=p2->count;
p2->count=temp.count;
}

void sort(struct toparr *top10)	//based on bubble sort
{
int times;
struct toparr *pointer;
for (times=0;times<10;times++)
	for (pointer=top10;pointer<top10+9;pointer++)
		if (pointer->count<(pointer+1)->count)
			swaptop10(pointer,pointer+1);
}
