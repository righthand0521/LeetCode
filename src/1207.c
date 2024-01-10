#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool uniqueOccurrences(int* arr, int arrSize) {
    bool retVal = false;

    int i;

// 1 <= arr.length <= 1000, -1000 <= arr[i] <= 1000
#define MAX_RANGE (1000)
#define MAX_SIZE (MAX_RANGE + 1 + MAX_RANGE)

    int occurrences[MAX_SIZE];
    memset(occurrences, 0, sizeof(occurrences));
    for (i = 0; i < arrSize; ++i) {
        // f(x) = 1000 + x, -1000 <= x <= 1000, 0 <= f(x) <= 2000.
        occurrences[MAX_RANGE + arr[i]] += 1;
    }

    int times[MAX_SIZE];
    memset(times, 0, sizeof(times));
    int index;
    for (i = 0; i < MAX_SIZE; ++i) {
        index = occurrences[i];
        if (index == 0) {
            continue;
        }

        if (times[index] != 0) {
            return retVal;
        }
        times[index] += 1;
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int arr[1000];
        int arrSize;
    } testCase[] = {{{1, 2, 2, 1, 1, 3}, 6}, {{1, 2}, 2}, {{-3, 0, 1, -3, 1, 1, 1, -3, 10, 0}, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [1,2,2,1,1,3]
     *  Output: true
     *
     *  Input: arr = [1,2]
     *  Output: false
     *
     *  Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
     *  Output: true
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].arr[j]);
        }
        printf("]\n");

        answer = uniqueOccurrences(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}