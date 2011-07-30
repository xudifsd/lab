#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#define MAX 30
#define LEN sizeof(struct node)
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

struct toparr
{
    char word[MAX];
    int count;
}top10[10];	//top10作为全局变量

extern struct root *creat();
extern int insert(struct root *,char *);
extern void printall(struct node *);
extern void gettop10(struct node *);
extern void sort(struct toparr *);
#endif /*SPLAYTREE_H*/
