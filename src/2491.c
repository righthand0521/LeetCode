#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long dividePlayers(int* skill, int skillSize) {
    long long retVal = -1;

    int totalSkill = 0;
    int skillFrequency[1001];  // 1 <= skill[i] <= 1000
    memset(skillFrequency, 0, sizeof(skillFrequency));
    for (int i = 0; i < skillSize; ++i) {
        totalSkill += skill[i];
        skillFrequency[skill[i]]++;
    }
    if (totalSkill % (skillSize / 2) != 0) {
        return retVal;
    }

    int partnerSkill;
    int targetTeamSkill = totalSkill / (skillSize / 2);
    long long totalChemistry = 0;
    for (int i = 0; i < skillSize; ++i) {
        partnerSkill = targetTeamSkill - skill[i];
        if (skillFrequency[partnerSkill] == 0) {
            return retVal;
        }

        totalChemistry += (long long)skill[i] * (long long)partnerSkill;
        skillFrequency[partnerSkill]--;
    }
    retVal = totalChemistry / 2;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int skill[MAX_SIZE];
        int skillSize;
    } testCase[] = {{{3, 2, 5, 1, 3, 4}, 6}, {{3, 4}, 2}, {{1, 1, 2, 3}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: skill = [3,2,5,1,3,4]
     *  Output: 22
     *
     *  Input: skill = [3,4]
     *  Output: 12
     *
     *  Input: skill = [1,1,2,3]
     *  Output: -1
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: skill = [");
        for (j = 0; j < testCase[i].skillSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].skill[j]);
        }
        printf("]\n");

        answer = dividePlayers(testCase[i].skill, testCase[i].skillSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
