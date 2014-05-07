#include <stdlib.h>
#include <assert.h>
#include "skiplist.h"

int main(int argc, char *argv[]) {
    struct skiplist_node *header = new_skiplist();

    skiplist_insert(header, 1);
    skiplist_insert(header, -1);
    skiplist_insert(header, 100);
    skiplist_insert(header, 5);
    skiplist_insert(header, -100);

    assert(skiplist_contains(header, 1));
    assert(skiplist_contains(header, -1));
    assert(skiplist_contains(header, 100));
    assert(skiplist_contains(header, 5));
    assert(skiplist_contains(header, -100));
}
