#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minBitFlips(int start, int goal) {
    int retVal = 0;

    int i;
    for (i = 0; i < 32; ++i) {
        retVal += (start & 1) ^ (goal & 1);
        start >>= 1;
        goal >>= 1;
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int start;
        int goal;
    } testCase[] = {{10, 7}, {3, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: start = 10, goal = 7
     *  Output: 3
     *
     *  Input: start = 3, goal = 4
     *  Output: 3
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: start = %d, goal = %d\n", testCase[i].start, testCase[i].goal);

        answer = minBitFlips(testCase[i].start, testCase[i].goal);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
