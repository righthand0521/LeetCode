#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int n, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = n + 1;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    int i;
    for (i = 1; i < (*returnSize); ++i) {
#if (1)  // O(n)
        /* f[i] = f[i/2] + i%2
         *  pRetVal[000] = 0
         *  pRetVal[001] = pRetVal[00] + (1%2) = 0 + 1 = 1
         *  pRetVal[010] = pRetVal[01] + (2%2) = 1 + 0 = 1
         *  pRetVal[011] = pRetVal[01] + (3%2) = 1 + 1 = 2
         *  pRetVal[100] = pRetVal[10] + (4%2) = 1 + 0 = 1
         *  pRetVal[101] = pRetVal[10] + (5%2) = 1 + 1 = 2
         *  pRetVal[110] = pRetVal[11] + (6%2) = 2 + 0 = 2
         *  pRetVal[111] = pRetVal[11] + (7%2) = 2 + 1 = 3
         */
        pRetVal[i] = pRetVal[i >> 1] + (i & 1);
#else  // O(n log n)
        unsigned int tmp = i;
        while (tmp) {
            if (tmp & 1) {
                pRetVal[i]++;
            }
            tmp >>= 1;
        }
#endif
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int returnSize;
    } testCase[] = {{2, 0}, {5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2
     *  Output: [0,1,1]
     *
     *  Input: n = 5
     *  Output: [0,1,1,2,1,2]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = countBits(testCase[i].n, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
