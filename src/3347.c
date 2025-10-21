#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef HASH_H
#define HASH_H

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} HashItem;
HashItem* hashFindItem(HashItem** obj, int key) {
    HashItem* pEntry = NULL;

    HASH_FIND_INT(*obj, &key, pEntry);

    return pEntry;
}
bool hashAddItem(HashItem** obj, int key, int val) {
    bool retVal = false;

    if (hashFindItem(obj, key)) {
        return retVal;
    }

    HashItem* pEntry = (HashItem*)malloc(sizeof(HashItem));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
bool hashSetItem(HashItem** obj, int key, int val) {
    HashItem* pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        hashAddItem(obj, key, val);
    } else {
        pEntry->val = val;
    }
    return true;
}
int hashGetItem(HashItem** obj, int key, int defaultVal) {
    int retVal = defaultVal;

    HashItem* pEntry = hashFindItem(obj, key);
    if (pEntry != NULL) {
        retVal = pEntry->val;
    }

    return retVal;
}
void hashFree(HashItem** obj) {
    HashItem* curr = NULL;
    HashItem* tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}
void addMode(int* nums, int numsSize, int k, HashItem** modes, int value) {
    hashAddItem(modes, value, 1);
    if (value - k >= nums[0]) {
        hashAddItem(modes, value - k, 1);
    }
    if (value + k <= nums[numsSize - 1]) {
        hashAddItem(modes, value + k, 1);
    }
}

#endif  // HASH_H
int leftBound(int* nums, int numsSize, int value) {
    int retVal = 0;

    int left = 0;
    int right = numsSize - 1;
    int middle;
    while (left < right) {
        middle = (left + right) / 2;
        if (nums[middle] < value) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}
int rightBound(int* nums, int numsSize, int value) {
    int retVal = 0;

    int left = 0;
    int right = numsSize - 1;
    int middle;
    while (left < right) {
        middle = (left + right + 1) / 2;
        if (nums[middle] > value) {
            right = middle - 1;
        } else {
            left = middle;
        }
    }
    retVal = left;

    return retVal;
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxFrequency(int* nums, int numsSize, int k, int numOperations) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    HashItem* numCount = NULL;
    HashItem* modes = NULL;

    int lastNumIndex = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == nums[lastNumIndex]) {
            continue;
        }

        hashSetItem(&numCount, nums[lastNumIndex], i - lastNumIndex);
        if (i - lastNumIndex > retVal) {
            retVal = i - lastNumIndex;
        }
        addMode(nums, numsSize, k, &modes, nums[lastNumIndex]);
        lastNumIndex = i;
    }

    hashSetItem(&numCount, nums[lastNumIndex], numsSize - lastNumIndex);
    if (numsSize - lastNumIndex > retVal) {
        retVal = numsSize - lastNumIndex;
    }
    addMode(nums, numsSize, k, &modes, nums[lastNumIndex]);

    int modesSize = HASH_COUNT(modes);
    int sortModes[modesSize];
    int pos = 0;
    for (HashItem* pEntry = modes; pEntry; pEntry = pEntry->hh.next) {
        sortModes[pos++] = pEntry->key;
    }
    qsort(sortModes, modesSize, sizeof(int), compareInteger);

    int mode, left, right, count, tempAns;
    for (int i = 0; i < modesSize; i++) {
        mode = sortModes[i];
        left = leftBound(nums, numsSize, mode - k);
        right = rightBound(nums, numsSize, mode + k);

        if (hashFindItem(&numCount, mode)) {
            count = hashGetItem(&numCount, mode, 0);
            tempAns = fmin(right - left + 1, count + numOperations);
        } else {
            tempAns = fmin(right - left + 1, numOperations);
        }

        if (tempAns > retVal) {
            retVal = tempAns;
        }
    }

    //
    hashFree(&numCount);
    hashFree(&modes);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
        int numOperations;
    } testCase[] = {{{1, 4, 5}, 3, 1, 2}, {{5, 11, 20, 20}, 4, 5, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,4,5], k = 1, numOperations = 2
     *  Output: 2
     *
     *  Input: nums = [5,11,20,20], k = 5, numOperations = 1
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d, numOperations = %d\n", testCase[i].k, testCase[i].numOperations);

        answer = maxFrequency(testCase[i].nums, testCase[i].numsSize, testCase[i].k, testCase[i].numOperations);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
