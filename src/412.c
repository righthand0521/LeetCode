#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** fizzBuzz(int n, int* returnSize) {
    char** pRetVal;

#define ANSWER3 "Fizz"
#define ANSWER5 "Buzz"
    *returnSize = n;
    pRetVal = (char**)malloc((*returnSize) * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        *returnSize = 0;
        return pRetVal;
    }

    int len = 12;
    int i;
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = (char*)malloc(len * sizeof(char));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            break;
        }
        memset(pRetVal[i], 0, len * sizeof(char));
        if ((((i + 1) % 3) == 0) && (((i + 1) % 5) == 0)) {
            snprintf(pRetVal[i], len, "%s%s", ANSWER3, ANSWER5);
        } else if (((i + 1) % 3) == 0) {
            snprintf(pRetVal[i], len, "%s", ANSWER3);
        } else if (((i + 1) % 5) == 0) {
            snprintf(pRetVal[i], len, "%s", ANSWER5);
        } else {
            snprintf(pRetVal[i], len, "%d", (i + 1));
        }
    }
    if (i != (*returnSize)) {
        *returnSize = i;
        for (i = 0; i < *returnSize; ++i) {
            if (pRetVal[i] == NULL) {
                continue;
            }
            free(pRetVal[i]);
        }
        free(pRetVal);
        pRetVal = NULL;
        *returnSize = 0;
        return pRetVal;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int returnSize;
    } testCase[] = {{3, 0}, {5, 0}, {15, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = fizzBuzz(testCase[i].n, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            if (pAnswer[j]) {
                free(pAnswer[j]);
            }
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
