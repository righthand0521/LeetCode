#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef List_H
#define List_H

typedef struct {
    struct ListNode* head;
    int size;
} List;
List* listCreate() {
    List* pObj = NULL;

    pObj = (List*)malloc(sizeof(List));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->head = NULL;
    pObj->size = 0;

    return pObj;
}
void listPush(List* list, int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (node == NULL) {
        perror("malloc");
        return;
    }
    node->val = val;
    node->next = list->head;
    list->head = node;
    list->size++;
}
void listPop(List* list) {
    if (list->head == NULL) {
        return;
    }
    struct ListNode* temp = list->head;
    list->head = list->head->next;
    free(temp);
    list->size--;
}
int listAt(List* list, int index) {
    int retVal = -1;

    struct ListNode* cur = list->head;
    for (int i = 0; i < index && cur != NULL; i++) {
        cur = cur->next;
    }
    if (cur != NULL) {
        retVal = cur->val;
    }

    return retVal;
}
void listReverse(List* list) {
    struct ListNode* prev = NULL;
    struct ListNode* cur = list->head;
    struct ListNode* next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    list->head = prev;
}
void listFree(List* list) {
    while (list->head != NULL) {
        listPop(list);
    }
    free(list);
}

#endif  // List_H
#ifndef Hash_H
#define Hash_H

typedef struct {
    int key;
    List* val;
    UT_hash_handle hh;
} HashItem;
HashItem* hashFindItem(HashItem** obj, int key) {
    HashItem* pEntry = NULL;

    HASH_FIND_INT(*obj, &key, pEntry);

    return pEntry;
}
bool hashAddItem(HashItem** obj, int key, List* val) {
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
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
List* hashGetItem(HashItem** obj, int key) {
    List* pRetVal = NULL;

    HashItem* pEntry = hashFindItem(obj, key);
    if (pEntry == NULL) {
        pRetVal = listCreate();
        hashAddItem(obj, key, pRetVal);
        return pRetVal;
    }
    pRetVal = pEntry->val;

    return pRetVal;
}
void hashFree(HashItem** obj) {
    HashItem* curr = NULL;
    HashItem* tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        listFree(curr->val);
        free(curr);
    }
}
void hashIterate(HashItem** obj, void (*callback)(HashItem* item)) {
    HashItem* curr = NULL;
    HashItem* tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        //
        callback(curr);
    }
}
void reverseList(HashItem* item) {
    //
    listReverse(item->val);
}

#endif  // Hash_H
#ifndef LazyTag_H
#define LazyTag_H

typedef struct {
    int toAdd;
} LazyTag;
void lazyTagAdd(LazyTag* tag, LazyTag* other) {
    //
    tag->toAdd += other->toAdd;
}
bool lazyTagHasTag(LazyTag* tag) {
    bool retVal = (tag->toAdd != 0);

    return retVal;
}
void lazyTagClear(LazyTag* tag) {
    //
    tag->toAdd = 0;
}

#endif  // LazyTag_H
#ifndef SegmentTree_H
#define SegmentTree_H

