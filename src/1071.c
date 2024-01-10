#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int dividend, int divisor) {
    int remainder;
    while (divisor != 0) {
        remainder = dividend % divisor;
        dividend = divisor;
        divisor = remainder;
    }

    return dividend;
}
char* gcdOfStrings(char* str1, char* str2) {
    char* pRetVal = NULL;

    /* Math: Greatest Common Divisor
     *  if str1 and str2 have Greatest Common Divisor of Strings
     *  let str1 = m * (substr), str2 = n * (substr)
     *  => str1 + str2 = m * (substr) + n * (substr) = (m + n)(substr)
     *  => str2 + str1 = n * (substr) + m * (substr) = (n + m)(substr)
     *  => str1 + str2 = str2 + str1
     *  let lenStr1 = m * lenSubstr, lenStr2 = n * lenSubstr
     *  => gcd(lenStr1, lenStr2) = lenSubstr
     *  Hence, str1 and str2 Greatest Common Divisor of Strings is str1[0:lenSubstr] or str2[0:lenSubstr]
     */
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int gcdLen = gcd(len1, len2);
    pRetVal = (char*)calloc(gcdLen + 1, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    char buf1[len1 + len2 + 1];
    memset(buf1, 0, sizeof(buf1));
    snprintf(buf1, sizeof(buf1), "%s%s", str1, str2);
    char buf2[len1 + len2 + 1];
    memset(buf2, 0, sizeof(buf1));
    snprintf(buf2, sizeof(buf2), "%s%s", str2, str1);
    if (strcmp(buf1, buf2) != 0) {
        return pRetVal;
    }
    memcpy(pRetVal, str1, gcdLen);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char str1[MAX_SIZE];
        char str2[MAX_SIZE];
    } testCase[] = {{"ABCABC", "ABC"},
                    {"ABABAB", "ABAB"},
                    {"LEET", "CODE"},
                    {"TAUXXTAUXXTAUXXTAUXXTAUXX", "TAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXX"},
                    {"ABABCCABAB", "ABAB"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: str1 = "ABCABC", str2 = "ABC"
     *  Output: "ABC"
     *
     *  Input: str1 = "ABABAB", str2 = "ABAB"
     *  Output: "AB"
     *
     *  Input: str1 = "LEET", str2 = "CODE"
     *  Output: ""
     *
     *  Input: str1 = "TAUXXTAUXXTAUXXTAUXXTAUXX", str2 = "TAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXX"
     *  Output: "TAUXX"
     *
     *  Input: str1 = "ABABCCABAB", str2 = "ABAB"
     *  Output: ""
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: str1 = \"%s\", str2 = \"%s\"\n", testCase[i].str1, testCase[i].str2);

        pAnswer = gcdOfStrings(testCase[i].str1, testCase[i].str2);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
