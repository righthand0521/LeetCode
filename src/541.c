#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reverseStr(char* s, int k) {
    char* pRetVal = s;

    int sSize = strlen(s);
    char tmp;
    int left, right;
    int i;
    for (i = 0; i < sSize; i += 2 * k) {
        left = i;
        right = fmin(i + k, sSize) - 1;
        while (left < right) {
            tmp = s[left];
            s[left++] = s[right];
            s[right--] = tmp;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char s[MAX_SIZE];
        int k;
    } testCase[] = {{"abcdefg", 2}, {"abcd", 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abcdefg", k = 2
     *  Output: "bacdfeg"
     *
     *  Input: s = "abcd", k = 2
     *  Output: "bacd"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        pAnswer = reverseStr(testCase[i].s, testCase[i].k);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
