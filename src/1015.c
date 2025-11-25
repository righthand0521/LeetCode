#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int smallestRepunitDivByK(int k) {
    int retVal = -1;

    int remainder = 0;
    for (int nSize = 1; nSize <= k; ++nSize) {
        remainder = (remainder * 10 + 1) % k;
        if (remainder == 0) {
            retVal = nSize;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int k;
    } testCase[] = {{1}, {2}, {3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: k = 1
     *  Output: 1
     *
     *  Input: k = 2
     *  Output: -1
     *
     *  Input: k = 3
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: k = %d\n", testCase[i].k);

        answer = smallestRepunitDivByK(testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
