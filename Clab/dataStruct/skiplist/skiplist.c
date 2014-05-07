#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "skiplist.h"

static struct skiplist_node * alloc_node(int s) {
    int size = sizeof(struct skiplist_node) + s * sizeof(void *);
    struct skiplist_node *result = malloc(size);
    memset(result, 0, size);
    result->size = s;
    return result;
}

static int random_level() {
    static int inited;
    if (!inited) {
        srand(time(NULL));
        inited = 1;
    }

    int result = 0;
    int r;

    do {
        r = rand() % 1;
        if (!r)
            break;
        result++;
    } while (result < MAX_LEVEL);

    return result;
}

struct skiplist_node *new_skiplist() {
    return alloc_node(MAX_LEVEL);
}

void skiplist_insert(struct skiplist_node *header, int value) {
    static struct skiplist_node *should_update[MAX_LEVEL];

    if (header == NULL)
        return;

    struct skiplist_node *p = header;
    int level = header->value; //header use this field to store current level
    int i;

    for (i = level; i >= 0; i--) {
        while (p->forward[i] && p->forward[i]->value < value)
            p = p->forward[i];
        should_update[i] = p;
    }
    p = p->forward[0];

    if (p == NULL || p->value != value) {
        int l = random_level();

        if (l > level) {
            for (i = level + 1; i < l + 1; i++)
                should_update[i] = header;
            level = header->value = l;
        }

        struct skiplist_node *new_node = alloc_node(l + 1);
        new_node->value = value;

        for (i = 0; i < l + 1; i++) {
            new_node->forward[i] = should_update[i]->forward[i];
            should_update[i]->forward[i] = new_node;
        }
    }
}

void skiplist_delete(struct skiplist_node *header, int value) {
    static struct skiplist_node *should_update[MAX_LEVEL];

    if (header == NULL)
        return;

    struct skiplist_node *p = header;
    int level = header->value; //header use this field to store current level
    int i;

    for (i = level; i >= 0; i--) {
        while (p->forward[i] && p->forward[i]->value < value)
            p = p->forward[i];
        should_update[i] = p;
    }
    p = p->forward[0];

    if (p && p->value == value) {
        for (i = 0; i < level + 1; i++) {
            if (should_update[i]->forward[i] != p)
                break;
            should_update[i]->forward[i] = p->forward[i];
        }

        while (level > 0 && header->forward[level] == NULL) {
            level--;
            header->value = level;
        }
    }
}

int skiplist_contains(struct skiplist_node *header, int value) {
    int i;
    int level = header->value;
    struct skiplist_node *p = header;

    for (i = level; i >= 0; i--) {
        while (p->forward[i] && p->forward[i]->value <= value)
            p = p->forward[i];
        if (p->value == value)
            return 1;
    }
    return 0;
}
