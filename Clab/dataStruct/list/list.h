#ifndef LEN
	#define LEN sizeof(node)
#endif
#ifndef MAX
	#define MAX 50
#endif

typedef struct node{//set
	char word[MAX];
	unsigned int count;
	struct node *next;
}node;

typedef struct{//root
	unsigned int sum;
	struct node *head;
}root;

