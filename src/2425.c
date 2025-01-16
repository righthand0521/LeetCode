#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int xorAllNums(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int retVal = 0;

    int xor1 = 0;
    if (nums2Size % 2 != 0) {
        for (int i = 0; i < nums1Size; i++) {
            xor1 ^= nums1[i];
        }
    }

    int xor2 = 0;
    if (nums1Size % 2 != 0) {
        for (int i = 0; i < nums2Size; i++) {
            xor2 ^= nums2[i];
        }
    }

    retVal = xor1 ^ xor2;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
    } testCase[] = {{{2, 1, 3}, 3, {10, 2, 5, 0}, 4}, {{1, 2}, 2, {3, 4}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [2,1,3], nums2 = [10,2,5,0]
     *  Output: 13
     *
     *  Input: nums1 = [1,2], nums2 = [3,4]
     *  Output: 0
     */

    int answer;
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

        answer = xorAllNums(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
