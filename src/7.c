#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reverse(int x) {
    int retVal = 0;

    long long reverseSum = 0;
    while (x != 0) {
        reverseSum = (reverseSum * 10) + (x % 10);
        x /= 10;
    }

    // If reversing x causes the value to go outside the signed 32 - bit integer range[-2 ^ 31, 2 ^ 31 - 1],
    // then return 0.
    if ((reverseSum < INT_MAX) && (reverseSum > INT_MIN)) {
        retVal = reverseSum;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int x;
    } testCase[] = {{123}, {-123}, {120}, {INT_MAX}, {INT_MIN}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: x = 123
     *  Output: 321
     *
     *  Input: x = -123
     *  Output: -321
     *
     *  Input: x = 120
     *  Output: 21
     *
     *  Input: x = 2147483647
     *  Output: 0
     *
     *  Input: x = -2147483648
     *  Output: 0
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: x = %d\n", testCase[i].x);

        answer = reverse(testCase[i].x);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
