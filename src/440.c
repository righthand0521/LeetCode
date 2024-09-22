#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// To count how many numbers exist between prefix1 and prefix2
int countSteps(int n, long prefix1, long prefix2) {
    int retVal = 0;

    while (prefix1 <= n) {
        retVal += fmin((long)(n + 1), prefix2) - prefix1;
        prefix1 *= 10;
        prefix2 *= 10;
    }

    return retVal;
}
int findKthNumber(int n, int k) {
    int retVal = 1;

    int step;
    k--;
    while (k > 0) {
        step = countSteps(n, retVal, retVal + 1);

        // If the steps are less than or equal to k, we skip this prefix's subtree
        if (step <= k) {
            // Move to the next prefix and decrease k by the number of steps we skip
            retVal++;
            k -= step;
        } else {
            // Move to the next level of the tree and decrement k by 1
            retVal *= 10;
            k--;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
        int k;
    } testCase[] = {{13, 2}, {1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 13, k = 2
     *  Output: 10
     *
     *  Input: n = 1, k = 1
     *  Output: 1
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d\n", testCase[i].n, testCase[i].k);

        answer = findKthNumber(testCase[i].n, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
