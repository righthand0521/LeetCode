#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *addBinary(char *a, char *b) {
    char *pRetVal = NULL;

    //
    int lenA = strlen(a) - 1;
    int lenB = strlen(b) - 1;
    int len = (lenA > lenB ? (lenA + 1) : (lenB + 1)) + 2;
    char buf[len];
    memset(buf, 0, sizeof(buf));
    int idx = len - 2;

    //
    int sum;
    int carry = 0;
    while ((lenA >= 0) && (lenB >= 0)) {
        sum = (a[lenA--] - '0') + (b[lenB--] - '0') + carry;
        carry = (sum > 1 ? 1 : 0);
        buf[idx--] = (sum % 2) + '0';
    }
    while (lenA >= 0) {
        sum = (a[lenA--] - '0') + carry;
        carry = (sum > 1 ? 1 : 0);
        buf[idx--] = (sum % 2) + '0';
    }
    while (lenB >= 0) {
        sum = (b[lenB--] - '0') + carry;
        carry = (sum > 1 ? 1 : 0);
        buf[idx--] = (sum % 2) + '0';
    }
    if (carry == 1) {
        buf[idx--] = carry + '0';
    }

    //
    pRetVal = (char *)calloc((len - 1 - idx), sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    memcpy(pRetVal, buf + 1 + idx, ((len - 1 - idx) * sizeof(char)));

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char a[MAX_SIZE];
        char b[MAX_SIZE];
    } testCase[] = {{"11", "1"}, {"1010", "1011"}, {"0", "0"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: a = "11", b = "1"
     *  Output: "100"
     *
     *  Input: a = "1010", b = "1011"
     *  Output: "10101"
     */

    char *pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: a = \"%s\", b = \"%s\"\n", testCase[i].a, testCase[i].b);

        pAnswer = addBinary(testCase[i].a, testCase[i].b);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
