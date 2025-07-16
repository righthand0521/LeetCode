#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximumLength(int* nums, int numsSize) {
    int retVal = 0;

    int patterns[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    for (int i = 0; i < 4; i++) {
        int cnt = 0;
        for (int j = 0; j < numsSize; j++) {
            if (nums[j] % 2 == patterns[i][cnt % 2]) {
                cnt++;
            }
        }
        if (cnt > retVal) {
            retVal = cnt;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 4}, 4}, {{1, 2, 1, 1, 2, 1, 2}, 7}, {{1, 3}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,4]
     *  Output: 4
     *
     *  Input: nums = [1,2,1,1,2,1,2]
     *  Output: 6
     *
     *  Input: nums = [1,3]
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maximumLength(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
