#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int num1, int num2) {
    int retVal = 0;

    int temp;
    while (num2 != 0) {
        temp = num1;
        num1 = num2;
        num2 = temp % num2;
    }
    retVal = num1;

    return retVal;
}
void add(char* t, int n, int a, int start) {
    int minVal = 10;
    int times = 0;
    int added;
    for (int i = 0; i < 10; i++) {
        added = ((t[start] - '0') + i * a) % 10;
        if (added < minVal) {
            minVal = added;
            times = i;
        }
    }

    for (int i = start; i < n; i += 2) {
        t[i] = '0' + ((t[i] - '0') + times * a) % 10;
    }
}
char* findLexSmallestString(char* s, int a, int b) {
    char* pRetVal = NULL;

    int sSize = strlen(s);

    int returnSize = sSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));
    snprintf(pRetVal, returnSize, "%s", s);

    char str[2 * sSize + 1];
    memset(str, 0, sizeof(str));
    snprintf(str, sizeof(str), "%s%s", s, s);
    char t[sSize + 1];
    int g = gcd(b, sSize);
    for (int i = 0; i < sSize; i += g) {
        memset(t, 0, sizeof(t));
        snprintf(t, sizeof(t), "%s", str + i);
        add(t, sSize, a, 1);

        if (b % 2 != 0) {
            add(t, sSize, a, 0);
        }

        if (strcmp(t, pRetVal) < 0) {
            memset(pRetVal, 0, (returnSize * sizeof(char)));
            snprintf(pRetVal, returnSize, "%s", t);
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* s;
        int a;
        int b;
    } testCase[] = {{"5525", 9, 2}, {"74", 5, 1}, {"0011", 4, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "5525", a = 9, b = 2
     *  Output: "2050"
     *
     *  Input: s = "74", a = 5, b = 1
     *  Output: "24"
     *
     *  Input: s = "0011", a = 4, b = 2
     *  Output: "0011"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", a = %d, b = %d\n", testCase[i].s, testCase[i].a, testCase[i].b);

        pAnswer = findLexSmallestString(testCase[i].s, testCase[i].a, testCase[i].b);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        if (pAnswer) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
