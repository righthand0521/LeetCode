#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "list.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct {
    int* arr;
    int length;
} Solution;
Solution* solutionCreate(struct ListNode* head) {
    Solution* pRetVal = NULL;

    pRetVal = (Solution*)malloc(sizeof(Solution));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->length = 0;

    struct ListNode* pNext = head;
    while (pNext != NULL) {
        pNext = pNext->next;
        pRetVal->length++;
    }

    pRetVal->arr = (int*)malloc(pRetVal->length * sizeof(int));
    if (pRetVal->arr == NULL) {
        perror("malloc");
        return pRetVal;
    }

    pNext = head;
    int i;
    for (i = 0; i < pRetVal->length; ++i) {
        pRetVal->arr[i] = pNext->val;
        pNext = pNext->next;
    }

    return pRetVal;
}
int solutionGetRandom(Solution* obj) {
    int retVal = obj->arr[rand() % obj->length];

    return retVal;
}
void solutionFree(Solution* obj) {
    free(obj->arr);
    obj->arr = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your Solution struct will be instantiated and called as such:
 * Solution* obj = solutionCreate(head);
 * int param_1 = solutionGetRandom(obj);
 * solutionFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int nums[MAX_SIZE][10];
        int numsSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"},
                     {{1, 2, 3}, {}, {}, {}, {}, {}},
                     {3, 0, 0, 0, 0, 0},
                     6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
     *  [[[1, 2, 3]], [], [], [], [], []]
     *  Output
     *  [null, 1, 3, 2, 2, 3]
     */

    struct ListNode* pHead = NULL;
    Solution* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "Solution") == 0) {
                printf("[[");
                for (k = 0; k < testCase[i].numsSize[j]; ++k) {
                    printf("%s%d", (k == 0) ? "" : ", ", testCase[i].nums[j][k]);
                }
                printf("]]");
            } else if (strcmp(testCase[i].methods[j], "getRandom") == 0) {
                printf("%s[]", (j == 0) ? "" : ", ");
            }
        }
        printf("]\n");

        printf("Output\n[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "Solution") == 0) {
                pHead = buildList(testCase[i].nums[j], testCase[i].numsSize[j]);
                pAnswer = solutionCreate(pHead);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "getRandom") == 0) {
                srand(time(NULL) + j);
                printf("%s%d", (j == 0) ? "" : ", ", solutionGetRandom(pAnswer));
            }
        }
        solutionFree(pAnswer);
        pAnswer = NULL;
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
