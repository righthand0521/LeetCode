#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* successfulPairs(int* spells, int spellsSize, int* potions, int potionsSize, long long success, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = spellsSize;
    pRetVal = (int*)calloc((*returnSize), sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    qsort(potions, potionsSize, sizeof(int), compareInteger);
    long divisor;
    int left, right, middle;
    int i;
    for (i = 0; i < spellsSize; ++i) {
        divisor = (success + spells[i] - 1) / spells[i];

        left = 0;
        right = potionsSize;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (potions[middle] < divisor) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        pRetVal[i] = potionsSize - left;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int spells[MAX_SIZE];
        int spellsSize;
        int potions[MAX_SIZE];
        int potionsSize;
        long long success;
        int returnSize;
    } testCase[] = {{{5, 1, 3}, 3, {1, 2, 3, 4, 5}, 5, 7, 0}, {{3, 1, 2}, 3, {8, 5, 8}, 3, 16, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
     *  Output: [4,0,3]
     *
     *  Input: spells = [3,1,2], potions = [8,5,8], success = 16
     *  Output: [2,0,2]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: spells = [");
        for (j = 0; j < testCase[i].spellsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].spells[j]);
        }
        printf("], potions = [");
        for (j = 0; j < testCase[i].potionsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].potions[j]);
        }
        printf("], success = %lld\n", testCase[i].success);

        pAnswer = successfulPairs(testCase[i].spells, testCase[i].spellsSize, testCase[i].potions,
                                  testCase[i].potionsSize, testCase[i].success, &testCase[i].returnSize);
        printf("Output = [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
