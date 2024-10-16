#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestDiverseString(int a, int b, int c) {
    char* pRetVal = NULL;

    int returnSize = a + b + c + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    int idx = 0;
    int curra = 0;
    int currb = 0;
    int currc = 0;
    int totalIterations = a + b + c;
    int i;
    for (i = 0; i < totalIterations; i++) {
        if (a >= b && a >= c && curra != 2) {
            pRetVal[idx++] = 'a';
            a--;
            curra++;
            currb = 0;
            currc = 0;
        } else if (a > 0 && (currb == 2 || currc == 2)) {
            pRetVal[idx++] = 'a';
            a--;
            curra++;
            currb = 0;
            currc = 0;
        } else if (b >= a && b >= c && currb != 2) {
            pRetVal[idx++] = 'b';
            b--;
            currb++;
            curra = 0;
            currc = 0;
        } else if (b > 0 && (currc == 2 || curra == 2)) {
            pRetVal[idx++] = 'b';
            b--;
            currb++;
            curra = 0;
            currc = 0;
        } else if (c >= a && c >= b && currc != 2) {
            pRetVal[idx++] = 'c';
            c--;
            currc++;
            curra = 0;
            currb = 0;
        } else if (c > 0 && (curra == 2 || currb == 2)) {
            pRetVal[idx++] = 'c';
            c--;
            currc++;
            curra = 0;
            currb = 0;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int a;
        int b;
        int c;
    } testCase[] = {{1, 1, 7}, {7, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: a = 1, b = 1, c = 7
     *  Output: "ccaccbcc"
     *
     *  Input: a = 7, b = 1, c = 0
     *  Output: "aabaa"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: a  = %d, b  = %d, c  = %d\n", testCase[i].a, testCase[i].b, testCase[i].c);

        pAnswer = longestDiverseString(testCase[i].a, testCase[i].b, testCase[i].c);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
