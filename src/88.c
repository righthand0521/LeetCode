#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUILD_IN (0)
#define TWO_POINTERS (1)
#if (BUILD_IN)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#elif (TWO_POINTERS)
#endif
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    if ((m + n) > nums1Size) {
        return;
    }

#if (BUILD_IN)
    printf("BUILD_IN\n");

    memcpy(nums1 + m, nums2, n * sizeof(int));
    qsort(nums1, m + n, sizeof(int), compareInteger);
#elif (TWO_POINTERS)
    printf("TWO_POINTERS\n");

    int idx = nums1Size - 1;
    int idx1 = m - 1;
    int idx2 = n - 1;
    while ((idx1 >= 0) && (idx2 >= 0)) {
        if (nums1[idx1] > nums2[idx2]) {
            nums1[idx--] = nums1[idx1--];
        } else {
            nums1[idx--] = nums2[idx2--];
        }
    }
    while (idx1 >= 0) {
        nums1[idx--] = nums1[idx1--];
    }
    while (idx2 >= 0) {
        nums1[idx--] = nums2[idx2--];
    }
#endif
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int m;
        int nums2[MAX_SIZE];
        int nums2Size;
        int n;
    } testCase[] = {{{1, 2, 3, 0, 0, 0}, 6, 3, {2, 5, 6}, 3, 3}, {{1}, 1, 1, {}, 0, 0}, {{0}, 1, 0, {1}, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
     *  Output: [1,2,2,3,5,6]
     *
     *  Input: nums1 = [1], m = 1, nums2 = [], n = 0
     *  Output: [1]
     *
     *  Input: nums1 = [0], m = 0, nums2 = [1], n = 1
     *  Output: [1]
     */

    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums1 = [");
        for (j = 0; j < testCase[i].nums1Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums1[j]);
        }
        printf("], m = %d, ", testCase[i].m);
        printf("nums2 = [");
        for (j = 0; j < testCase[i].nums2Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums2[j]);
        }
        printf("], n = %d\n", testCase[i].n);

        merge(testCase[i].nums1, testCase[i].nums1Size, testCase[i].m, testCase[i].nums2, testCase[i].nums2Size,
              testCase[i].n);

        printf("Output: [");
        for (j = 0; j < (testCase[i].m + testCase[i].n); ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums1[j]);
        }
        printf("]\n");
        printf("\n");
    }

    return EXIT_SUCCESS;
}
