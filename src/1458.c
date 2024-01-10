#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxDotProduct(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int retVal = 0;

    int dp[nums1Size][nums2Size];
    memset(dp, 0, sizeof(dp));
    int product;
    int row, col;
    for (row = 0; row < nums1Size; ++row) {
        for (col = 0; col < nums2Size; ++col) {
            product = nums1[row] * nums2[col];

            dp[row][col] = product;
            if (row > 0) {
                dp[row][col] = fmax(dp[row][col], dp[row - 1][col]);
            }
            if (col > 0) {
                dp[row][col] = fmax(dp[row][col], dp[row][col - 1]);
            }
            if ((row > 0) && (col > 0)) {
                dp[row][col] = fmax(dp[row][col], dp[row - 1][col - 1] + product);
            }
        }
    }
    retVal = dp[nums1Size - 1][nums2Size - 1];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
    } testCase[] = {{{2, 1, -2, 5}, 4, {3, 0, -6}, 3}, {{3, -2}, 2, {2, -6, 7}, 3}, {{-1, -1}, 2, {1, 1}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
     *  Output: 18
     *
     *  Input: nums1 = [3,-2], nums2 = [2,-6,7]
     *  Output: 21
     *
     *  Input: nums1 = [-1,-1], nums2 = [1,1]
     *  Output: -1
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums1 = [");
        for (j = 0; j < testCase[i].nums1Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums1[j]);
        }
        printf("], nums2 = [");
        for (j = 0; j < testCase[i].nums2Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums2[j]);
        }
        printf("]\n");

        answer = maxDotProduct(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
