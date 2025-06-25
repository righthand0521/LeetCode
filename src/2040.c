#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long kthSmallestProduct(int* nums1, int nums1Size, int* nums2, int nums2Size, long long k) {
    long long retVal = 0;

    int pos1 = 0;
    while ((pos1 < nums1Size) && (nums1[pos1] < 0)) {
        pos1++;
    }
    int pos2 = 0;
    while ((pos2 < nums2Size) && (nums2[pos2] < 0)) {
        pos2++;
    }

    long long count, i1, i2;
    long long middle;
    long long left = -1e10;
    long long right = 1e10;
    while (left <= right) {
        middle = (left + right) / 2;
        count = 0;

        i1 = 0, i2 = pos2 - 1;
        while ((i1 < pos1) && (i2 >= 0)) {
            if ((long long)nums1[i1] * nums2[i2] > middle) {
                i1++;
            } else {
                count += (pos1 - i1);
                i2--;
            }
        }

        i1 = pos1;
        i2 = nums2Size - 1;
        while ((i1 < nums1Size) && (i2 >= pos2)) {
            if ((long long)nums1[i1] * nums2[i2] > middle) {
                i2--;
            } else {
                count += (i2 - pos2 + 1);
                i1++;
            }
        }

        i1 = 0;
        i2 = pos2;
        while ((i1 < pos1) && (i2 < nums2Size)) {
            if ((long long)nums1[i1] * nums2[i2] > middle) {
                i2++;
            } else {
                count += (nums2Size - i2);
                i1++;
            }
        }

        i1 = pos1;
        i2 = 0;
        while ((i1 < nums1Size) && (i2 < pos2)) {
            if ((long long)nums1[i1] * nums2[i2] > middle) {
                i1++;
            } else {
                count += (nums1Size - i1);
                i2++;
            }
        }

        if (count < k) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(5 * 10000)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
        long long k;
    } testCase[] = {
        {{2, 5}, 2, {3, 4}, 2, 2}, {{-4, -2, 0, 3}, 4, {2, 4}, 2, 6}, {{-2, -1, 0, 1, 2}, 5, {-3, -1, 2, 4, 5}, 5, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [2,5], nums2 = [3,4], k = 2
     *  Output: 8
     *
     *  Input: nums1 = [-4,-2,0,3], nums2 = [2,4], k = 6
     *  Output: 0
     *
     *  Input: nums1 = [-2,-1,0,1,2], nums2 = [-3,-1,2,4,5], k = 3
     *  Output: -6
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
        printf("], k = %lld\n", testCase[i].k);

        answer = kthSmallestProduct(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size,
                                    testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
