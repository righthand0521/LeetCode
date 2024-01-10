#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    double retVal = 0;

    int total = nums1Size + nums2Size;
    int merge[total];
    memset(merge, 0, total * sizeof(int));

    int idx1 = 0;
    int idx2 = 0;
    int idx;
    for (idx = 0; idx < total; ++idx) {
        if ((idx1 == nums1Size) || (idx2 == nums2Size)) {
            break;
        }
        merge[idx] = (nums1[idx1] < nums2[idx2]) ? nums1[idx1++] : nums2[idx2++];
    }
    while (idx < total) {
        if (idx1 == nums1Size) {
            merge[idx] = nums2[idx2++];
        } else if (idx2 == nums2Size) {
            merge[idx] = nums1[idx1++];
        }
        idx++;
    }

    if ((total % 2) == 1) {
        retVal = merge[total / 2];
    } else {
        retVal = merge[total / 2 - 1] + merge[total / 2];
        retVal /= 2.0;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
    } testCase[] = {{{1, 3}, 2, {2}, 1}, {{1, 2}, 2, {3, 4}, 2}, {{1}, 1, {}, 0}, {{1}, 1, {2}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [1,3], nums2 = [2]
     *  Output: 2.00000
     *
     *  Input: nums1 = [1,2], nums2 = [3,4]
     *  Output: 2.50000
     *
     *  Input: nums1 = [1], nums2 = []
     *  Output: 1.00000
     *
     *  Input: nums1 = [1], nums2 = [2]
     *  Output: 1.50000
     */

    int i, j;
    double answer;
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

        answer =
            findMedianSortedArrays(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size);
        printf("Output: %.5f\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
