#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int matchPlayersAndTrainers(int* players, int playersSize, int* trainers, int trainersSize) {
    int retVal = 0;

    qsort(players, playersSize, sizeof(int), compareInteger);
    qsort(trainers, trainersSize, sizeof(int), compareInteger);

    int playersIdx = 0;
    int trainersIdx = 0;
    while ((playersIdx < playersSize) && (trainersIdx < trainersSize)) {
        while ((trainersIdx < trainersSize) && (players[playersIdx] > trainers[trainersIdx])) {
            ++trainersIdx;
        }

        if (trainersIdx < trainersSize) {
            ++retVal;
        }

        ++playersIdx;
        ++trainersIdx;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int players[MAX_SIZE];
        int playersSize;
        int trainers[MAX_SIZE];
        int trainersSize;
    } testCase[] = {{{4, 7, 9}, 3, {8, 2, 5, 8}, 4}, {{1, 1, 1}, 3, {10}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: players = [4,7,9], trainers = [8,2,5,8]
     *  Output: 2
     *
     *  Input: players = [1,1,1], trainers = [10]
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: players = [");
        for (j = 0; j < testCase[i].playersSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].players[j]);
        }
        printf("], trainers = [");
        for (j = 0; j < testCase[i].trainersSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].trainers[j]);
        }
        printf("]\n");

        answer = matchPlayersAndTrainers(testCase[i].players, testCase[i].playersSize, testCase[i].trainers,
                                         testCase[i].trainersSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
