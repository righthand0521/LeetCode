#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATH (1)
#define ONE_TRAVERSAL (1)
#define BRUTE_FORCE (1)  // Time Limit Exceeded
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int retVal = -1;

#if (MATH)
    printf("MATH\n");
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
#elif (ONE_TRAVERSAL)
    printf("ONE_TRAVERSAL\n");

    int tank;
    int count;
    int index;
    int i = 0;
    while (i < gasSize) {
        tank = 0;
        count = 0;
        while (count < gasSize) {
            index = (i + count) % gasSize;
            tank += (gas[index] - cost[index]);
            if (tank < 0) {
                break;
            }
            count++;
        }

        if (count == gasSize) {
            retVal = i;
            break;
        }
        i = i + count + 1;
    }
#elif (BRUTE_FORCE)
    printf("BRUTE_FORCE\n");

    int tank = 0;
    int i, j;
    for (i = 0; i < gasSize; ++i) {
        tank = gas[i] - cost[i];
        j = (i + 1) % gasSize;
        while ((tank > 0) && (j != i)) {
            tank += (gas[j] - cost[j]);
            j = (j + 1) % gasSize;
        }

        if ((tank >= 0) && (j == i)) {
            retVal = i;
            break;
        }
    }
#endif

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
