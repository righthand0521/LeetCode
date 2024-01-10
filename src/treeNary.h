#include <limits.h>

#ifndef TREE_NARY_H
#define TREE_NARY_H

struct Node {
    int val;
    int numChildren;
    struct Node** children;
};

#endif  // TREE_NARY_H
