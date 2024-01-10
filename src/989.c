#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* addToArrayForm(int* num, int numSize, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    // 1 <= k <= 10^4
#define MAX_K_SIZE (5)
    int len = (numSize > MAX_K_SIZE) ? (numSize + 1) : (MAX_K_SIZE + 1);
    int buf[len];
    memset(buf, 0, sizeof(buf));
    --numSize;

    int sum = 0;
    int carry = 0;
    int idx = len - 1;
    while ((numSize >= 0) && (k > 0)) {
        sum = num[numSize--] + (k % 10) + carry;
        carry = sum / 10;
        buf[idx--] = sum % 10;
        k /= 10;
    }
    while (numSize >= 0) {
        sum = num[numSize--] + carry;
        carry = sum / 10;
        buf[idx--] = sum % 10;
    }
    while (k > 0) {
        sum = (k % 10) + carry;
        carry = sum / 10;
        buf[idx--] = sum % 10;
        k /= 10;
    }
    if (carry == 1) {
        buf[idx--] = carry;
    }

    (*returnSize) = len - 1 - idx;
    pRetVal = (int*)calloc((*returnSize), sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memcpy(pRetVal, buf + 1 + idx, (*returnSize) * sizeof(int));

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int num[MAX_SIZE];
        int numSize;
        int k;
        int returnSize;
    } testCase[] = {{{1, 2, 0, 0}, 4, 34, 0}, {{2, 7, 4}, 3, 181, 0}, {{2, 1, 5}, 3, 806, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = [1,2,0,0], k = 34
     *  Output: [1,2,3,4]
     *
     *  Input: num = [2,7,4], k = 181
     *  Output: [4,5,5]
     *
     *  Input: num = [2,1,5], k = 806
     *  Output: [1,0,2,1]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = [");
        for (j = 0; j < testCase[i].numSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].num[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pAnswer = addToArrayForm(testCase[i].num, testCase[i].numSize, testCase[i].k, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
