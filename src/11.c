#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxArea(int* height, int heightSize) {
    int retVal = 0;

    int leftValue, rightValue, minValue;
    int left = 0;
    int right = heightSize - 1;
    while (left < right) {
        leftValue = height[left];
        rightValue = height[right];
        minValue = fmin(leftValue, rightValue);
        retVal = fmax(retVal, minValue * (right - left));

        if (leftValue > rightValue) {
            right--;
        } else {
            left++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int height[MAX_SIZE];
        int heightSize;
    } testCase[] = {{{1, 8, 6, 2, 5, 4, 8, 3, 7}, 9}, {{1, 1}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: height = [1,8,6,2,5,4,8,3,7]
     *  Output: 49
     *
     *  Input: height = [1,1]
     *  utput: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: height = [");
        for (j = 0; j < testCase[i].heightSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].height[j]);
        }
        printf("]\n");

        answer = maxArea(testCase[i].height, testCase[i].heightSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
