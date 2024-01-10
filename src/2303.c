#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double calculateTax(int** brackets, int bracketsSize, int* bracketsColSize, int income) {
    double retVal = 0;

    int lower = 0;
    int upper;
    int percent;
    int i;
    for (i = 0; i < bracketsSize; ++i) {
        upper = brackets[i][0];
        percent = brackets[i][1];
        retVal += ((double)((fmin(income, upper) - lower) * percent) / 100);
        lower = upper;

        if (income < brackets[i][0]) {
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int brackets[MAX_SIZE][2];
        int bracketsSize;
        int bracketsColSize[MAX_SIZE];
        int income;
    } testCase[] = {{{{3, 50}, {7, 10}, {12, 25}}, 3, {2, 2, 2}, 10},
                    {{{1, 0}, {4, 25}, {5, 50}}, 3, {2, 2, 2}, 2},
                    {{{2, 50}}, 1, {2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pBrackets = NULL;
    double answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: brackets = [");
        for (j = 0; j < testCase[i].bracketsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].bracketsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].brackets[j][k]);
            }
            printf("]");
        }
        printf("], income = %d\n", testCase[i].income);

        pBrackets = (int**)malloc(testCase[i].bracketsSize * sizeof(int*));
        if (pBrackets == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].bracketsSize; ++j) {
            pBrackets[j] = (int*)malloc(testCase[i].bracketsColSize[j] * sizeof(int));
            if (pBrackets[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pBrackets[k]) {
                        free(pBrackets[k]);
                    }
                }
                free(pBrackets);
                pBrackets = NULL;
                return EXIT_FAILURE;
            }
            memset(pBrackets[j], 0, testCase[i].bracketsColSize[j] * sizeof(int));
            memcpy(pBrackets[j], testCase[i].brackets[j], testCase[i].bracketsColSize[j] * sizeof(int));
        }

        answer = calculateTax(pBrackets, testCase[i].bracketsSize, testCase[i].bracketsColSize, testCase[i].income);
        printf("Output: %f\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].bracketsSize; ++j) {
            if (pBrackets[j]) {
                free(pBrackets[j]);
                pBrackets[j] = NULL;
            }
        }
        free(pBrackets);
        pBrackets = NULL;
    }

    return EXIT_SUCCESS;
}
