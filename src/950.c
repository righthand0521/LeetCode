#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *deckRevealedIncreasing(int *deck, int deckSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)malloc(deckSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (deckSize * sizeof(int)));

    int indexQueueSize = deckSize * 2;
    int indexQueue[indexQueueSize];
    memset(indexQueue, 0, sizeof(indexQueue));
    int indexQueueHead = 0;
    int indexQueueTail = 0;
    for (indexQueueTail = 0; indexQueueTail < deckSize; ++indexQueueTail) {
        indexQueue[indexQueueTail] = indexQueueTail;
    }

    qsort(deck, deckSize, sizeof(int), compareInteger);
    int i;
    for (i = 0; i < deckSize; ++i) {
        pRetVal[indexQueue[indexQueueHead++]] = deck[i];
        (*returnSize)++;
        if (indexQueueHead < indexQueueTail) {
            indexQueue[indexQueueTail++] = indexQueue[indexQueueHead++];
        }
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int deck[MAX_SIZE];
        int deckSize;
        int returnSize;
    } testCase[] = {{{17, 13, 11, 2, 3, 5, 7}, 7, 0}, {{1, 1000}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: deck = [17,13,11,2,3,5,7]
     *  Output: [2,13,3,11,5,17,7]
     *
     *  Input: deck = [1,1000]
     *  Output: [1,1000]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: deck = [");
        for (j = 0; j < testCase[i].deckSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].deck[j]);
        }
        printf("]\n");

        pAnswer = deckRevealedIncreasing(testCase[i].deck, testCase[i].deckSize, &testCase[i].returnSize);
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
