#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
char* getHint(char* secret, char* guess) {
    char* pRetVal = NULL;

#define MAX_INPUT (2)
#define MAX_DIGITS (10)
    int Record[MAX_INPUT * MAX_DIGITS] = {0};
    int countA = 0;
    while (*secret) {
        if ((*secret) == (*guess)) {
            ++countA;
        } else {
            Record[(unsigned char)(*secret - '0')]++;
            Record[(unsigned char)(*guess - '0') + MAX_DIGITS]++;
        }
        ++secret;
        ++guess;
    }

    int countB = 0;
    int i;
    for (i = 0; i < MAX_DIGITS; ++i) {
        countB += MIN(Record[i], Record[i + MAX_DIGITS]);
    }

#define MAX_RETURN_SIZE (16)
    int returnSize = MAX_RETURN_SIZE * sizeof(char);
    pRetVal = (char*)malloc(returnSize);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, returnSize);
    snprintf(pRetVal, returnSize, "%dA%dB", countA, countB);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char secret[MAX_SIZE];
        char guess[MAX_SIZE];
    } testCase[] = {{"1807", "7810"}, {"1123", "0111"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: secret = \"%s\", guess = \"%s\"\n", testCase[i].secret, testCase[i].guess);

        pAnswer = getHint(testCase[i].secret, testCase[i].guess);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
