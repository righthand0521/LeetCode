#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numPairsDivisibleBy60(int* time, int timeSize) {
    int retVal = 0;

#define DIVISIBLE (60)
    int hashTable[DIVISIBLE];
    memset(hashTable, 0, sizeof(hashTable));
    int value;
    int i;
    for (i = 0; i < timeSize; ++i) {
        value = time[i] % DIVISIBLE;
        if (hashTable[value] != 0) {
            retVal += hashTable[value];
        }

        value = (60 - value) % 60;
        hashTable[value] += 1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (6 * 10000)
    struct testCaseType {
        int time[MAX_SIZE];
        int timeSize;
    } testCase[] = {{{30, 20, 150, 100, 40}, 5}, {{60, 60, 60}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: time = [30,20,150,100,40]
     *  IOutput: 3
     *  I
     *  IInput: time = [60,60,60]
     *  IOutput: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: time = [");
        for (j = 0; j < testCase[i].timeSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].time[j]);
        }
        printf("]\n");

        answer = numPairsDivisibleBy60(testCase[i].time, testCase[i].timeSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
