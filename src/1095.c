#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MOUNTAINARRAY_H
#define MOUNTAINARRAY_H

typedef struct {
    int* pNums;
    int pNumsSize;
} MountainArray;
MountainArray* MountainArrayCreate(int* nums, int numsSize) {
    MountainArray* pRetVal = NULL;

    pRetVal = (MountainArray*)malloc(sizeof(MountainArray));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    pRetVal->pNums = (int*)malloc(numsSize * sizeof(int));
    if (pRetVal->pNums == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(pRetVal->pNums, 0, (numsSize * sizeof(int)));
    memcpy(pRetVal->pNums, nums, (numsSize * sizeof(int)));
    pRetVal->pNumsSize = numsSize;

    return pRetVal;
}
int get(MountainArray* mountainArr, int index) {
    int retVal = 0;

    if (index < mountainArr->pNumsSize) {
        retVal = mountainArr->pNums[index];
    }

    return retVal;
}
int length(MountainArray* mountainArr) {
    int retVal = 0;

    retVal = mountainArr->pNumsSize;

    return retVal;
}
void MountainArrayFree(MountainArray* obj) {
    if (obj == NULL) {
        return;
    }

    if (obj->pNums) {
        free(obj->pNums);
        obj->pNums = NULL;
    }
    free(obj);
    obj = NULL;
}

#endif  // MOUNTAINARRAY_H
/**
 * *********************************************************************
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * int get(MountainArray *, int index);
 * int length(MountainArray *);
 */
int findInMountainArray(int target, MountainArray* mountainArr) {
    int retVal = -1;

    int arrSize = length(mountainArr);
    int left, right, middle, peak, value;

    // Find the index of the peak element
    left = 0;
    right = arrSize - 1;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (get(mountainArr, middle) < get(mountainArr, middle + 1)) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    peak = left;

    // Search in the strictly increasing part of the array. If found, will be returned in the loop itself.
    left = 0;
    right = peak;
    while (left <= right) {
        middle = left + (right - left) / 2;
        value = get(mountainArr, middle);
        if (value == target) {
            retVal = middle;
            return retVal;
        } else if (value < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    // Search in the strictly decreasing part of the array. If found, will be returned in the loop itself.
    left = peak + 1;
    right = arrSize - 1;
    while (left <= right) {
        middle = left + (right - left) / 2;
        value = get(mountainArr, middle);
        if (value == target) {
            retVal = middle;
            return retVal;
        } else if (value > target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int target;
    } testCase[] = {{{1, 2, 3, 4, 5, 3, 1}, 7, 3}, {{0, 1, 2, 4, 2, 1}, 6, 3}, {{0, 5, 3, 1}, 4, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: array = [1,2,3,4,5,3,1], target = 3
     *  Output: 2
     *
     *  Input: array = [0,1,2,4,2,1], target = 3
     *  Output: -1
     *
     *  Input: array = [0,5,3,1], target = 1
     *  Output: 3
     */

    MountainArray* obj = NULL;
    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        obj = MountainArrayCreate(testCase[i].arr, testCase[i].arrSize);
        if (obj == NULL) {
            return EXIT_FAILURE;
        }
        answer = findInMountainArray(testCase[i].target, obj);
        printf("Output: %d\n", answer);

        printf("\n");

        MountainArrayFree(obj);
        obj = NULL;
    }

    return EXIT_SUCCESS;
}
