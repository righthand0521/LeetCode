#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int maxFrequencyElements(int* nums, int numsSize) {
    int retVal = 0;

#define MAX_NUMS_SIZE (100)  // 1 <= nums.length <= 100; 1 <= nums[i] <= 100;
    int hashTable[MAX_NUMS_SIZE];
    memset(hashTable, 0, sizeof(hashTable));

    int i;
    for (i = 0; i < numsSize; ++i) {
        hashTable[nums[i] - 1]++;
    }
    qsort(hashTable, MAX_NUMS_SIZE, sizeof(int), compareInteger);

    int frequency;
    int maxFrequency = 0;
    for (i = 0; i < MAX_NUMS_SIZE; ++i) {
        frequency = hashTable[i];
        if (frequency >= maxFrequency) {
            maxFrequency = frequency;
            retVal += frequency;
        } else {
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 2, 3, 1, 4}, 6}, {{1, 2, 3, 4, 5}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,2,3,1,4]
     *  Output: 4
     *
     *  Input: nums = [1,2,3,4,5]
     *  Output: 5
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxFrequencyElements(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
