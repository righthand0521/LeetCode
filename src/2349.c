#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

// https://leetcode.cn/problems/design-a-number-container-system/solutions/2830597/cyu-yan-ti-jie-by-6oofy-i3anachhuk-jakh/
typedef struct IndexList {
    int index;
    struct IndexList *next;
} IndexList;
typedef struct ValType {
    int val;
    int minIndex;
    IndexList *head;
    UT_hash_handle hh;
} ValType;
typedef struct IndexType {
    int index;
    int val;
    UT_hash_handle hh;
} IndexType;
typedef struct {
    IndexType *indexDict;
    ValType *valDict;
} NumberContainers;
NumberContainers *numberContainersCreate() {
    NumberContainers *obj = (NumberContainers *)malloc(sizeof(NumberContainers));
    obj->indexDict = NULL;
    obj->valDict = NULL;
    return obj;
}
void numberContainersChange(NumberContainers *obj, int index, int number) {
    IndexType *indexRes = NULL;
    ValType *temp1 = NULL;
    ValType *temp2 = NULL;
    int flag = 0;
    int insertVal = 0;
    HASH_FIND_INT(obj->indexDict, &index, indexRes);
    if (indexRes == NULL) {
        indexRes = malloc(sizeof(IndexType));
        indexRes->index = index;
        indexRes->val = number;
        HASH_ADD_INT(obj->indexDict, index, indexRes);
    } else {
        if (indexRes->val == number) {
            flag = 1;
        } else {
            flag = 2;
            insertVal = indexRes->val;
            indexRes->val = number;
        }
    }
    if (flag == 1) {
        return;
    }
    HASH_FIND_INT(obj->valDict, &number, temp2);
    if (temp2 == NULL) {
        temp2 = malloc(sizeof(ValType));
        temp2->val = number;
        temp2->minIndex = index;
        temp2->head = malloc(sizeof(IndexList));
        temp2->head->index = index;
        temp2->head->next = NULL;
        HASH_ADD_INT(obj->valDict, val, temp2);
    } else {
        IndexList *node1 = malloc(sizeof(IndexList));
        IndexList *cur10 = temp2->head;
        node1->index = index;
        node1->next = cur10;
        temp2->head = node1;
        if (index < temp2->minIndex) {
            temp2->minIndex = index;
        }
    }
    if (flag == 2) {
        HASH_FIND_INT(obj->valDict, &insertVal, temp1);
        IndexList *dummy = malloc(sizeof(IndexList));
        IndexList *node = dummy;
        dummy->next = temp1->head;
        int update = 0;
        if (temp1->minIndex == index) {
            update = 1;
        }
        while (dummy->next) {
            if (dummy->next->index == index) {
                IndexList *temp10 = dummy->next;
                dummy->next = dummy->next->next;
                free(temp10);
                break;
            } else {
                dummy = dummy->next;
            }
        }
        if (node->next == NULL) {
            HASH_DEL(obj->valDict, temp1);
            free(temp1);
        } else {
            temp1->head = node->next;
            if (update == 1) {
                IndexList *node88 = temp1->head;
                temp1->minIndex = node88->index;
                while (node88) {
                    if (node88->index < temp1->minIndex) {
                        temp1->minIndex = node88->index;
                    }
                    node88 = node88->next;
                }
            }
        }
    }
}
int numberContainersFind(NumberContainers *obj, int number) {
    int index = -1;
    ValType *temp2 = NULL;
    HASH_FIND_INT(obj->valDict, &number, temp2);
    if (temp2 != NULL) {
        return temp2->minIndex;
    }
    return index;
}
void numberContainersFree(NumberContainers *obj) {
    IndexType *cur;
    IndexType *nxt;
    HASH_ITER(hh, obj->indexDict, cur, nxt) {
        HASH_DEL(obj->indexDict, cur);
        free(cur);
    }
    ValType *cur2;
    ValType *nxt2;
    HASH_ITER(hh, obj->valDict, cur2, nxt2) {
        HASH_DEL(obj->valDict, cur2);
        while (cur2->head) {
            IndexList *temp = cur2->head;
            cur2->head = cur2->head->next;
            free(temp);
        }
        free(cur2);
    }
    free(obj);
}
/**
 * Your NumberContainers struct will be instantiated and called as such:
 * NumberContainers* obj = numberContainersCreate();
 * numberContainersChange(obj, index, number);
 * int param_2 = numberContainersFind(obj, number);
 * numberContainersFree(obj);
 */

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char *methods[MAX_SIZE];
        int val[MAX_SIZE][4];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"},
                     {{}, {10}, {2, 10}, {1, 10}, {3, 10}, {5, 10}, {10}, {1, 20}, {10}},
                     {0, 1, 2, 2, 2, 2, 1, 2, 1},
                     9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"]
     *  [[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]
     *  Output
     *  [null, -1, null, null, null, null, 1, null, 2]
     */

    NumberContainers *obj = NULL;
    int retInt;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[", (j == 0) ? "" : ", ");
            for (k = 0; k < testCase[i].valSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ", ", testCase[i].val[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "NumberContainers") == 0) {
                obj = numberContainersCreate();
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "change") == 0) {
                numberContainersChange(obj, testCase[i].val[j][0], testCase[i].val[j][1]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "find") == 0) {
                retInt = numberContainersFind(obj, testCase[i].val[j][0]);
                printf("%s%d", (j == 0) ? "" : ", ", retInt);
            }
        }
        printf("]\n");

        numberContainersFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
