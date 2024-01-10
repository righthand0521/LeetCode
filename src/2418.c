#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // descending order
    return (p1[0] < p2[0]);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** sortPeople(char** names, int namesSize, int* heights, int heightsSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = namesSize;
    pRetVal = (char**)malloc((*returnSize) * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    int id[(*returnSize)][2];
    int i;
    for (i = 0; i < (*returnSize); ++i) {
        id[i][0] = heights[i];
        id[i][1] = i;
    }
    qsort(id, (*returnSize), sizeof(id[0]), compareIntArray);
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = names[id[i][1]];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e3)
    struct testCaseType {
        char* names[MAX_SIZE];
        int namesSize;
        int heights[MAX_SIZE];
        int heightsSize;
        int returnSize;
    } testCase[] = {{{"Mary", "John", "Emma"}, 3, {180, 165, 170}, 3, 0},
                    {{"Alice", "Bob", "Bob"}, 3, {155, 185, 150}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: names = ["Mary","John","Emma"], heights = [180,165,170]
     *  Output: ["Mary","Emma","John"]
     *
     *  Input: names = ["Alice","Bob","Bob"], heights = [155,185,150]
     *  Output: ["Bob","Alice","Bob"]
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: names = [");
        for (j = 0; j < testCase[i].namesSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].names[j]);
        }
        printf("], heights = [");
        for (j = 0; j < testCase[i].heightsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].heights[j]);
        }
        printf("]\n");

        pAnswer = sortPeople(testCase[i].names, testCase[i].namesSize, testCase[i].heights, testCase[i].heightsSize,
                             &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
