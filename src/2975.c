#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int compareInteger(const void* a, const void* b) {
    int retVal = 0;

    int x = *(const int*)a;
    int y = *(const int*)b;
    retVal = (x > y) - (x < y);

    return retVal;
}
int* getEdges(int* fences, int fencesSize, int border, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int arrSize = fencesSize + 2;
    int* arr = (int*)malloc(arrSize * sizeof(int));
    if (arr == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(arr, 0, (arrSize * sizeof(int)));
    memcpy(arr, fences, (fencesSize * sizeof(int)));
    arr[fencesSize] = 1;
    arr[fencesSize + 1] = border;
    qsort(arr, arrSize, sizeof(int), compareInteger);

    int maxEdges = arrSize * (arrSize - 1) / 2;
    pRetVal = (int*)malloc(maxEdges * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        free(arr);
        arr = NULL;
        return pRetVal;
    }
    memset(pRetVal, 0, (maxEdges * sizeof(int)));
    int idx = 0;
    for (int i = 0; i < arrSize; i++) {
        for (int j = i + 1; j < arrSize; j++) {
            pRetVal[idx++] = arr[j] - arr[i];
        }
    }
    free(arr);
    arr = NULL;
    qsort(pRetVal, idx, sizeof(int), compareInteger);

    for (int i = 0; i < idx; i++) {
        if ((i == 0) || (pRetVal[i] != pRetVal[i - 1])) {
            pRetVal[(*returnSize)++] = pRetVal[i];
        }
    }

    return pRetVal;
}
int maximizeSquareArea(int m, int n, int* hFences, int hFencesSize, int* vFences, int vFencesSize) {
    int retVal = -1;

    int hSize = 0;
    int* hEdges = getEdges(hFences, hFencesSize, m, &hSize);
    if (hEdges == NULL) {
        return retVal;
    }

    int vSize = 0;
    int* vEdges = getEdges(vFences, vFencesSize, n, &vSize);
    if (vEdges == NULL) {
        free(hEdges);
        hEdges = NULL;
        return retVal;
    }

    int i = 0, j = 0;
    long long ans = 0;
    while ((i < hSize) && (j < vSize)) {
        if (hEdges[i] == vEdges[j]) {
            if (hEdges[i] > ans) {
                ans = hEdges[i];
            }
            i++;
            j++;
        } else if (hEdges[i] < vEdges[j]) {
            i++;
        } else {
            j++;
        }
    }
    free(hEdges);
    hEdges = NULL;
    free(vEdges);
    vEdges = NULL;

    if (ans != 0) {
        retVal = ans * ans % MODULO;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (600)
    struct testCaseType {
        int m;
        int n;
        int hFences[MAX_SIZE];
        int hFencesSize;
        int vFences[MAX_SIZE];
        int vFencesSize;
    } testCase[] = {{4, 3, {2, 3}, 2, {2}, 1}, {6, 7, {2}, 1, {4}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
     *  Output: 4
     *
     *  Input: m = 6, n = 7, hFences = [2], vFences = [4]
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: m = %d, n = %d, hFences = [", testCase[i].m, testCase[i].n);
        for (j = 0; j < testCase[i].hFencesSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].hFences[j]);
        }
        printf("], vFences = [");
        for (j = 0; j < testCase[i].vFencesSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].vFences[j]);
        }
        printf("]\n");

        answer = maximizeSquareArea(testCase[i].m, testCase[i].n, testCase[i].hFences, testCase[i].hFencesSize,
                                    testCase[i].vFences, testCase[i].vFencesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
