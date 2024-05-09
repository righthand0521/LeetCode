#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
long long maximumHappinessSum(int* happiness, int happinessSize, int k) {
    long long retVal = 0;

    qsort(happiness, happinessSize, sizeof(int), compareInteger);
    int happy;
    int i;
    for (i = 0; i < k; ++i) {
        happy = happiness[i] - i;
        if (happy <= 0) {
            break;
        }
        retVal += happy;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 100000)
    struct testCaseType {
        int happiness[MAX_SIZE];
        int happinessSize;
        int k;
    } testCase[] = {{{1, 2, 3}, 3, 2}, {{1, 1, 1, 1}, 4, 2}, {{2, 3, 4, 5}, 4, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: happiness = [1,2,3], k = 2
     *  Output: 4
     *
     *  Input: happiness = [1,1,1,1], k = 2
     *  Output: 1
     *
     *  Input: happiness = [2,3,4,5], k = 1
     *  Output: 5
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: happiness = [");
        for (j = 0; j < testCase[i].happinessSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].happiness[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maximumHappinessSum(testCase[i].happiness, testCase[i].happinessSize, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
