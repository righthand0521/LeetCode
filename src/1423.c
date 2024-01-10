#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxScore(int* cardPoints, int cardPointsSize, int k) {
    int retVal = 0;

    /* maximum sum of k elements that take one card from the beginning or from the end of the row
     * => minimum sum of n-k continuously elements
     *
     *  +---------------------------+
     *  | 1 | 2 | 3 | 4 | 5 | 6 | 1 |
     *  +---------------------------+
     *  |->minsum(n-k)<-|
     *      |->minsum(n-k)<-|
     *          |->minsum(n-k)<-|
     *              |->minsum(n-k)<-|
     */
    int windowSum = 0;
    int windowSize = cardPointsSize - k;
    int i;
    for (i = 0; i < windowSize; ++i) {
        windowSum += cardPoints[i];
    }

    int totalSum = windowSum;
    int minSum = windowSum;
    for (i = windowSize; i < cardPointsSize; ++i) {
        totalSum += cardPoints[i];

        windowSum += (cardPoints[i] - cardPoints[i - windowSize]);
        minSum = fmin(minSum, windowSum);
    }
    retVal = totalSum - minSum;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int cardPoints[MAX_SIZE];
        int cardPointsSize;
        int k;
    } testCase[] = {{{1, 2, 3, 4, 5, 6, 1}, 7, 3}, {{2, 2, 2}, 3, 2}, {{9, 7, 7, 9, 7, 7, 9}, 7, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: target = [");
        for (j = 0; j < testCase[i].cardPointsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].cardPoints[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maxScore(testCase[i].cardPoints, testCase[i].cardPointsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
