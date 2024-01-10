#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareChar(const void* c1, const void* c2) {
    // ascending order
    return (*(char*)c1 - *(char*)c2);
}
char* orderlyQueue(char* s, int k) {
    char* pRetVal = NULL;

    int len = strlen(s);
    int returnSize = (len + 1) * sizeof(char);
    pRetVal = (char*)malloc(returnSize);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, returnSize);
    snprintf(pRetVal, returnSize, "%s", s);

    // k>=2: Bubble Sort Concept? it could get the optimal solution(ascending order)
    if (k > 1) {
        qsort(pRetVal, len, sizeof(char), compareChar);
        return pRetVal;
    }

    // k = 1: rotate the whole string to return the lexicographically smallest string
    char tmp;
    int i;
    for (i = 0; i < len; ++i) {
        tmp = s[0];
        memmove(s, &(s[1]), len - 1);
        s[len - 1] = tmp;
        if (strcmp(pRetVal, s) > 0) {
            memset(pRetVal, 0, returnSize);
            snprintf(pRetVal, returnSize, "%s", s);
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* s;
        int k;
    } testCase[] = {{"cba", 1}, {"baaca", 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pString = NULL;
    int len;
    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        len = strlen(testCase[i].s) + 1;
        pString = (char*)malloc(len * sizeof(char));
        if (pString == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        memset(pString, 0, (len * sizeof(char)));
        memcpy(pString, testCase[i].s, (len * sizeof(char)));
        pAnswer = orderlyQueue(pString, testCase[i].k);
        printf("Output: %s\n", pAnswer);

        printf("\n");

        if (pString) {
            free(pString);
            pString = NULL;
        }

        if (pAnswer) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
