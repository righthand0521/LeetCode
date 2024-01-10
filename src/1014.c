#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxScoreSightseeingPair(int* values, int valuesSize) {
    int retVal = 0;

    // The score of a pair (i < j) of sightseeing spots is
    // values[i] + values[j] + i - j = (values[i] + i) + (values[j] - j)
    int maxScore = values[0] + 0;
    int i;
    for (i = 1; i < valuesSize; ++i) {
        retVal = fmax(retVal, (maxScore + values[i] - i));
        maxScore = fmax(maxScore, values[i] + i);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int values[MAX_SIZE];
        int valuesSize;
    } testCase[] = {{{8, 1, 5, 2, 6}, 5}, {{1, 2}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: values = [8,1,5,2,6]
     *  Output: 11
     *
     *  Input: values = [1,2]
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: values = [");
        for (j = 0; j < testCase[i].valuesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].values[j]);
        }
        printf("]\n");

        answer = maxScoreSightseeingPair(testCase[i].values, testCase[i].valuesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
