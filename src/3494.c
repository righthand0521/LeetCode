#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long minTime(int* skill, int skillSize, int* mana, int manaSize) {
    long long retVal = 0;

    long long times[skillSize];
    memset(times, 0, sizeof(times));
    long long currentTime;
    for (int j = 0; j < manaSize; j++) {
        currentTime = 0;
        for (int i = 0; i < skillSize; i++) {
            currentTime = ((currentTime > times[i]) ? (currentTime) : (times[i])) + (long long)(skill[i] * mana[j]);
        }
        times[skillSize - 1] = currentTime;
        for (int i = skillSize - 2; i >= 0; i--) {
            times[i] = times[i + 1] - (long long)skill[i + 1] * mana[j];
        }
    }
    retVal = times[skillSize - 1];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int skill[MAX_SIZE];
        int skillSize;
        int mana[MAX_SIZE];
        int manaSize;
    } testCase[] = {{{1, 5, 2, 4}, 4, {5, 1, 4, 2}, 4}, {{1, 1, 1}, 3, {1, 1, 1}, 3}, {{1, 2, 3, 4}, 4, {1, 2}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: skill = [1,5,2,4], mana = [5,1,4,2]
     *  Output: 110
     *
     *  Input: skill = [1,1,1], mana = [1,1,1]
     *  Output: 5
     *
     *  Input: skill = [1,2,3,4], mana = [1,2]
     *  Output: 21
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: skill = [");
        for (j = 0; j < testCase[i].skillSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].skill[j]);
        }
        printf("], mana = [");
        for (j = 0; j < testCase[i].manaSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].mana[j]);
        }
        printf("]\n");

        answer = minTime(testCase[i].skill, testCase[i].skillSize, testCase[i].mana, testCase[i].manaSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
