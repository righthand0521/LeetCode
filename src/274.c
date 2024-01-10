#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hIndex(int* citations, int citationsSize) {
    int retVal = 0;

    int countMap[citationsSize + 1];
    memset(countMap, 0, sizeof(countMap));

    int cited = 0;
    int i;
    for (i = 0; i < citationsSize; ++i) {
        if (citations[i] > citationsSize) {
            cited++;
        } else {
            countMap[citations[i]]++;
        }
    }

    for (i = citationsSize; i >= 0; --i) {
        cited += countMap[i];
        if (cited >= i) {
            retVal = i;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int citations[MAX_SIZE];
        int citationsSize;
    } testCase[] = {{{3, 0, 6, 1, 5}, 5}, {{1, 3, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: citations = [3,0,6,1,5]
     *  Output: 3
     *
     *  Input: citations = [1,3,1]
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: citations = [");
        for (j = 0; j < testCase[i].citationsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].citations[j]);
        }
        printf("]\n");

        answer = hIndex(testCase[i].citations, testCase[i].citationsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
