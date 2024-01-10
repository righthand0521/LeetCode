#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
typedef struct {
    int* heap;
    int heapSize;
} KthLargest;
KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest* pRetVal = NULL;

    pRetVal = (KthLargest*)malloc(sizeof(KthLargest));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->heap = (int*)malloc(k * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    pRetVal->heapSize = k;
    memset(pRetVal->heap, 0, (k * sizeof(int)));
    for (int i = 0; i < k; ++i) {
        pRetVal->heap[i] = INT_MIN;
    }

    qsort(nums, numsSize, sizeof(int), compareInteger);
    for (int i = 0; i < numsSize; ++i) {
        if (i >= k) {
            break;
        }
        pRetVal->heap[k - 1 - i] = nums[i];
    }

    return pRetVal;
}
int kthLargestAdd(KthLargest* obj, int val) {
    int retVal = obj->heap[0];

    if (val < obj->heap[0]) {
        return retVal;
    }

    for (int i = obj->heapSize - 1; i >= 0; --i) {
        if (obj->heap[i] > val) {
            continue;
        }
        int tmp = obj->heap[i];
        obj->heap[i] = val;
        val = tmp;
    }
    retVal = obj->heap[0];

    return retVal;
}
void kthLargestFree(KthLargest* obj) {
    free(obj->heap);
    obj->heap = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 * kthLargestFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE];
        int calls;
    } testCase[] = {{{"KthLargest", "add", "add", "add", "add", "add"}, {0, 3, 5, 10, 9, 4}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["KthLargest", "add", "add", "add", "add", "add"]
     *  [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
     *  Output
     *  [null, 4, 5, 5, 8, 8]
     */

    KthLargest* obj = NULL;
    int nums[MAX_SIZE];
    int retInt;
    char displayStr[8];
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (j == 0) {
                if (i == 0) {
                    printf("[3, [4, 5, 8, 2]]");
                }
                continue;
            }
            printf("%s[%d]", (j == 0) ? "" : ", ", testCase[i].val[j]);
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            memset(displayStr, 0, sizeof(displayStr));
            if (strcmp(testCase[i].methods[j], "KthLargest") == 0) {
                memset(nums, 0, sizeof(nums));
                if (i == 0) {
                    nums[0] = 4;
                    nums[1] = 5;
                    nums[2] = 8;
                    nums[3] = 2;
                }
                obj = kthLargestCreate(3, nums, 4);
                snprintf(displayStr, sizeof(displayStr), "%s", "null");
            } else if (strcmp(testCase[i].methods[j], "add") == 0) {
                retInt = kthLargestAdd(obj, testCase[i].val[j]);
                snprintf(displayStr, sizeof(displayStr), "%d", retInt);
            }
            printf("%s%s", (j == 0) ? "" : ", ", displayStr);
        }
        printf("]\n");

        kthLargestFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
