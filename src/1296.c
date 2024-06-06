#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    int frequency;
} Node;
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
bool isPossibleDivide(int *nums, int numsSize, int k) {
    bool retVal = false;

    if (numsSize % k != 0) {
        return retVal;
    }

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int i, j;

    Node *pCount = (Node *)malloc(numsSize * sizeof(Node));
    if (pCount == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pCount, 0, sizeof(Node) * numsSize);
    pCount[0].value = nums[0];
    pCount[0].frequency = 1;
    int cardSize = 0;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] != pCount[cardSize].value) {
            cardSize++;
        }
        pCount[cardSize].value = nums[i];
        pCount[cardSize].frequency++;
    }

    int num;
    int pos = 0;
    for (i = 0; i < numsSize; ++i) {
        while ((pos < cardSize) && (pCount[pos].frequency == 0)) {
            pos++;
        }

        if ((pCount[pos].value == nums[i]) && (pCount[pos].frequency > 0)) {
            for (j = 0; j < k; ++j) {
                num = nums[i] + j;
                if ((pCount[pos + j].frequency > 0) && (pCount[pos + j].value == num)) {
                    pCount[pos + j].frequency--;
                } else {
                    goto exit;
                }
            }
        }
    }
    retVal = true;

exit:
    //
    free(pCount);
    pCount = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {
        {{1, 2, 3, 3, 4, 4, 5, 6}, 8, 4}, {{3, 2, 1, 2, 3, 4, 3, 4, 5, 9, 10, 11}, 12, 3}, {{1, 2, 3, 4}, 4, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,3,4,4,5,6], k = 4
     *  Output: true
     *
     *  Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
     *  Output: true
     *
     *  Input: nums = [1,2,3,4], k = 3
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = isPossibleDivide(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
