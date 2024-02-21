#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rangeBitwiseAnd(int left, int right) {
    int retVal = 0;

    int shift = 0;
    while (left < right) {
        left >>= 1;
        right >>= 1;
        shift += 1;
    }
    retVal = left << shift;

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int left;
        int right;
    } testCase[] = {{5, 7}, {0, 0}, {1, 2147483647}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: left = 5, right = 7
     *  Output: 4
     *
     *  Input: left = 0, right = 0
     *  Output: 0
     *
     *  Input: left = 1, right = 2147483647
     *  Output: 0
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: left = %d, right = %d\n", testCase[i].left, testCase[i].right);

        answer = rangeBitwiseAnd(testCase[i].left, testCase[i].right);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
