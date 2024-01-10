#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximumWealth(int** accounts, int accountsSize, int* accountsColSize) {
    int retVal = 0;

    int sum;
    int i, j;
    for (i = 0; i < accountsSize; ++i) {
        sum = 0;
        for (j = 0; j < (*accountsColSize); ++j) {
            sum += accounts[i][j];
        }
        retVal = (retVal > sum) ? retVal : sum;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int accounts[MAX_SIZE][MAX_SIZE];
        int accountsSize;
        int accountsColSize;
    } testCase[] = {
        {{{1, 2, 3}, {3, 2, 1}}, 2, 3}, {{{1, 5}, {7, 3}, {3, 5}}, 3, 2}, {{{2, 8, 7}, {7, 1, 3}, {1, 9, 5}}, 3, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pAccounts = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: accounts = [");
        for (j = 0; j < testCase[i].accountsSize; ++j) {
            printf("[");
            for (k = 0; k < testCase[i].accountsColSize; ++k) {
                printf("%s%d", (j == 0) ? "" : ",", testCase[i].accounts[j][k]);
            }
            printf("]%s", (j == testCase[i].accountsSize - 1) ? "" : ",");
        }
        printf("]\n");

        pAccounts = (int**)malloc(testCase[i].accountsSize * sizeof(int*));
        if (pAccounts == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].accountsSize; ++j) {
            pAccounts[j] = (int*)malloc(testCase[i].accountsColSize * sizeof(int));
            if (pAccounts[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pAccounts[k]) {
                        free(pAccounts[k]);
                    }
                }
                free(pAccounts);
                pAccounts = NULL;
                return EXIT_FAILURE;
            }
            memset(pAccounts[j], 0, testCase[i].accountsColSize * sizeof(int));
            memcpy(pAccounts[j], testCase[i].accounts[j], testCase[i].accountsColSize * sizeof(int));
        }
        answer = maximumWealth(pAccounts, testCase[i].accountsSize, &testCase[i].accountsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (k = 0; k < testCase[i].accountsSize; ++k) {
            if (pAccounts[k]) {
                free(pAccounts[k]);
                pAccounts[k] = NULL;
            }
        }
        free(pAccounts);
        pAccounts = NULL;
    }

    return EXIT_SUCCESS;
}
