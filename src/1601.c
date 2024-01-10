#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void backtracking(int n, int** requests, int requestsSize, int* requestsColSize, int index, int* building, int* count,
                  int* zero, int* answer) {
    if (index == requestsSize) {
        if ((*zero) == n) {
            (*answer) = fmax((*answer), (*count));
        }
        return;
    }

    backtracking(n, requests, requestsSize, requestsColSize, index + 1, building, count, zero, answer);

    int z = (*zero);
    (*count) += 1;
    int x = requests[index][0];
    int y = requests[index][1];
    (*zero) -= (building[x] == 0);
    building[x] -= 1;
    (*zero) += (building[x] == 0);
    (*zero) -= (building[y] == 0);
    building[y] += 1;
    (*zero) += building[y] == 0;
    backtracking(n, requests, requestsSize, requestsColSize, index + 1, building, count, zero, answer);
    building[y] -= 1;
    building[x] += 1;
    (*count) -= 1;
    (*zero) = z;
}
int maximumRequests(int n, int** requests, int requestsSize, int* requestsColSize) {
    int retVal = 0;

    int building[n];
    memset(building, 0, sizeof(building));
    int count = 0;
    int zero = n;
    backtracking(n, requests, requestsSize, requestsColSize, 0, building, &count, &zero, &retVal);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (16)
    struct testCaseType {
        int n;
        int requests[MAX_SIZE][2];
        int requestsSize;
        int requestsColSize[MAX_SIZE];
    } testCase[] = {{5, {{0, 1}, {1, 0}, {0, 1}, {1, 2}, {2, 0}, {3, 4}}, 6, {2, 2, 2, 2, 2, 2}},
                    {3, {{0, 0}, {1, 2}, {2, 1}}, 3, {2, 2, 2}},
                    {4, {{0, 3}, {3, 1}, {1, 2}, {2, 0}}, 4, {2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, requests = [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]
     *  Output: 5
     *
     *  Input: n = 3, requests = [[0,0],[1,2],[2,1]]
     *  Output: 3
     *
     *  Input: n = 4, requests = [[0,3],[3,1],[1,2],[2,0]]
     *  Output: 4
     */

    int** pRequests = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("n = %d, requests = [", testCase[i].n);
        for (j = 0; j < testCase[i].requestsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].requestsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].requests[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pRequests = (int**)malloc(testCase[i].requestsSize * sizeof(int*));
        if (pRequests == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pRequests, 0, testCase[i].requestsSize * sizeof(int*));
        for (j = 0; j < testCase[i].requestsSize; ++j) {
            pRequests[j] = (int*)malloc(testCase[i].requestsColSize[j] * sizeof(int));
            if (pRequests[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pRequests[k]);
                    pRequests[k] = NULL;
                }
                free(pRequests);
                pRequests = NULL;
            }
            memset(pRequests[j], 0, (testCase[i].requestsColSize[j] * sizeof(int)));
            memcpy(pRequests[j], testCase[i].requests[j], (testCase[i].requestsColSize[j] * sizeof(int)));
        }
        answer = maximumRequests(testCase[i].n, pRequests, testCase[i].requestsSize, testCase[i].requestsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].requestsSize; ++j) {
            free(pRequests[j]);
            pRequests[j] = NULL;
        }
        free(pRequests);
        pRequests = NULL;
    }

    return EXIT_SUCCESS;
}
