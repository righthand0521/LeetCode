#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NONE_STR "none"
#define EQUILATERAL_STR "equilateral"
#define ISOSCELES_STR "isosceles"
#define SCALENE_STR "scalene"
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
char* triangleType(int* nums, int numsSize) {
    char* pRetVal;

    qsort(nums, numsSize, sizeof(int), compareInteger);
    if (nums[0] + nums[1] <= nums[2]) {
        pRetVal = NONE_STR;
    } else if (nums[0] == nums[2]) {
        pRetVal = EQUILATERAL_STR;
    } else if ((nums[0] == nums[1]) || (nums[1] == nums[2])) {
        pRetVal = ISOSCELES_STR;
    } else {
        pRetVal = SCALENE_STR;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 3, 3}, 3}, {{3, 4, 5}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,3,3]
     *  Output: "equilateral"
     *
     *  Input: nums = [3,4,5]
     *  Output: "scalene"
     */

    char* answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = triangleType(testCase[i].nums, testCase[i].numsSize);
        printf("Output: \"%s\"\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
