#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool judgeSquareSum(int c) {
    bool retVal = false;

    long sum;
    long left = 0;
    long right = (int)sqrt(c);
    while (left <= right) {
        sum = (left * left) + (right * right);
        if (sum == c) {
            retVal = true;
            break;
        } else if (sum > c) {
            right--;
        } else {
            left++;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int c;
    } testCase[] = {{5}, {3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: c = 5
     *  Output: true
     *
     *  Input: c = 3
     *  Output: false
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: c = %d\n", testCase[i].c);

        answer = judgeSquareSum(testCase[i].c);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
