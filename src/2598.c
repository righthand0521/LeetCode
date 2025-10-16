#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findSmallestInteger(int* nums, int numsSize, int value) {
    int retVal = 0;

    int mp[value];
    memset(mp, 0, sizeof(mp));
    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];
        int v = (x % value + value) % value;
        mp[v]++;
    }

    while (mp[retVal % value] > 0) {
        mp[retVal % value]--;
        retVal++;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int value;
    } testCase[] = {{{1, -10, 7, 13, 6, 8}, 6, 5}, {{1, -10, 7, 13, 6, 8}, 6, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,-10,7,13,6,8], value = 5
     *  Output: 4
     *
     *  Input: nums = [1,-10,7,13,6,8], value = 7
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], value = %d\n", testCase[i].value);

        answer = findSmallestInteger(testCase[i].nums, testCase[i].numsSize, testCase[i].value);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
