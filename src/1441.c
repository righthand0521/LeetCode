#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** buildArray(int* target, int targetSize, int n, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (char**)malloc(sizeof(char*) * (n * 2));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

#define STR_SIZE (8)
#define STR_PUSH "Push"
#define STR_POP "Pop"
    int targetIndex = 0;
    int i;
    for (i = 1; i <= n; ++i) {
        if (targetIndex == targetSize) {
            break;
        }

        if (i == target[targetIndex]) {
            pRetVal[(*returnSize)] = (char*)malloc(STR_SIZE * sizeof(char));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (STR_SIZE * sizeof(char)));
            snprintf(pRetVal[(*returnSize)], (STR_SIZE * sizeof(char)), "%s", STR_PUSH);
            targetIndex++;
            (*returnSize)++;
        } else {
            pRetVal[(*returnSize)] = (char*)malloc(STR_SIZE * sizeof(char));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (STR_SIZE * sizeof(char)));
            snprintf(pRetVal[(*returnSize)], (STR_SIZE * sizeof(char)), "%s", STR_PUSH);
            (*returnSize)++;

            pRetVal[(*returnSize)] = (char*)malloc(STR_SIZE * sizeof(char));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (STR_SIZE * sizeof(char)));
            snprintf(pRetVal[(*returnSize)], (STR_SIZE * sizeof(char)), "%s", STR_POP);
            (*returnSize)++;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int target[MAX_SIZE];
        int targetSize;
        int n;
        int returnSize;
    } testCase[] = {{{1, 3}, 2, 3}, {{1, 2, 3}, 3, 3}, {{1, 2}, 2, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: target = [1,3], n = 3
     *  Output: ["Push","Push","Pop","Push"]
     *
     *  Input: target = [1,2,3], n = 3
     *  Output: ["Push","Push","Push"]
     *
     *  Input: target = [1,2], n = 4
     *  Output: ["Push","Push"]
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: target = [");
        for (j = 0; j < testCase[i].targetSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].target[j]);
        }
        printf("], n = %d\n", testCase[i].n);

        pAnswer = buildArray(testCase[i].target, testCase[i].targetSize, testCase[i].n, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
