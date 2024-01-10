#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxUncrossedLines(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int retVal = 0;

    int dp[nums1Size + 1][nums2Size + 1];
    memset(dp, 0, sizeof(dp));

    /* Example: Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
     *     10 5 2 1 5 2
     *    0 0 0 0 0 0 0
     *  2 0 0 0 1 1 1 1
     *  5 0 0 1 1 1 2 2
     *  1 0 0 1 1 2 2 2
     *  2 0 0 1 2 2 2 3
     *  5 0 0 1 2 2 3 3
     */
    int idx1, idx2;
    for (idx1 = 1; idx1 <= nums1Size; ++idx1) {
        for (idx2 = 1; idx2 <= nums2Size; ++idx2) {
            if (nums1[idx1 - 1] == nums2[idx2 - 1]) {
                dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + 1;
            } else {
                dp[idx1][idx2] = fmax(dp[idx1 - 1][idx2], dp[idx1][idx2 - 1]);
            }
        }
    }
    retVal = dp[nums1Size][nums2Size];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
    } testCase[] = {{{1, 4, 2}, 3, {1, 2, 4}, 3},
                    {{2, 5, 1, 2, 5}, 5, {10, 5, 2, 1, 5, 2}, 6},
                    {{1, 3, 7, 1, 7, 5}, 6, {1, 9, 2, 5, 1}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [1,4,2], nums2 = [1,2,4]
     *  Output: 2
     *
     *  Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
     *  Output: 3
     *
     *  Input: nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums1 = [");
        for (j = 0; j < testCase[i].nums1Size; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums1[j]);
        }
        printf("], nums2 = [");
        for (j = 0; j < testCase[i].nums2Size; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums2[j]);
        }
        printf("]\n");

        answer = maxUncrossedLines(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
