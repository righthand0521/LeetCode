#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double averageWaitingTime(int** customers, int customersSize, int* customersColSize) {
    double retVal = 0;

    int nextIdleTime = 0;
    double netWaitTime = 0;
    int i;
    for (i = 0; i < customersSize; ++i) {
        nextIdleTime = fmax(customers[i][0], nextIdleTime) + customers[i][1];
        netWaitTime += (nextIdleTime - customers[i][0]);
    }
    retVal = netWaitTime / customersSize;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int customers[MAX_SIZE][2];
        int customersSize;
        int customersColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2}, {2, 5}, {4, 3}}, 3, {2, 2, 2}}, {{{5, 2}, {5, 4}, {10, 3}, {20, 1}}, 4, {2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: customers = [[1,2],[2,5],[4,3]]
     *  Output: 5.00000
     *
     *  Input: customers = [[5,2],[5,4],[10,3],[20,1]]
     *  Output: 3.25000
     */

    int** pCustomers = NULL;
    double answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("customers = [");
        for (j = 0; j < testCase[i].customersSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].customersColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].customers[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pCustomers = (int**)malloc(testCase[i].customersSize * sizeof(int*));
        if (pCustomers == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pCustomers, 0, testCase[i].customersSize * sizeof(int*));
        for (j = 0; j < testCase[i].customersSize; ++j) {
            pCustomers[j] = (int*)malloc(testCase[i].customersColSize[j] * sizeof(int));
            if (pCustomers[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pCustomers[k]);
                    pCustomers[k] = NULL;
                }
                free(pCustomers);
                pCustomers = NULL;
            }
            memset(pCustomers[j], 0, (testCase[i].customersColSize[j] * sizeof(int)));
            memcpy(pCustomers[j], testCase[i].customers[j], (testCase[i].customersColSize[j] * sizeof(int)));
        }
        answer = averageWaitingTime(pCustomers, testCase[i].customersSize, testCase[i].customersColSize);
        printf("Output: %.5f\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].customersSize; ++j) {
            free(pCustomers[j]);
            pCustomers[j] = NULL;
        }
        free(pCustomers);
        pCustomers = NULL;
    }

    return EXIT_SUCCESS;
}
