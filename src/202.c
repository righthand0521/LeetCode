#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINK_LIST (1)
#define UTHASH (1)
#if (LINK_LIST)
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* createNode(int value) {
    struct ListNode* pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->val = value;
    pNew->next = NULL;

    return pNew;
}
void freeNode(struct ListNode* pHead) {
    struct ListNode* pFree = NULL;
    while (pHead != NULL) {
        pFree = pHead;
        pHead = pHead->next;
        free(pFree);
    }
}
struct ListNode* addValueToEnd(struct ListNode* pHead, int value) {
    struct ListNode* pNew = createNode(value);
    if (pNew == NULL) {
        return pHead;
    }

    if (pHead == NULL) {
        pHead = pNew;
        return pHead;
    }

    struct ListNode* pCurrent = pHead;
    while (pCurrent->next != NULL) {
        pCurrent = pCurrent->next;
    }
    pCurrent->next = pNew;

    return pHead;
}
bool searchNode(struct ListNode* pHead, int searchValue) {
    bool retVal = true;

    struct ListNode* pCurrent = pHead;
    while (pCurrent != NULL) {
        if (pCurrent->val == searchValue) {
            return retVal;
        }
        pCurrent = pCurrent->next;
    }
    retVal = false;

    return retVal;
}
#elif (UTHASH)
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashStruct {
    int value;
    UT_hash_handle hh;
};

void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
#endif
bool isHappy(int n) {
    bool retVal = true;

#if (LINK_LIST)
    printf("LINK_LIST\n");

    struct ListNode* pHead = NULL;
#elif (UTHASH)
    printf("UTHASH\n");

    struct hashStruct* map = NULL;
    struct hashStruct* temp;
#endif

    int sum;
    int num = n;
    while (num != 1) {
#if (LINK_LIST)
        retVal = searchNode(pHead, num);
        if (retVal == true) {
            break;
        }
        pHead = addValueToEnd(pHead, num);
#elif (UTHASH)
        temp = NULL;
        HASH_FIND_INT(map, &num, temp);
        if (temp != NULL) {
            break;
        }
        temp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
        if (temp == NULL) {
            perror("malloc");
            freeAll(map);
            retVal = false;
            return retVal;
        }
        temp->value = num;
        HASH_ADD_INT(map, value, temp);
#endif

        sum = 0;
        while (num > 0) {
            sum += ((num % 10) * (num % 10));
            num = (num - num % 10) / 10;
        }
        num = sum;
    }
    retVal = (num == 1) ? true : false;

#if (LINK_LIST)
    if (pHead != NULL) {
        freeNode(pHead);
        pHead = NULL;
    }
#elif (UTHASH)
    freeAll(map);
#endif

    return retVal;
}

int main(int argc, char** argv) {
    int testCase[] = {19, 2, INT_MAX, 7, 4, 37};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i]);

        answer = isHappy(testCase[i]);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
