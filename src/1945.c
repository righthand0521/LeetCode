#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getLucky(char* s, int k) {
    int retVal = 0;

    int sum = 0;
    int translateToInteger = 0;
    while (*s) {
        translateToInteger = *(s++) - 'a' + 1;
        sum += (translateToInteger % 10);
        sum += (translateToInteger / 10);
    }

    retVal = sum;
    int i;
    for (i = 1; i < k; ++i) {
        retVal = 0;
        while (sum > 0) {
            retVal += (sum % 10);
            sum /= 10;
        }
        sum = retVal;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
        int k;
    } testCase[] = {{"iiii", 1}, {"leetcode", 2}, {"zbax", 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "iiii", k = 1
     *  Output: 36
     *
     *  Input: s = "leetcode", k = 2
     *  Output: 6
     *
     *  Input: s = "zbax", k = 2
     *  Output: 8
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        answer = getLucky(testCase[i].s, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
