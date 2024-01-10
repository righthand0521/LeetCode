#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if (1)  // pre-defined API
int pick;
int guess(int num) {
    int retVal = 0;

    if (num > pick) {
        retVal = -1;
    } else if (num < pick) {
        retVal = 1;
    }

    return retVal;
}
#endif
/**
 * Forward declaration of guess API.
 * @param  num  your guess
 * @return      -1 if num is higher than the picked number
 *               1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */
int guessNumber(int n) {
    int retVal = 0;

    int left = 1;
    int right = n;
    int middle, ret;
    while (left <= right) {
        middle = left + ((right - left) / 2);

        ret = guess(middle);
        if (ret == 0) {
            retVal = middle;
            break;
        } else if (ret == -1) {
            right = middle - 1;
        } else if (ret == 1) {
            left = middle + 1;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
        int pick;
    } testCase[] = {{10, 6}, {1, 1}, {2, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 10, pick = 6
     *  Output: 6
     *
     *  Input: n = 1, pick = 1
     *  Output: 1
     *
     *  Input: n = 2, pick = 1
     *  Output: 1
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, pick = %d\n", testCase[i].n, testCase[i].pick);

        pick = testCase[i].pick;
        answer = guessNumber(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
