#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int bagOfTokensScore(int* tokens, int tokensSize, int power) {
    int retVal = 0;

    qsort(tokens, tokensSize, sizeof(int), compareInteger);
    int left = 0;
    int right = tokensSize - 1;
    while (left <= right) {
        if (power >= tokens[left]) {
            power -= tokens[left];
            left++;
            retVal++;
        } else if ((left < right) && (retVal > 0)) {
            power += tokens[right];
            right--;
            retVal--;
        } else {
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int tokens[MAX_SIZE];
        int tokensSize;
        int power;
    } testCase[] = {{{100}, 1, 50}, {{200, 100}, 2, 150}, {{100, 200, 300, 400}, 4, 200}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: tokens = [100], power = 50
     *  Output: 0
     *
     *  Input: tokens = [200,100], power = 150
     *  Output: 1
     *
     *  Input: tokens = [100,200,300,400], power = 200
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: tokens = [");
        for (j = 0; j < testCase[i].tokensSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].tokens[j]);
        }
        printf("], power = %d\n", testCase[i].power);

        answer = bagOfTokensScore(testCase[i].tokens, testCase[i].tokensSize, testCase[i].power);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
