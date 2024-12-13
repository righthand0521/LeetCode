#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
long long findScore(int* nums, int numsSize) {
    long long retVal = 0;

    int sorted[numsSize][2];
    memset(sorted, 0, sizeof(sorted));
    for (int i = 0; i < numsSize; ++i) {
        sorted[i][0] = nums[i];
        sorted[i][1] = i;
    }
    qsort(sorted, numsSize, sizeof(sorted[0]), compareIntArray);

    int marked[numsSize];
    memset(marked, false, sizeof(marked));
    int num, index;
    for (int i = 0; i < numsSize; i++) {
        num = sorted[i][0];
        index = sorted[i][1];

        if (marked[index] == true) {
            continue;
        }

        retVal += num;

        marked[index] = true;
        // mark adjacent elements if they exist
        if (index - 1 >= 0) {
            marked[index - 1] = true;
        }
        if (index + 1 < numsSize) {
            marked[index + 1] = true;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 1, 3, 4, 5, 2}, 6}, {{2, 3, 5, 1, 3, 2}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,1,3,4,5,2]
     *  Output: 7
     *
     *  Input: nums = [2,3,5,1,3,2]
     *  Output: 5
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = findScore(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
