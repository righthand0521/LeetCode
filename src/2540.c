#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getCommon(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int retVal = -1;

    int nums1Idx = 0;
    int nums2Idx = 0;
    while ((nums1Idx < nums1Size) && (nums2Idx < nums2Size)) {
        if (nums1[nums1Idx] == nums2[nums2Idx]) {
            retVal = nums1[nums1Idx];
            break;
        } else if (nums1[nums1Idx] > nums2[nums2Idx]) {
            nums2Idx++;
        } else if (nums1[nums1Idx] < nums2[nums2Idx]) {
            nums1Idx++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
    } testCase[] = {{{1, 2, 3}, 3, {2, 4}, 2}, {{1, 2, 3, 6}, 4, {2, 3, 4, 5}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [1,2,3], nums2 = [2,4]
     *  Output: 2
     *
     *  Input: nums1 = [1,2,3,6], nums2 = [2,3,4,5]
     *  Output: 2
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

        answer = getCommon(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
