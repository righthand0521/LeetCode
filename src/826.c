#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    } else {
        return (p1[0] > p2[0]);
    }
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {
    int retVal = 0;

    int jobIdx = 0;
    int jobSize = difficultySize;
    int job[jobSize][2];
    int i;
    for (i = 0; i < jobSize; ++i) {
        job[i][0] = difficulty[i];
        job[i][1] = profit[i];
    }
    qsort(job, jobSize, sizeof(job[0]), compareIntArray);

    int maxProfit = 0;
    qsort(worker, workerSize, sizeof(int), compareInteger);
    for (i = 0; i < workerSize; ++i) {
        while ((jobIdx < jobSize) && (worker[i] >= job[jobIdx][0])) {
            maxProfit = fmax(maxProfit, job[jobIdx][1]);
            ++jobIdx;
        }
        retVal += maxProfit;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int difficulty[MAX_SIZE];
        int difficultySize;
        int profit[MAX_SIZE];
        int profitSize;
        int worker[MAX_SIZE];
        int workerSize;
    } testCase[] = {{{2, 4, 6, 8, 10}, 5, {10, 20, 30, 40, 50}, 5, {4, 5, 6, 7}, 4},
                    {{85, 47, 57}, 3, {24, 66, 99}, 3, {40, 25, 25}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
     *  Output: 100
     *
     *  Input: difficulty = [85,47,57], profit = [24,66,99], worker = [40,25,25]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: difficulty = [");
        for (j = 0; j < testCase[i].difficultySize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].difficulty[j]);
        }
        printf("], profit = [");
        for (j = 0; j < testCase[i].profitSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].profit[j]);
        }
        printf("], worker = [");
        for (j = 0; j < testCase[i].workerSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].worker[j]);
        }
        printf("]\n");

        answer = maxProfitAssignment(testCase[i].difficulty, testCase[i].difficultySize, testCase[i].profit,
                                     testCase[i].profitSize, testCase[i].worker, testCase[i].workerSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
