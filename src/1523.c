#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countOdds(int low, int high) {
    int retVal = 0;

    int range = high - low + 1;
    retVal = range / 2;
    if ((range % 2) == 1) {
        retVal = (((low % 2) == 1) || ((high % 2) == 1)) ? retVal + 1 : retVal;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int low;
        int high;
    } testCase[] = {{3, 7}, {8, 10}, {1, 1}, {1, 2}, {2, 2}, {2, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: low = 3, high = 7
     *  Output: 3
     *
     *  Input: low = 8, high = 10
     *  Output: 1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: low = %d, high = %d\n", testCase[i].low, testCase[i].high);

        answer = countOdds(testCase[i].low, testCase[i].high);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
