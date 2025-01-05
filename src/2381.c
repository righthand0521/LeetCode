#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* shiftingLetters(char* s, int** shifts, int shiftsSize, int* shiftsColSize) {
    char* pRetVal = s;

    int sSize = strlen(s);

    int diffArray[sSize];
    memset(diffArray, 0, sizeof(diffArray));
    for (int i = 0; i < shiftsSize; i++) {
        if (shifts[i][2] == 1) {
            diffArray[shifts[i][0]]++;
            if (shifts[i][1] + 1 < sSize) {
                diffArray[shifts[i][1] + 1]--;
            }
        } else {
            diffArray[shifts[i][0]]--;
            if (shifts[i][1] + 1 < sSize) {
                diffArray[shifts[i][1] + 1]++;
            }
        }
    }

    int numberOfShifts = 0;
    for (int i = 0; i < sSize; i++) {
        numberOfShifts = (numberOfShifts + diffArray[i]) % 26;
        if (numberOfShifts < 0) {
            numberOfShifts += 26;
        }
        pRetVal[i] = 'a' + (s[i] - 'a' + numberOfShifts) % 26;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(5 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
        int shifts[MAX_SIZE][3];
        int shiftsSize;
        int shiftsColSize[MAX_SIZE];
    } testCase[] = {{"abc", {{0, 1, 0}, {1, 2, 1}, {0, 2, 1}}, 3, {3, 3, 3}},
                    {"dztz", {{0, 0, 0}, {1, 1, 1}}, 2, {3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
     *  Output: "ace"
     *
     *  Input: s = "dztz", shifts = [[0,0,0],[1,1,1]]
     *  Output: "catz"
     */

    int** pShifts = NULL;
    char* pAnswer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", shifts = [", testCase[i].s);
        for (j = 0; j < testCase[i].shiftsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].shiftsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].shifts[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pShifts = (int**)malloc(testCase[i].shiftsSize * sizeof(int*));
        if (pShifts == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pShifts, 0, testCase[i].shiftsSize * sizeof(int*));
        for (j = 0; j < testCase[i].shiftsSize; ++j) {
            pShifts[j] = (int*)malloc(testCase[i].shiftsColSize[j] * sizeof(int));
            if (pShifts[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pShifts[k]);
                    pShifts[k] = NULL;
                }
                free(pShifts);
                pShifts = NULL;
            }
            memset(pShifts[j], 0, (testCase[i].shiftsColSize[j] * sizeof(int)));
            memcpy(pShifts[j], testCase[i].shifts[j], (testCase[i].shiftsColSize[j] * sizeof(int)));
        }
        pAnswer = shiftingLetters(testCase[i].s, pShifts, testCase[i].shiftsSize, testCase[i].shiftsColSize);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        for (j = 0; j < testCase[i].shiftsSize; ++j) {
            free(pShifts[j]);
            pShifts[j] = NULL;
        }
        free(pShifts);
        pShifts = NULL;
    }

    return EXIT_SUCCESS;
}
