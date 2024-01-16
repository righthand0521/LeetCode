#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int retVal = -1;

    /* https://leetcode.cn/problems/gas-station/solutions/488498/shou-hua-tu-jie-liang-ge-guan-jian-jie-lun-de-jian/
     *  1. if sum(gas) < sum(cost), then it has no solution(-1).
     *  2. if sum(gas) >= sum(cost), then it has solution(i).
     *
     *      sum(gas) < sum(cost)     sum(gas) >= sum(cost)
     *     /                    \   /                     \
     *  [0]----------------------[i]-----------------------[n]
     */
    int tank = 0;
    int totalSum = 0;
    int start = 0;
    int i;
    for (i = 0; i < gasSize; ++i) {
        totalSum += (gas[i] - cost[i]);

        tank += (gas[i] - cost[i]);
        if (tank < 0) {
            start = i + 1;
            tank = 0;
        }
    }

    if (totalSum >= 0) {
        retVal = start;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int gas[MAX_SIZE];
        int gasSize;
        int cost[MAX_SIZE];
        int costSize;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5, {3, 4, 5, 1, 2}, 5}, {{2, 3, 4}, 3, {3, 4, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
     *  Output: 3
     *
     *  Input: gas = [2,3,4], cost = [3,4,3]
     *  Output: -1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: gas = [");
        for (j = 0; j < testCase[i].gasSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].gas[j]);
        }
        printf("], cost = [");
        for (j = 0; j < testCase[i].costSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].cost[j]);
        }
        printf("]\n");

        answer = canCompleteCircuit(testCase[i].gas, testCase[i].gasSize, testCase[i].cost, testCase[i].costSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
