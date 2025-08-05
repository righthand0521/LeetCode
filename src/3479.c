#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#define MAX_SEGTREE_SIZE (400007)  // n == fruits.length == baskets.length, 1 <= n <= 10 ^ 5 .

int segmentTree[MAX_SEGTREE_SIZE];
int* basketsBuffer;

void build(int p, int left, int right) {
    if (left == right) {
        segmentTree[p] = basketsBuffer[left];
        return;
    }

    int middle = (left + right) >> 1;
    build((p << 1), left, middle);
    build((p << 1) | 1, middle + 1, right);
    segmentTree[p] = fmax(segmentTree[(p << 1)], segmentTree[(p << 1) | 1]);
}
int query(int p, int left, int right, int ql, int qr) {
    int retVal = 0;

    if ((ql > right) || (qr < left)) {
        retVal = INT_MIN;
    } else if ((ql <= left) && (right <= qr)) {
        retVal = segmentTree[p];
    } else {
        int middle = (left + right) >> 1;
        retVal = fmax(query((p << 1), left, middle, ql, qr), query((p << 1) | 1, middle + 1, right, ql, qr));
    }

    return retVal;
}
void update(int p, int left, int right, int pos, int val) {
    if (left == right) {
        segmentTree[p] = val;
        return;
    }

    int middle = (left + right) >> 1;
    if (pos <= middle) {
        update((p << 1), left, middle, pos, val);
    } else {
        update((p << 1) | 1, middle + 1, right, pos, val);
    }
    segmentTree[p] = fmax(segmentTree[(p << 1)], segmentTree[(p << 1) | 1]);
}

#endif  // SEGMENT_TREE_H
int numOfUnplacedFruits(int* fruits, int fruitsSize, int* baskets, int basketsSize) {
    int retVal = 0;

    basketsBuffer = baskets;

    if (basketsSize == 0) {
        retVal = fruitsSize;
        return retVal;
    }

    for (int i = 0; i < MAX_SEGTREE_SIZE; i++) {
        segmentTree[i] = INT_MIN;
    }

    build(1, 0, basketsSize - 1);

    int middle, left, right, res;
    for (int i = 0; i < fruitsSize; i++) {
        res = -1;

        left = 0;
        right = basketsSize - 1;
        while (left <= right) {
            middle = (left + right) >> 1;
            if (query(1, 0, basketsSize - 1, 0, middle) >= fruits[i]) {
                res = middle;
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }

        if ((res != -1) && (baskets[res] >= fruits[i])) {
            update(1, 0, basketsSize - 1, res, INT_MIN);
        } else {
            retVal++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int fruits[MAX_SIZE];
        int fruitsSize;
        int baskets[MAX_SIZE];
        int basketsSize;
    } testCase[] = {{{4, 2, 5}, 3, {3, 5, 4}, 3}, {{3, 6, 1}, 3, {6, 4, 7}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: fruits = [4,2,5], baskets = [3,5,4]
     *  Output: 1
     *
     *  Input: fruits = [3,6,1], baskets = [6,4,7]
     *  Output: 0
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: fruits = [");
        for (j = 0; j < testCase[i].fruitsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].fruits[j]);
        }
        printf("], baskets = [");
        for (j = 0; j < testCase[i].basketsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].baskets[j]);
        }
        printf("]\n");

        answer = numOfUnplacedFruits(testCase[i].fruits, testCase[i].fruitsSize, testCase[i].baskets,
                                     testCase[i].basketsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
