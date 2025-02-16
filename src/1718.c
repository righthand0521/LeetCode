#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool findLexicographicallyLargestSequence(int index, int* result, int* returnSize, bool* isNumberUsed, int target) {
    bool retVal = true;

    // If we have filled all positions, return true indicating success
    if (index == (*returnSize)) {
        return retVal;
    }

    // If the current position is already filled, move to the next index
    if (result[index] != 0) {
        retVal = findLexicographicallyLargestSequence(index + 1, result, returnSize, isNumberUsed, target);
        return retVal;
    }

    // Attempt to place numbers from target to 1 for a lexicographically largest result
    for (int numberToPlace = target; numberToPlace >= 1; numberToPlace--) {
        if (isNumberUsed[numberToPlace] == true) {
            continue;
        }
        isNumberUsed[numberToPlace] = true;
        result[index] = numberToPlace;

        // If placing number 1, move to the next index directly
        if (numberToPlace == 1) {
            if (findLexicographicallyLargestSequence(index + 1, result, returnSize, isNumberUsed, target) == true) {
                return retVal;
            }
        }
        // Place larger numbers at two positions if valid
        else if ((index + numberToPlace < (*returnSize)) && (result[index + numberToPlace] == 0)) {
            result[index + numberToPlace] = numberToPlace;
            if (findLexicographicallyLargestSequence(index + 1, result, returnSize, isNumberUsed, target) == true) {
                return retVal;
            }
            // Undo the placement for backtracking
            result[index + numberToPlace] = 0;
        }

        // Undo current placement and mark the number as unused
        result[index] = 0;
        isNumberUsed[numberToPlace] = false;
    }
    retVal = false;

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* constructDistancedSequence(int n, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 2 * n - 1;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    // Keep track of which numbers are already placed in the sequence
    int isNumberUsedSize = n + 1;
    bool* isNumberUsed = (bool*)malloc(isNumberUsedSize * sizeof(bool));
    if (isNumberUsed == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(isNumberUsed, false, (isNumberUsedSize * sizeof(bool)));

    // Start recursive backtracking to construct the sequence
    findLexicographicallyLargestSequence(0, pRetVal, returnSize, isNumberUsed, n);

    //
    free(isNumberUsed);
    isNumberUsed = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int returnSize;
    } testCase[] = {{3, 0}, {5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3
     *  Output: [3,1,2,3,2]
     *
     *  Input: n = 5
     *  Output: [5,3,1,4,3,5,2,4,2]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = constructDistancedSequence(testCase[i].n, &testCase[i].returnSize);
        printf("Output: [");
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
