#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long halfToPalindrome(long left, bool even) {
    long retVal = left;

    if (even == false) {
        left = left / 10;
    }

    while (left > 0) {
        retVal = retVal * 10 + left % 10;
        left /= 10;
    }

    return retVal;
}
char* nearestPalindromic(char* n) {
    char* pRetVal = NULL;

    int nSize = strlen(n);

    int returnSize = nSize + 4;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (nSize * sizeof(char)));

    int i;
    int firstHalfSize = (nSize % 2 == 0) ? (nSize / 2 - 1) : (nSize / 2);
    long firstHalf = 0;
    for (i = 0; i < firstHalfSize + 1; ++i) {
        firstHalf = (long)(10 * firstHalf) + (long)(n[i] - '0');
    }

    /* Generate possible palindromic candidates:
     *  1. Create a palindrome by mirroring the first half.
     *  2. Create a palindrome by mirroring the first half incremented by 1.
     *  3. Create a palindrome by mirroring the first half decremented by 1.
     *  4. Handle edge cases by considering palindromes of the
     *     form 999...and 100...001 (smallest and largest n-digit palindromes).
     */
    int candidatesSize = 5;
    long candidates[candidatesSize];
    candidates[0] = halfToPalindrome(firstHalf, nSize % 2 == 0);
    candidates[1] = halfToPalindrome(firstHalf + 1, nSize % 2 == 0);
    candidates[2] = halfToPalindrome(firstHalf - 1, nSize % 2 == 0);
    candidates[3] = (long)pow(10, nSize - 1) - 1;
    candidates[4] = (long)pow(10, nSize) + 1;

    long diff = LONG_MAX;
    long res = 0;
    long nl = atol(n);
    for (i = 0; i < candidatesSize; ++i) {
        if (candidates[i] == nl) {
            continue;
        }

        if (labs(candidates[i] - nl) < diff) {
            diff = labs(candidates[i] - nl);
            res = candidates[i];
        } else if (labs(candidates[i] - nl) == diff) {
            res = fmin(res, candidates[i]);
        }
    }

    char buf[returnSize];
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "%ld", res);
    memcpy(pRetVal, buf, returnSize);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        char n[MAX_SIZE];
    } testCase[] = {{"123"}, {"1"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = "123"
     *  Output: "121"
     *
     *  Input: n = "1"
     *  Output: "0"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = \"%s\"\n", testCase[i].n);

        pAnswer = nearestPalindromic(testCase[i].n);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
