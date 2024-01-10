#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATH (1)
#define BRUTE_FORCE (1)
int addDigits(int num) {
    int retVal = 0;

#if (MATH)
    printf("MATH\n");

    /* https://en.wikipedia.org/wiki/Digital_root
     *  abcd
     *  = a * 1000 + b * 100 + c * 10 + d
     *  = a * (999 + 1) + b * (99 + 1) + c * (9 + 1) + d
     *  = (a * 999 + b * 99 + c * 9) + (a + b + c + d)
     */
    if (num != 0) {
        retVal = num % 9;
        if (retVal == 0) {
            retVal = 9;
        }
    }
#elif (BRUTE_FORCE)
    printf("BRUTE_FORCE\n");

    retVal = num;
    while (num >= 10) {
        retVal = 0;
        int tmp = num;
        while (tmp > 0) {
            retVal += (tmp % 10);
            tmp /= 10;
        }
        num = retVal;
    }
#endif

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int num;
    } testCase[] = {{38}, {0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = 38
     *  Output: 2
     *
     *  Input: num = 0
     *  Output: 0
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = %d\n", testCase[i].num);

        answer = addDigits(testCase[i].num);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
