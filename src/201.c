#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rangeBitwiseAnd(int left, int right) {
    int retVal = 0;

    while (left < right) {
        right = right & (right - 1);
    }
    retVal = left & right;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_NUMSSIZE 1024
    struct testCaseType {
        int left;
        int right;
    } testCase[] = {{5, 7}, {0, 0}, {1, 2147483647}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

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
