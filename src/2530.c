#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HEAP_H
#define HEAP_H

void swap(int *nums, int i, int j) {
    int x = nums[i];
    nums[i] = nums[j];
    nums[j] = x;
}
void down(int *nums, int size, int i) {
    int k;
    for (k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if ((k + 1 < size) && (nums[k] < nums[k + 1])) {
            k++;
        }
        if (nums[k] < nums[(k - 1) / 2]) {
            break;
        }

        swap(nums, k, (k - 1) / 2);
    }
}
void Init(int *nums, int size) {
    int i;
    for (i = size / 2 - 1; i >= 0; i--) {
        down(nums, size, i);
    }
}
void Push(int *nums, int size, int x) {
    nums[size] = x;

    int i;
    for (i = size; ((i > 0) && (nums[(i - 1) / 2] < nums[i])); i = (i - 1) / 2) {
        swap(nums, i, (i - 1) / 2);
    }
}
int Pop(int *nums, int size) {
    int retVal = 0;

    swap(nums, 0, size - 1);
    down(nums, size - 1, 0);
    retVal = nums[size - 1];

    return retVal;
}

#endif  // HEAP_H
long long maxKelements(int *nums, int numsSize, int k) {
    long long retVal = 0;

    Init(nums, numsSize);

    int maxElement;
    int i;
    for (i = 0; i < k; i++) {
        maxElement = Pop(nums, numsSize);
        retVal += maxElement;
        Push(nums, numsSize - 1, (maxElement + 2) / 3);
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{10, 10, 10, 10, 10}, 5, 5}, {{1, 10, 3, 3, 3}, 5, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [10,10,10,10,10], k = 5
     *  Output: 50
     *
     *  Input: nums = [1,10,3,3,3], k = 3
     *  Output: 17
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maxKelements(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
