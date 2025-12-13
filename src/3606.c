#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareString(const void* str1, const void* str2) {
    // ascending order
    return strcmp(*(char**)str1, *(char**)str2);
}
bool check(const char* code, bool isActive) {
    bool retVal = isActive;

    for (int i = 0; code[i] != '\0'; i++) {
        if ((code[i] != '_') && (isalnum(code[i]) == 0)) {
            retVal = false;
            break;
        }
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** validateCoupons(char** code, int codeSize, char** businessLine, int businessLineSize, bool* isActive,
                       int isActiveSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    char* groups[4][codeSize];
    int groupsSize[4] = {0};
    for (int i = 0; i < codeSize; i++) {
        if (strlen(code[i]) <= 0) {
            continue;
        } else if (check(code[i], isActive[i]) == false) {
            continue;
        }

        if (strcmp(businessLine[i], "electronics") == 0) {
            groups[0][groupsSize[0]++] = code[i];
        } else if (strcmp(businessLine[i], "grocery") == 0) {
            groups[1][groupsSize[1]++] = code[i];
        } else if (strcmp(businessLine[i], "pharmacy") == 0) {
            groups[2][groupsSize[2]++] = code[i];
        } else if (strcmp(businessLine[i], "restaurant") == 0) {
            groups[3][groupsSize[3]++] = code[i];
        }
    }

    int totalSize = 0;
    for (int i = 0; i < 4; i++) {
        qsort(groups[i], groupsSize[i], sizeof(char*), compareString);
        totalSize += groupsSize[i];
    }

    pRetVal = malloc(sizeof(char*) * totalSize);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    int pos = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < groupsSize[i]; j++) {
            pRetVal[pos] = malloc(strlen(groups[i][j]) + 1);
            if (pRetVal[pos] == NULL) {
                perror("malloc");
                for (int k = 0; k < pos; k++) {
                    if (pRetVal[k] != NULL) {
                        free(pRetVal[k]);
                    }
                    pRetVal[k] = NULL;
                }
                free(pRetVal);
                pRetVal = NULL;
                return pRetVal;
            }
            strcpy(pRetVal[pos], groups[i][j]);
            pos++;
        }
    }
    (*returnSize) = totalSize;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* code[MAX_SIZE];
        int codeSize;
        char* businessLine[MAX_SIZE];
        int businessLineSize;
        bool isActive[MAX_SIZE];
        int isActiveSize;
        int returnSize;
    } testCase[] = {{{"SAVE20", "", "PHARMA5", "SAVE@20"},
                     4,
                     {"restaurant", "grocery", "pharmacy", "restaurant"},
                     4,
                     {true, true, true, true},
                     4,
                     0},
                    {{"GROCERY15", "ELECTRONICS_50", "DISCOUNT10"},
                     3,
                     {"grocery", "electronics", "invalid"},
                     3,
                     {false, true, true},
                     3,
                     0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: code = ["SAVE20","","PHARMA5","SAVE@20"],
     *         businessLine = ["restaurant","grocery","pharmacy","restaurant"],
     *         isActive = [true,true,true,true]
     *  Output: ["PHARMA5","SAVE20"]
     *
     *  Input: code = ["GROCERY15","ELECTRONICS_50","DISCOUNT10"],
     *         businessLine = ["grocery","electronics","invalid"],
     *         isActive = [false,true,true]
     *  Output: ["ELECTRONICS_50"]
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: code = [");
        for (j = 0; j < testCase[i].codeSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].code[j]);
        }
        printf("], businessLine = [");
        for (j = 0; j < testCase[i].businessLineSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].businessLine[j]);
        }
        printf("], isActive = [");
        for (j = 0; j < testCase[i].isActiveSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", testCase[i].isActive[j] ? "true" : "false");
        }
        printf("]\n");

        pAnswer = validateCoupons(testCase[i].code, testCase[i].codeSize, testCase[i].businessLine,
                                  testCase[i].businessLineSize, testCase[i].isActive, testCase[i].isActiveSize,
                                  &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
