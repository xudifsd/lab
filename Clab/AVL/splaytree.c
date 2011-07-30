#include <string.h>
#include <malloc.h>
#include "splaytree.h"

struct root * init_root(){
	struct root *rtn = malloc(sizeof(struct root));
	memset(rtn, 0, sizeof(struct root));
	return rtn;
}

struct node * init_node(char *word){
	struct node *rtn = malloc(sizeof(struct node));
	memset(rtn, 0, sizeof(struct node));
	rtn->word = strdup(word);
	rtn->count = 1;
	rtn->depth = 1;
	return rtn;
}

static inline int max(int a, int b){
	return a > b ? a : b;
}
int traverse(struct node *cur, void (*fun)(const char *, const int)){	/*traverse reutrn the depth of cur*/
	if (cur == NULL)
		return 0;
	int l,r;
	l = traverse(cur->left, fun);
	if (fun)
		fun(cur->word, cur->count);
	r = traverse(cur->right, fun);
	return max(l, r) + 1;
}

int depth(struct node *cur){
	if (cur == NULL)
		return 0;
	else
		return cur->depth;
}

static struct node * SingleRotateWithLeft(struct node *k2){
	struct node *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->depth = max(depth(k2->left), depth(k2->right)) + 1;
	k1->depth = max(depth(k1->left), k2->depth) + 1;
	return k1;
}

static struct node * SingleRotateWithRight(struct node *k2){
	struct node *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->depth = max(depth(k2->left), depth(k2->right)) + 1;
	k1->depth = max(depth(k1->right), k2->depth) + 1;
	return k1;
}

static struct node *DoubleRotateWithLeft(struct node *k3){
	k3->left = SingleRotateWithRight(k3->left);
	return SingleRotateWithLeft(k3);
}

static struct node *DoubleRotateWithRight(struct node *k3){
	k3->right = SingleRotateWithLeft(k3->right);
	return SingleRotateWithRight(k3);
}

struct node *insert(struct node *cur, char *word){
	/*this tree is AVL tree*/
	if (cur == NULL){
		return init_node(word);
	}
	int r = strcmp(cur->word, word);
	if (r == 0){
		cur->count++;
		return cur;
	} else if(r > 0){
		cur->left = insert(cur->left, word);
		if (depth(cur->left) - depth(cur->right) == 2){
			if(strcmp(word, cur->left->word) < 0){
				cur = SingleRotateWithLeft(cur);
				return cur;
			} else{
				cur = DoubleRotateWithLeft(cur);
				return cur;
			}
		}
	} else{
		cur->right = insert(cur->right, word);
		if (depth(cur->right) - depth(cur->left) == 2){
			if(strcmp(word, cur->right->word) > 0){
				cur = SingleRotateWithRight(cur);
				return cur;
			} else{
				cur = DoubleRotateWithRight(cur);
				return cur;
			}
		}
	}
	cur->depth = max(depth(cur->left), depth(cur->right)) + 1;
	return cur;
}
