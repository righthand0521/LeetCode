#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/solutions/6457845/python-check-mod2-and-mod5/
int* cal(int a, int mod) {
    int* pRetVal = NULL;

    pRetVal = (int*)calloc(2, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    int count = 0;
    while ((a > 0) && (a % mod == 0)) {
        count += 1;
        a /= mod;
    }
    pRetVal[0] = a % mod;
    pRetVal[1] = count;

    return pRetVal;
}
bool test(char* s, int mod) {
    bool retVal = false;

    int sSize = strlen(s);

    int* pCalResult = NULL;
    long long res = 0;
    long long r = 1;
    int c = 0;
    for (int i = 0; i < sSize - 1; ++i) {
        if (c == 0) {
            res += (r * ((s[i] - '0') - (s[i + 1] - '0')));
        }

        pCalResult = cal(sSize - 2 - i, mod);
        if (pCalResult == NULL) {
            return retVal;
        }
        r = r * pCalResult[0] % mod;
        c += pCalResult[1];
        free(pCalResult);
        pCalResult = NULL;

        pCalResult = cal(i + 1, mod);
        if (pCalResult == NULL) {
            return retVal;
        }
        r = r * (long long)(pow(pCalResult[0], mod - 2)) % mod;
        c -= pCalResult[1];
        free(pCalResult);
        pCalResult = NULL;
    }

    retVal = (res % mod == 0);

    return retVal;
}
bool hasSameDigits(char* s) {
    bool retVal = true;

    retVal = test(s, 2) && test(s, 5);

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"3902"}, {"34789"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "3902"
     *  Output: true
     *
     *  Input: s = "34789"
     *  Output: false
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = hasSameDigits(testCase[i].s);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
