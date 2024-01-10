#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int atMostDifferent(int* nums, int numsSize, int k) {
    int retVal = 0;

    // 1 <= nums.length <= 2 * 10^4, 1 <= nums[i], k <= nums.length.
#define MAX_HASHTABLE (int)(2 * 1e4 + 4)
    int HashTable[MAX_HASHTABLE];
    memset(HashTable, 0, sizeof(HashTable));
    int countHashTable = 0;
    int head = 0;
    int tail = 0;
    while (tail < numsSize) {
        if (HashTable[nums[tail]] == 0) {
            ++countHashTable;
        }
        ++HashTable[nums[tail]];
        ++tail;

        while (countHashTable > k) {
            --HashTable[nums[head]];
            if (HashTable[nums[head]] == 0) {
                --countHashTable;
            }
            ++head;
        }
        retVal += (tail - head);
    }

    return retVal;
}
int subarraysWithKDistinct(int* nums, int numsSize, int k) {
    int retVal = 0;

    // https://leetcode.com/problems/subarrays-with-k-different-integers/solutions/523136/JavaC++Python-Sliding-Window/
    retVal = atMostDifferent(nums, numsSize, k) - atMostDifferent(nums, numsSize, k - 1);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 2, 1, 2, 3}, 5, 2}, {{1, 2, 1, 3, 4}, 5, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = subarraysWithKDistinct(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
