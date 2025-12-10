#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countPermutations(int* complexity, int complexitySize) {
    int retVal = 0;

    for (int i = 1; i < complexitySize; i++) {
        if (complexity[i] <= complexity[0]) {
            return retVal;
        }
    }

    long long answer = 1;
    int mod = 1000000007;
    for (int i = 2; i < complexitySize; i++) {
        answer = answer * i % mod;
    }
    retVal = answer;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int complexity[MAX_SIZE];
        int complexitySize;
    } testCase[] = {{{1, 2, 3}, 3}, {{3, 3, 3, 4, 4, 4}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: complexity = [1,2,3]
     *  Output: 2
     *
     *  Input: complexity = [3,3,3,4,4,4]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: complexity = [");
        for (j = 0; j < testCase[i].complexitySize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].complexity[j]);
        }
        printf("]\n");

        answer = countPermutations(testCase[i].complexity, testCase[i].complexitySize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
