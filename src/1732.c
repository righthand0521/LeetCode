#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int largestAltitude(int* gain, int gainSize) {
    int retVal = 0;

    int prefixSum = retVal;
    int i;
    for (i = 0; i < gainSize; ++i) {
        prefixSum += gain[i];
        retVal = fmax(retVal, prefixSum);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int gain[MAX_SIZE];
        int gainSize;
    } testCase[] = {{{-5, 1, 5, 0, -7}, 5}, {{-4, -3, -2, -1, 4, 3, 2}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: gain = [-5,1,5,0,-7]
     *  Output: 1
     *
     *  Input: gain = [-4,-3,-2,-1,4,3,2]
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: gain = [");
        for (j = 0; j < testCase[i].gainSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].gain[j]);
        }
        printf("]\n");

        answer = largestAltitude(testCase[i].gain, testCase[i].gainSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
