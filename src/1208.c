#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int equalSubstring(char* s, char* t, int maxCost) {
    int retVal = 0;

    int sSize = strlen(s);

    int cost = 0;
    int start = 0;
    int end = 0;
    for (end = 0; end < sSize; ++end) {
        cost += abs(s[end] - t[end]);
        while (cost > maxCost) {
            cost -= abs(s[start] - t[start]);
            start += 1;
        }
        retVal = fmax(retVal, end - start + 1);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        char t[MAX_SIZE];
        int maxCost;
    } testCase[] = {{"abcd", "bcdf", 3}, {"abcd", "cdef", 3}, {"abcd", "acde", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abcd", t = "bcdf", maxCost = 3
     *  Output: 3
     *
     *  Input: s = "abcd", t = "cdef", maxCost = 3
     *  Output: 1
     *
     *  Input: s = "abcd", t = "acde", maxCost = 0
     *  Output: 1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = \"%s\", maxCost = %d\n", testCase[i].s, testCase[i].t, testCase[i].maxCost);

        answer = equalSubstring(testCase[i].s, testCase[i].t, testCase[i].maxCost);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
