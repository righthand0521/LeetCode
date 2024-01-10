#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define UTHASH (1)
#if (UTHASH)
struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};

void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
#else
#define TIME_LIMIT_EXCEEDED (1)
#endif
bool checkSubarraySum(int* nums, int numsSize, int k) {
    bool retVal = false;

#if (UTHASH)
    struct hashTable* map = NULL;

    struct hashTable* first;
    first = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (first == NULL) {
        perror("malloc");
        freeAll(map);
        return retVal;
    }
    first->key = nums[0] % k;
    first->value = 0;
    HASH_ADD_INT(map, key, first);

    struct hashTable* temp;
    int i;
    for (i = 1; i < numsSize; ++i) {
        nums[i] = (nums[i] + nums[i - 1]) % k;
        if (nums[i] == 0) {
            retVal = true;
            break;
        }

        HASH_FIND_INT(map, &nums[i], temp);
        if (temp == NULL) {
            temp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (temp == NULL) {
                perror("malloc");
                break;
            }
            temp->key = nums[i];
            temp->value = i;
            HASH_ADD_INT(map, key, temp);
        } else if ((i - temp->value) > 1) {
            retVal = true;
            break;
        }
    }

    freeAll(map);
#else
    if (numsSize == 1)  // nums has a continuous subarray of size at least two
    {
        return retVal;
    } else if (k == 1)  // multiple of 1
    {
        retVal = true;
        return retVal;
    }

    // use hash table to record sum of nums status
    bool* pHashTable = (bool*)malloc(k * sizeof(bool));
    if (pHashTable == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pHashTable, 0, k * sizeof(bool));

    int sum = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        // multiple of k in above HashTable is like stand still(0 is always a multiple of k)
        if (nums[i] % k == 0) {
            // at least two
            if ((i < (numsSize - 1)) && ((nums[i + 1] % k) == 0)) {
                retVal = true;
                break;
            }
            continue;
        }

        sum += nums[i];
        if ((sum % k) == 0) {
            retVal = true;
            break;
        } else if (pHashTable[sum % k] == true) {
            retVal = true;
            break;
        }
        pHashTable[sum % k] = true;
    }

#if (TIME_LIMIT_EXCEEDED)
    free(pHashTable);
    pHashTable = NULL;
#endif

#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_NUMSSIZE (1000)
    struct testCaseType {
        int nums[MAX_NUMSSIZE];
        int numsSize;
        int k;
    } testCase[] = {{{23, 2, 4, 6, 7}, 5, 6},
                    {{23, 2, 6, 4, 7}, 5, 6},
                    {{23, 2, 6, 4, 7}, 5, 13},
                    {{5, 0, 0, 0}, 4, 3},
                    {{1, 0}, 2, 2},
                    {{2, 4, 3}, 3, 6},
                    {{1, 2, 12}, 3, 6},
                    {{50000000, 50000000}, 2, 100000000}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = checkSubarraySum(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
