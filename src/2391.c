#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int garbageCollection(char** garbage, int garbageSize, int* travel, int travelSize) {
    int retVal = 0;

    int i, j;

    int travelPrefixSum[travelSize + 1];
    memset(travelPrefixSum, 0, sizeof(travelPrefixSum));
    for (i = 0; i < travelSize; ++i) {
        travelPrefixSum[i + 1] = travelPrefixSum[i] + travel[i];
    }

    // garbage[i] consists only of the characters 'M', 'P' and 'G'
    int garbageType = 4;
    int lastGarbage[garbageType];
    memset(lastGarbage, 0, sizeof(lastGarbage));

    int len;
    for (i = 0; i < garbageSize; ++i) {
        len = strlen(garbage[i]);
        for (j = 0; j < len; ++j) {
            if (garbage[i][j] == 'M') {
                lastGarbage[1] = i;
            } else if (garbage[i][j] == 'P') {
                lastGarbage[2] = i;
            } else if (garbage[i][j] == 'G') {
                lastGarbage[3] = i;
            }
            retVal += 1;
        }
    }

    for (i = 0; i < garbageType; ++i) {
        retVal += travelPrefixSum[lastGarbage[i]];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char* garbage[MAX_SIZE];
        int garbageSize;
        int travel[MAX_SIZE];
        int travelSize;
    } testCase[] = {{{"G", "P", "GP", "GG"}, 4, {2, 4, 3}, 3}, {{"MMM", "PGM", "GP"}, 3, {3, 10}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: garbage = ["G","P","GP","GG"], travel = [2,4,3]
     *  Output: 21
     *
     *  Input: garbage = ["MMM","PGM","GP"], travel = [3,10]
     *  Output: 37
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: garbage = [");
        for (j = 0; j < testCase[i].garbageSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].garbage[j]);
        }
        printf("], travel = [");
        for (j = 0; j < testCase[i].travelSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].travel[j]);
        }
        printf("]\n");

        answer =
            garbageCollection(testCase[i].garbage, testCase[i].garbageSize, testCase[i].travel, testCase[i].travelSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
