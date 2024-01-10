#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareLonglong(const void* n1, const void* n2) {
    // ascending order
    return (*(long long*)n1 > *(long long*)n2);
}
// https://leetcode.com/problems/put-marbles-in-bags/solutions/3111736/java-c-python-3-approachs-best-o-n/
// https://leetcode.cn/problems/put-marbles-in-bags/solutions/2080577/by-wan-shi-liang-de-mang-fu-mwjh/
long long putMarbles(int* weights, int weightsSize, int k) {
    long long retVal = 0;

    /* Example: weights = [1,3,5,1], k = 2. Return the difference between the maximum and minimum scores.
     *  [1] [3,5,1]: (1+1) + (3+1) = 6  ->  6 - (1+1) = 4
     *  [1,3] [5,1]: (1+3) + (5+1) = 10 -> 10 - (1+1) = 8
     *  [1,3 5] [1]: (1+5) + (1+1) = 8  ->  8 - (1+1) = 6
     *
     *  [1,3,5,1] => [(1+3),(3+5),(5+1)] = [4,8,6]
     *
     *  1. 對weights進行兩兩求和得到map
     *  2. map中挑k-1個值，並累和得到sum
     *  3. 求出sum的最大值和最小值並做差
     */
    int mapSize = weightsSize - 1;
    if (weightsSize == 1) {
        return retVal;
    }
    long long map[mapSize];
    memset(map, 0, sizeof(map));
    for (int i = 1; i < weightsSize; i++) {
        map[i - 1] = weights[i] + weights[i - 1];
    }
    qsort(map, mapSize, sizeof(long long), compareLonglong);

    long long minimumScores = 0;
    long long maximumScores = 0;
    for (int i = 0; i < k - 1; i++) {
        minimumScores += map[i];
        maximumScores += map[mapSize - 1 - i];
    }
    retVal = maximumScores - minimumScores;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int weights[MAX_SIZE];
        int weightsSize;
        int k;
    } testCase[] = {{{1, 3, 5, 1}, 4, 2}, {{1, 3}, 2, 2}, {{11}, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: weights = [1,3,5,1], k = 2
     *  Output: 4
     *
     *  Input: weights = [1, 3], k = 2
     *  Output: 0
     *
     *  Input: weights = [11], k = 1
     *  Output: 0
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: weights = [");
        for (j = 0; j < testCase[i].weightsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].weights[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = putMarbles(testCase[i].weights, testCase[i].weightsSize, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
