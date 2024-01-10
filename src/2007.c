#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int* findOriginalArray(int* changed, int changedSize, int* returnSize) {
    int* pRetVal = NULL;

    if (changedSize % 2 != 0) {
        *returnSize = 0;
        return pRetVal;
    }
    *returnSize = changedSize / 2;
    pRetVal = (int*)malloc(*returnSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        *returnSize = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, *returnSize * sizeof(int));
    // sort from large to small
    qsort(changed, changedSize, sizeof(int), compareInteger);

    // appending twice the value and hash function is one to one, so the Hash Table need double constraints size
#define MAX_RECORD (100000 * 2 + 4)
    int RECORD[MAX_RECORD] = {0};
    int idx = 0;
    int i;
    for (i = 0; i < changedSize; ++i) {
        if (RECORD[2 * changed[i]] == 0) {
            ++RECORD[changed[i]];
            continue;
        }
        pRetVal[idx++] = changed[i];
        --RECORD[2 * changed[i]];
    }

    for (i = 0; i < MAX_RECORD; ++i) {
        if (RECORD[i] != 0) {
            *returnSize = 0;
            free(pRetVal);
            pRetVal = NULL;
            break;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int changed[MAX_SIZE];
        int changedSize;
        int returnSize;
    } testCase[] = {
        {{1, 3, 4, 2, 6, 8}, 6, 0}, {{6, 3, 0, 1}, 4, 0}, {{1}, 1, 0}, {{3, 3, 3, 3}, 4, 0}, {{2, 5, 5, 4}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: changed = [");
        for (j = 0; j < testCase[i].changedSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].changed[j]);
        }
        printf("]\n");

        pAnswer = findOriginalArray(testCase[i].changed, testCase[i].changedSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
