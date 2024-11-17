#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DEQUE_H
#define DEQUE_H

typedef struct DLinkListNode {
    int val;
    struct DLinkListNode* prev;
    struct DLinkListNode* next;
} DLinkListNode;
DLinkListNode* dLinkListNodeCreat(int val) {
    DLinkListNode* obj = NULL;

    obj = (DLinkListNode*)malloc(sizeof(DLinkListNode));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->val = val;
    obj->prev = NULL;
    obj->next = NULL;

    return obj;
}
typedef struct {
    int capacity;
    DLinkListNode* head;
    DLinkListNode* tail;
    int size;
} MyCircularDeque;
MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque* obj = NULL;

    obj = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->capacity = k;
    obj->head = NULL;
    obj->tail = NULL;
    obj->size = 0;

    return obj;
}
bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    bool retVal = false;

    if (obj->size == 0) {
        retVal = true;
    }

    return retVal;
}
bool myCircularDequeIsFull(MyCircularDeque* obj) {
    bool retVal = false;

    if (obj->size == obj->capacity) {
        retVal = true;
    }

    return retVal;
}
bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    bool retVal = false;

    if (myCircularDequeIsFull(obj) == true) {
        return retVal;
    }

    DLinkListNode* pNew = dLinkListNodeCreat(value);
    if (pNew == NULL) {
        return retVal;
    }

    if (obj->size == 0) {
        obj->head = pNew;
        obj->tail = pNew;
    } else {
        pNew->next = obj->head;
        obj->head->prev = pNew;
        obj->head = pNew;
    }
    obj->size++;
    retVal = true;

    return retVal;
}
bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    bool retVal = false;

    if (myCircularDequeIsFull(obj) == true) {
        return retVal;
    }

    DLinkListNode* pNew = dLinkListNodeCreat(value);
    if (pNew == NULL) {
        return retVal;
    }

    if (obj->size == 0) {
        obj->head = pNew;
        obj->tail = pNew;
    } else {
        obj->tail->next = pNew;
        pNew->prev = obj->tail;
        obj->tail = pNew;
    }
    obj->size++;
    retVal = true;

    return retVal;
}
bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    bool retVal = false;

    if (myCircularDequeIsEmpty(obj) == true) {
        return retVal;
    }

    DLinkListNode* pDelete = obj->head;
    obj->head = obj->head->next;
    if (obj->head != NULL) {
        obj->head->prev = NULL;
    }
    free(pDelete);
    pDelete = NULL;
    obj->size--;
    retVal = true;

    return retVal;
}
bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    bool retVal = false;

    if (myCircularDequeIsEmpty(obj) == true) {
        return retVal;
    }

    DLinkListNode* pDelete = obj->tail;
    obj->tail = obj->tail->prev;
    if (obj->tail != NULL) {
        obj->tail->next = NULL;
    }
    free(pDelete);
    pDelete = NULL;
    obj->size--;
    retVal = true;

    return retVal;
}
int myCircularDequeGetFront(MyCircularDeque* obj) {
    int retVal = -1;  // Returns -1 if the deque is empty.

    if (myCircularDequeIsEmpty(obj) == false) {
        retVal = obj->head->val;
    }

    return retVal;
}
int myCircularDequeGetRear(MyCircularDeque* obj) {
    int retVal = -1;  // Returns -1 if the deque is empty.

    if (myCircularDequeIsEmpty(obj) == false) {
        retVal = obj->tail->val;
    }

    return retVal;
}
void myCircularDequeFree(MyCircularDeque* obj) {
    DLinkListNode* pDelete = NULL;
    while (obj->head != obj->tail) {
        pDelete = obj->head;
        obj->head = obj->head->next;
        free(pDelete);
        pDelete = NULL;
    }
    free(obj->head);
    obj->head = NULL;

    free(obj);
    obj = NULL;
}

#endif  // DEQUE_H
int shortestSubarray(int* nums, int numsSize, int k) {
    int retVal = -1;

    long long prefixSums[numsSize + 1];
    prefixSums[0] = 0;
    for (int i = 1; i <= numsSize; i++) {
        prefixSums[i] = prefixSums[i - 1] + nums[i - 1];
    }

    MyCircularDeque* candidateIndices = NULL;
    candidateIndices = myCircularDequeCreate(numsSize + 1);

    int shortestSubarrayLength = INT_MAX;
    for (int i = 0; i <= numsSize; i++) {
        // Remove candidates from front of deque where subarray sum meets target
        while ((myCircularDequeIsEmpty(candidateIndices) == false) &&
               (prefixSums[i] - prefixSums[myCircularDequeGetFront(candidateIndices)] >= k)) {
            shortestSubarrayLength = fmin(shortestSubarrayLength, i - myCircularDequeGetFront(candidateIndices));
            myCircularDequeDeleteFront(candidateIndices);
        }

        // Maintain monotonicity by removing indices with larger prefix sums
        while ((myCircularDequeIsEmpty(candidateIndices) == false) &&
               (prefixSums[i] <= prefixSums[myCircularDequeGetRear(candidateIndices)])) {
            myCircularDequeDeleteLast(candidateIndices);
        }

        // Add current index to candidates
        myCircularDequeInsertLast(candidateIndices, i);
    }
    if (shortestSubarrayLength != INT_MAX) {
        retVal = shortestSubarrayLength;
    }

    //
    myCircularDequeFree(candidateIndices);
    candidateIndices = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1}, 1, 1}, {{1, 2}, 2, 4}, {{2, -1, 2}, 3, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1], k = 1
     *  Output: 1
     *
     *  Input: nums = [1,2], k = 4
     *  Output: -1
     *
     *  Input: nums = [2,-1,2], k = 3
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = shortestSubarray(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
