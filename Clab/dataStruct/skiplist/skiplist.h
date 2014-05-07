#ifndef SKIPLIST_H
#define SKIPLIST_H

#define MAX_LEVEL 6

struct skiplist_node {
    int value; //header use this field to store current level
    int size; //this inited by alloc_node
    struct skiplist_node *forward[0];
};

extern struct skiplist_node *new_skiplist(void);
extern void skiplist_insert(struct skiplist_node *header, int value);
extern int skiplist_contains(struct skiplist_node *header, int value);

#endif /* SKIPLIST_H */
