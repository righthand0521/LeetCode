#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* pNums;
} NumArray;
NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray* pCreate = (NumArray*)malloc(sizeof(NumArray));
    if (pCreate == NULL) {
        perror("malloc");
        return pCreate;
    }
    pCreate->pNums = NULL;

    pCreate->pNums = (int*)malloc(numsSize * sizeof(int));
    if (pCreate->pNums == NULL) {
        perror("malloc");
        free(pCreate);
        pCreate = NULL;
        return pCreate;
    }
    memset(pCreate->pNums, 0, (numsSize * sizeof(int)));
    memcpy(pCreate->pNums, nums, (numsSize * sizeof(int)));

    return pCreate;
}
int numArraySumRange(NumArray* obj, int left, int right) {
    int retVal = 0;

    int i;
    for (i = left; i <= right; ++i) {
        retVal += obj->pNums[i];
    }

    return retVal;
}
void numArrayFree(NumArray* obj) {
    if (obj == NULL) {
        return;
    }

    if (obj->pNums) {
        free(obj->pNums);
        obj->pNums = NULL;
    }
    free(obj);
    obj = NULL;
}
/**
 * Your NumArray struct will be instantiated and called as such:
 * NumArray* obj = numArrayCreate(nums, numsSize);
 * int param_1 = numArraySumRange(obj, left, right);
 * numArrayFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][MAX_SIZE];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"NumArray", "sumRange", "sumRange", "sumRange"},
                     {{-2, 0, 3, -5, 2, -1}, {0, 2}, {2, 5}, {0, 5}},
                     {6, 2, 2, 2},
                     4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    NumArray* obj = NULL;
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
            if (strcmp(testCase[i].methods[j], "NumArray") == 0) {
                obj = numArrayCreate(testCase[i].val[j], testCase[i].valSize[j]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "sumRange") == 0) {
                retInt = numArraySumRange(obj, testCase[i].val[j][0], testCase[i].val[j][1]);
                printf("%s%d", (j == 0) ? "" : ", ", retInt);
            }
        }
        printf("]\n");

        numArrayFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