typedef struct {
    int minValue;
    int maxValue;
    LazyTag lazyTag;
} SegmentTreeNode;
typedef struct {
    int n;
    SegmentTreeNode* tree;
} SegmentTree;
void segmentTreeApplyTag(SegmentTree* seg, int i, LazyTag* tag) {
    seg->tree[i].minValue += tag->toAdd;
    seg->tree[i].maxValue += tag->toAdd;
    lazyTagAdd(&seg->tree[i].lazyTag, tag);
}
void segmentTreePushdown(SegmentTree* seg, int i) {
    if (lazyTagHasTag(&seg->tree[i].lazyTag)) {
        LazyTag tag = {seg->tree[i].lazyTag.toAdd};
        segmentTreeApplyTag(seg, i << 1, &tag);
        segmentTreeApplyTag(seg, (i << 1) | 1, &tag);
        lazyTagClear(&seg->tree[i].lazyTag);
    }
}
void segmentTreePushup(SegmentTree* seg, int i) {
    seg->tree[i].minValue = fmin(seg->tree[i << 1].minValue, seg->tree[(i << 1) | 1].minValue);
    seg->tree[i].maxValue = fmax(seg->tree[i << 1].maxValue, seg->tree[(i << 1) | 1].maxValue);
}
void segmentTreeBuild(SegmentTree* seg, int* data, int l, int r, int i) {
    if (l == r) {
        seg->tree[i].minValue = seg->tree[i].maxValue = data[l - 1];
        return;
    }

    int mid = l + ((r - l) >> 1);
    segmentTreeBuild(seg, data, l, mid, i << 1);
    segmentTreeBuild(seg, data, mid + 1, r, (i << 1) | 1);
    segmentTreePushup(seg, i);
}
void segmentTreeUpdate(SegmentTree* seg, int targetL, int targetR, LazyTag* tag, int l, int r, int i) {
    if ((targetL <= l) && (r <= targetR)) {
        segmentTreeApplyTag(seg, i, tag);
        return;
    }

    segmentTreePushdown(seg, i);
    int mid = l + ((r - l) >> 1);
    if (targetL <= mid) {
        segmentTreeUpdate(seg, targetL, targetR, tag, l, mid, i << 1);
    }
    if (targetR > mid) {
        segmentTreeUpdate(seg, targetL, targetR, tag, mid + 1, r, (i << 1) | 1);
    }
    segmentTreePushup(seg, i);
}
int segmentTreeFind(SegmentTree* seg, int targetL, int targetR, int val, int l, int r, int i) {
    int retVal = -1;

    if ((seg->tree[i].minValue > val) || (seg->tree[i].maxValue < val)) {
        return retVal;
    }

    if (l == r) {
        retVal = l;
        return retVal;
    }

    segmentTreePushdown(seg, i);

    int mid = l + ((r - l) >> 1);
    if (targetR >= mid + 1) {
        retVal = segmentTreeFind(seg, targetL, targetR, val, mid + 1, r, (i << 1) | 1);
        if (retVal != -1) {
            return retVal;
        }
    }

    if (targetL <= mid) {
        retVal = segmentTreeFind(seg, targetL, targetR, val, l, mid, i << 1);
        return retVal;
    }

    return retVal;
}
SegmentTree* segmentTreeCreate(int* data, int n) {
    SegmentTree* pObj = NULL;

    pObj = (SegmentTree*)malloc(sizeof(SegmentTree));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->n = n;
    pObj->tree = (SegmentTreeNode*)calloc(n * 4 + 1, sizeof(SegmentTreeNode));
    segmentTreeBuild(pObj, data, 1, n, 1);

    return pObj;
}
void segmentTreeAdd(SegmentTree* seg, int l, int r, int val) {
    LazyTag tag = {val};
    segmentTreeUpdate(seg, l, r, &tag, 1, seg->n, 1);
}
int segmentTreeFindLast(SegmentTree* seg, int start, int val) {
    int retVal = -1;

    if (start <= seg->n) {
        retVal = segmentTreeFind(seg, start, seg->n, val, 1, seg->n, 1);
    }

    return retVal;
}
void segmentTreeFree(SegmentTree* seg) {
    free(seg->tree);
    free(seg);
}

#endif  // SegmentTree_H
int sgn(int x) {
    int retVal = -1;

    if (x % 2 == 0) {
        retVal = 1;
    }

    return retVal;
}
int longestBalanced(int* nums, int numsSize) {
    int retVal = 0;

    int prefixSum[numsSize];
    memset(prefixSum, 0, sizeof(prefixSum));
    prefixSum[0] = sgn(nums[0]);

    HashItem* occurrences = NULL;
    List* list0 = hashGetItem(&occurrences, nums[0]);
    listPush(list0, 1);
    for (int i = 1; i < numsSize; i++) {
        prefixSum[i] = prefixSum[i - 1];
        List* occ = hashGetItem(&occurrences, nums[i]);
        if (occ->size == 0) {
            prefixSum[i] += sgn(nums[i]);
        }
        listPush(occ, i + 1);
    }
    hashIterate(&occurrences, reverseList);

    SegmentTree* seg = segmentTreeCreate(prefixSum, numsSize);
    for (int i = 0; i < numsSize; i++) {
        int findResult = segmentTreeFindLast(seg, i + retVal, 0);
        int newLen = findResult - i;
        if (newLen > retVal) {
            retVal = newLen;
        }

        int nextPos = numsSize + 1;
        List* occ = hashGetItem(&occurrences, nums[i]);
        listPop(occ);
        if (occ->size > 0) {
            nextPos = listAt(occ, 0);
        }
        segmentTreeAdd(seg, i + 1, nextPos - 1, -sgn(nums[i]));
    }

    //
    segmentTreeFree(seg);
    hashFree(&occurrences);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 5, 4, 3}, 4}, {{3, 2, 2, 5, 4}, 5}, {{1, 2, 3, 2}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,5,4,3]
     *  Output: 4
     *
     *  Input: nums = [3,2,2,5,4]
     *  Output: 5
     *
     *  Input: nums = [1,2,3,2]
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = longestBalanced(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
