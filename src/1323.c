#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximum69Number(int num) {
    int retVal = num;

    int add = 0;
    int multiplier = 1;
    int mod;
    while (num > 0) {
        mod = num % 10;
        if (mod == 6) {
            add = 3 * multiplier;
        }

        num -= mod;
        num /= 10;
        multiplier *= 10;
    }
    retVal += add;

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int num;
    } testCase[] = {{9669}, {9996}, {9999}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = 9669
     *  Output: 9969
     *
     *  Input: num = 9996
     *  Output: 9999
     *
     *  Input: num = 9999
     *  Output: 9999
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = %d\n", testCase[i].num);

        answer = maximum69Number(testCase[i].num);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
