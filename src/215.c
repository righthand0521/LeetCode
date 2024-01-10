#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HEAP (1)
#define QUICKSELECT (1)  // https://en.wikipedia.org/wiki/Quickselect
#if (HEAP)
void maxHeapify(int* a, int i, int heapSize) {
    int l = i * 2 + 1;
    int r = i * 2 + 2;
    int largest = i;

    if (l < heapSize && a[l] > a[largest]) {
        largest = l;
    }

    if (r < heapSize && a[r] > a[largest]) {
        largest = r;
    }

    if (largest != i) {
        int t = a[i];
        a[i] = a[largest], a[largest] = t;
        maxHeapify(a, largest, heapSize);
    }
}
void buildMaxHeap(int* a, int heapSize) {
    for (int i = heapSize / 2; i >= 0; --i) {
        maxHeapify(a, i, heapSize);
    }
}
#elif (QUICKSELECT)
inline int partition(int* a, int l, int r) {
    int x = a[r];
    int i = l - 1;
    int t;
    int j;
    for (j = l; j < r; ++j) {
        if (a[j] <= x) {
            t = a[++i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    t = a[i + 1];
    a[i + 1] = a[r];
    a[r] = t;

    return i + 1;
}
inline int randomPartition(int* a, int l, int r) {
    int i = rand() % (r - l + 1) + l;
    int t = a[i];
    a[i] = a[r], a[r] = t;

    return partition(a, l, r);
}
int quickSelect(int* a, int l, int r, int index) {
    int q = randomPartition(a, l, r);

    if (q == index) {
        return a[q];
    } else {
        return q < index ? quickSelect(a, q + 1, r, index) : quickSelect(a, l, q - 1, index);
    }
}
#endif
int findKthLargest(int* nums, int numsSize, int k) {
    int retVal = 0;

#if (HEAP)
    printf("Heap\n\n");

    int heapSize = numsSize;
    buildMaxHeap(nums, heapSize);

    int t;
    int i;
    for (i = numsSize - 1; i >= numsSize - k + 1; --i) {
        t = nums[0];
        nums[0] = nums[i];
        nums[i] = t;
        --heapSize;
        maxHeapify(nums, 0, heapSize);
    }

    retVal = nums[0];
#elif (QUICKSELECT)
    printf("Quickselect\n\n");

    srand(time(0));
    retVal = quickSelect(nums, 0, numsSize - 1, numsSize - k);
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (12)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{3, 2, 1, 5, 6, 4}, 6, 2}, {{3, 2, 3, 1, 2, 4, 5, 5, 6}, 9, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,2,1,5,6,4], k = 2
     *  Output: 5
     *
     *  Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
     *  Output: 4
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = findKthLargest(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
