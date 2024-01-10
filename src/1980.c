#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* findDifferentBinaryString(char** nums, int numsSize) {
    char* pRetVal = NULL;

    int returnSize = numsSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    // https://en.wikipedia.org/wiki/Cantor%27s_diagonal_argument
    char c;
    int i;
    for (i = 0; i < numsSize; ++i) {
        c = nums[i][i];
        pRetVal[i] = ((c == '0') ? '1' : '0');
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW_SIZE (16)
#define MAX_COL_SIZE (16)
    struct testCaseType {
        char nums[MAX_ROW_SIZE][MAX_COL_SIZE];
        int numsSize;
    } testCase[] = {{{"01", "10"}, 2}, {{"00", "01"}, 2}, {{"111", "011", "001"}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = ["01","10"]
     *  Output: "11"
     *
     *  Input: nums = ["00","01"]
     *  Output: "11"
     *
     *  Input: nums = ["111","011","001"]
     *  Output: "101"
     */

    char** pNums = NULL;
    char* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pNums = (char**)malloc(testCase[i].numsSize * sizeof(char*));
        if (pNums == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].numsSize; ++j) {
            pNums[j] = (char*)malloc(MAX_COL_SIZE * sizeof(char));
            if (pNums[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pNums[k]);
                    pNums[k] = NULL;
                }
                return EXIT_FAILURE;
            }
            memset(pNums[j], 0, (MAX_COL_SIZE * sizeof(char)));
            memcpy(pNums[j], testCase[i].nums[j], strlen(testCase[i].nums[j]));
        }
        pAnswer = findDifferentBinaryString(pNums, testCase[i].numsSize);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        for (j = 0; j < testCase[i].numsSize; ++j) {
            free(pNums[j]);
            pNums[j] = NULL;
        }
        free(pNums);
        pNums = NULL;

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
