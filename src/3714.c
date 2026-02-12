#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef HASH_H
#define HASH_H

typedef struct {
    long long key;
    int val;
    UT_hash_handle hh;
} HashItem;
HashItem* hashFindItem(HashItem** obj, long long key) {
    HashItem* pEntry = NULL;

    HASH_FIND(hh, *obj, &key, sizeof(long long), pEntry);

    return pEntry;
}
bool hashAddItem(HashItem** obj, long long key, int val) {
    bool retVal = false;

    if (hashFindItem(obj, key)) {
        return retVal;
    }

    HashItem* pEntry = (HashItem*)malloc(sizeof(HashItem));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_KEYPTR(hh, *obj, &pEntry->key, sizeof(long long), pEntry);
    retVal = true;

    return retVal;
}
void hashSetItem(HashItem** obj, long long key, int val) {
    HashItem* pEntry = hashFindItem(obj, key);
    if (pEntry == NULL) {
        hashAddItem(obj, key, val);
    } else {
        pEntry->val = val;
    }
}
int hashGetItem(HashItem** obj, long long key, int defaultVal) {
    int retVal = defaultVal;

    HashItem* pEntry = hashFindItem(obj, key);
    if (pEntry != NULL) {
        retVal = pEntry->val;
    }

    return retVal;
}
void hashFree(HashItem** obj) {
    HashItem* curr = NULL;
    HashItem* tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}

#endif  // HASH_H
int case2Helper(char* s, char x, char y) {
    int retVal = 0;

    int sSize = strlen(s);

    HashItem *h, *prevEntry;
    int j, diff, length;
    for (int i = 0; i < sSize; i++) {
        if ((s[i] != x) && (s[i] != y)) {
            continue;
        }

        h = NULL;
        hashAddItem(&h, 0, i - 1);

        diff = 0;
        j = i;
        while ((j < sSize) && ((s[j] == x) || (s[j] == y))) {
            diff += (s[j] == x) ? 1 : -1;

            prevEntry = hashFindItem(&h, diff);
            if (prevEntry != NULL) {
                length = j - prevEntry->val;
                retVal = fmax(retVal, length);
            } else {
                hashAddItem(&h, diff, j);
            }

            j++;
        }
        hashFree(&h);

        i = j - 1;
    }

    return retVal;
}
int longestBalanced(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

    // Case 1: single character
    int last = 0;
    for (int i = 0; i < sSize; i++) {
        if ((i > 0) && (s[i] == s[i - 1])) {
            last++;
        } else {
            last = 1;
        }
        if (last > retVal) {
            retVal = last;
        }
    }

    // Case 2: two distinct characters
    retVal = fmax(retVal, case2Helper(s, 'a', 'b'));
    retVal = fmax(retVal, case2Helper(s, 'b', 'c'));
    retVal = fmax(retVal, case2Helper(s, 'a', 'c'));

    // Case 3: all three characters
    HashItem* h = NULL;
    long long initKey = ((long long)sSize << 32) | sSize;
    hashAddItem(&h, initKey, -1);
    //
    int diffAB = 0;
    int diffBC = 0;
    char c;
    long long key;
    HashItem* prevEntry;
    int length;
    for (int i = 0; i < sSize; i++) {
        c = s[i];
        switch (c) {
            case 'a':
                diffAB--;
                break;
            case 'b':
                diffAB++;
                diffBC++;
                break;
            case 'c':
                diffBC--;
                break;
        }

        key = ((long long)(diffAB + sSize) << 32) | (diffBC + sSize);
        prevEntry = hashFindItem(&h, key);
        if (prevEntry != NULL) {
            length = i - prevEntry->val;
            retVal = fmax(retVal, length);
        } else {
            hashAddItem(&h, key, i);
        }
    }
    //
    hashFree(&h);

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"abbac"}, {"aabcc"}, {"aba"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abbac"
     *  Output: 4
     *
     *  Input: s = "aabcc"
     *  Output: 3
     *
     *  Input: s = "aba"
     *  Output: 2
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = longestBalanced(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
