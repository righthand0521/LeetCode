#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int makeTheIntegerZero(int num1, int num2) {
    int retVal = -1;

    int k = 1;
    while (1) {
        long long x = (long long)num1 - (long long)num2 * k;
        if (x < k) {
            break;
        } else if (k >= __builtin_popcountll(x)) {
            retVal = k;
            break;
        }
        k++;
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int num1;
        int num2;
    } testCase[] = {{3, -2}, {5, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num1 = 3, num2 = -2
     *  Output: 3
     *
     *  Input: num1 = 5, num2 = 7
     *  Output: -1
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num1 = %d, num2 = %d\n", testCase[i].num1, testCase[i].num2);

        answer = makeTheIntegerZero(testCase[i].num1, testCase[i].num2);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
