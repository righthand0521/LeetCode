#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int findContentChildren(int* g, int gSize, int* s, int sSize) {
    int retVal = 0;

    qsort(g, gSize, sizeof(int), compareInteger);
    int gIdx = 0;

    qsort(s, sSize, sizeof(int), compareInteger);
    int sIdx = 0;

    while ((gIdx < gSize) && (sIdx < sSize)) {
        if (g[gIdx] <= s[sIdx]) {
            ++gIdx;
            ++retVal;
        }
        ++sIdx;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (30000)
    struct testCaseType {
        int g[MAX_SIZE];
        int gSize;
        int s[MAX_SIZE];
        int sSize;
    } testCase[] = {{{1, 2, 3}, 3, {1, 1}, 2}, {{1, 2}, 2, {1, 2, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: g = [1,2,3], s = [1,1]
     *  Output: 1
     *
     *  Input: g = [1,2], s = [1,2,3]
     *  Output: 2
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: g = [");
        for (j = 0; j < testCase[i].gSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].g[j]);
        }
        printf("], s = [");
        for (j = 0; j < testCase[i].sSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].s[j]);
        }
        printf("]\n");

        answer = findContentChildren(testCase[i].g, testCase[i].gSize, testCase[i].s, testCase[i].sSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
