#ifndef HEAPTREE_H
#define HEAPTREE_H

struct node {
	char *word;
	unsigned int count;
	struct node *left;
	struct node *right;
};

struct root{
	unsigned int sum;
	struct node *head;
};

struct marrow{
	char *word;
	unsigned int count;
};

extern struct root * init_root();
extern struct node * init_node(char *);
extern int traverse(struct node *, void (*)(const struct node *));
extern int height(struct node *);
extern struct node *insert(struct node *, char *);
#endif /*HEAPTREE_H*/
