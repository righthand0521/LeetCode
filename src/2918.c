#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long minSum(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    long long retVal = -1;

    long long sum1 = 0;
    int zero1 = 0;
    for (int i = 0; i < nums1Size; ++i) {
        sum1 += nums1[i];
        if (nums1[i] == 0) {
            sum1 += 1;
            zero1 += 1;
        }
    }

    long long sum2 = 0;
    int zero2 = 0;
    for (int i = 0; i < nums2Size; ++i) {
        sum2 += nums2[i];
        if (nums2[i] == 0) {
            sum2++;
            zero2++;
        }
    }

    if (((zero1 == 0) && (sum2 > sum1)) || ((zero2 == 0) && (sum1 > sum2))) {
        return retVal;
    }
    retVal = fmax(sum1, sum2);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
    } testCase[] = {{{3, 2, 0, 1, 0}, 5, {6, 5, 0}, 3}, {{2, 0, 2, 0}, 4, {1, 4}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [3,2,0,1,0], nums2 = [6,5,0]
     *  Output: 12
     *
     *  Input: nums1 = [2,0,2,0], nums2 = [1,4]
     *  Output: -1
     */

    long long answer;
    int i, j;
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

        answer = minSum(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
