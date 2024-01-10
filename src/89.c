#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* grayCode(int n, int* returnSize) {
    int* pRetVal = NULL;

    *returnSize = (1 << n);
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (*returnSize) * sizeof(int));

    int shift;
    int tmp;
    int i = 0;
    /* 直接排列
     *  以二進制為0值的格雷碼為第零項，
     *  第一項改變最右邊的位元，
     *  第二項改變右起第一個為1的位元的左邊位元，
     *  第三、四項方法同第一、二項，如此反覆，即可排列出n個位元的格雷碼。
     *
     *  https://zh.wikipedia.org/wiki/%E6%A0%BC%E9%9B%B7%E7%A0%81
     */
    while (i < *returnSize) {
        pRetVal[i + 1] = pRetVal[i] ^ 1;
        ++i;

        if ((i + 1) >= (*returnSize)) {
            break;
        }
        shift = 0;
        tmp = pRetVal[i];
        while ((tmp & 1) == 0) {
            ++shift;
            tmp >>= 1;
        }
        ++shift;
        pRetVal[i + 1] = (1 << shift) ^ pRetVal[i];
        ++i;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int returnSize;
    } testCase[] = {{2, 0}, {1, 0}, {3, 0}, {4, 0}, {5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = grayCode(testCase[i].n, &testCase[i].returnSize);
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
