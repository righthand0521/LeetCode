#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** readBinaryWatch(int turnedOn, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    int maxReturnSize = 12 * 60;  // represent the hours (0-11) and minutes (0-59)
    pRetVal = (char**)malloc(maxReturnSize * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int maxRepresentSize = 6;                          // H:MM\0"
    for (int hours = 0; hours < 12; ++hours) {         // represent the hours (0-11)
        for (int minute = 0; minute < 60; ++minute) {  // represent the minutes (0-59)
            if (__builtin_popcount(hours) + __builtin_popcount(minute) != turnedOn) {
                continue;
            }

            pRetVal[(*returnSize)] = (char*)malloc(maxRepresentSize * sizeof(char));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (maxRepresentSize * sizeof(char)));
            sprintf(pRetVal[(*returnSize)], "%d:%02d", hours, minute);
            (*returnSize)++;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int returnSize;
    } testCase[] = {{1, 0}, {9, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: turnedOn = 1
     *  Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
     *
     *  Input: turnedOn = 9
     *  Output: []
     */

    char** pAnswer = NULL;
    for (int i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = readBinaryWatch(testCase[i].n, &testCase[i].returnSize);
        printf("Output: [");
        for (int j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (int j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
