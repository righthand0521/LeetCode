#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
    int retVal = 0;

    /* https://leetcode.cn/problems/poor-pigs/solutions/15770/hua-jie-suan-fa-458-ke-lian-de-xiao-zhu-by-guanpen/
     *  pow(base, answer) ≥ buckets
     *  => answer ≥ log(buckets) / log(base)
     *  => answer = ceil(log(buckets) / log(base))
     */
    int base = minutesToTest / minutesToDie + 1;
    retVal = ceil(log10(buckets) / log10(base));

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int buckets;
        int minutesToDie;
        int minutesToTest;
    } testCase[] = {{4, 15, 15}, {4, 15, 30}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: buckets = 4, minutesToDie = 15, minutesToTest = 15
     *  Output: 2
     *
     *  Input: buckets = 4, minutesToDie = 15, minutesToTest = 30
     *  Output: 2
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: buckets = %d, minutesToDie = %d, minutesToTest = %d\n", testCase[i].buckets,
               testCase[i].minutesToDie, testCase[i].minutesToTest);

        answer = poorPigs(testCase[i].buckets, testCase[i].minutesToDie, testCase[i].minutesToTest);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
