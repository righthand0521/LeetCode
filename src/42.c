#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DYNAMIC_PROGRAMMING (1)
#define MONOTONIC_STACK (1)
#define TWO_POINTERS (1)
int trap(int* height, int heightSize) {
    int retVal = 0;

    if (heightSize == 0) {
        return retVal;
    }

#if (DYNAMIC_PROGRAMMING)
    printf("DYNAMIC_PROGRAMMING\n");

    int i;

    int leftMax[heightSize];
    memset(leftMax, 0, sizeof(leftMax));
    leftMax[0] = height[0];
    for (i = 1; i < heightSize; ++i) {
        leftMax[i] = fmax(leftMax[i - 1], height[i]);
    }

    int rightMax[heightSize];
    memset(rightMax, 0, sizeof(rightMax));
    rightMax[heightSize - 1] = height[heightSize - 1];
    for (i = heightSize - 2; i >= 0; --i) {
        rightMax[i] = fmax(rightMax[i + 1], height[i]);
    }

    for (i = 0; i < heightSize; ++i) {
        retVal += fmin(leftMax[i], rightMax[i]) - height[i];
    }
#elif (MONOTONIC_STACK)
    printf("MONOTONIC_STACK\n");

    int monotonicStack[heightSize];
    memset(monotonicStack, 0, sizeof(monotonicStack));
    int top = 0;

    int popValue;
    int left, currWidth, currHeight;
    int i;
    for (i = 0; i < heightSize; ++i) {
        while ((top != 0) && (height[i] > height[monotonicStack[top - 1]])) {
            popValue = monotonicStack[--top];
            if (top == 0) {
                break;
            }
            left = monotonicStack[top - 1];
            currWidth = i - left - 1;
            currHeight = fmin(height[left], height[i]) - height[popValue];

            retVal += (currWidth * currHeight);
        }

        monotonicStack[top++] = i;
    }
#elif (TWO_POINTERS)
    printf("TWO_POINTERS\n");

    int leftMax = 0;
    int rightMax = 0;
    int left = 0;
    int right = heightSize - 1;
    while (left < right) {
        leftMax = fmax(leftMax, height[left]);
        rightMax = fmax(rightMax, height[right]);

        if (height[left] < height[right]) {
            retVal += leftMax - height[left];
            ++left;
        } else {
            retVal += rightMax - height[right];
            --right;
        }
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 10000)
    struct testCaseType {
        int height[MAX_SIZE];
        int heightSize;
    } testCase[] = {{{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, 12}, {{4, 2, 0, 3, 2, 5}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
     *  Output: 6
     *
     *  Input: height = [4,2,0,3,2,5]
     *  Output: 9
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: height = [");
        for (j = 0; j < testCase[i].heightSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].height[j]);
        }
        printf("]\n");

        answer = trap(testCase[i].height, testCase[i].heightSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
