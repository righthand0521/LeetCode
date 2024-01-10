#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countCollisions(char *directions) {
    int retVal = 0;

    // https://leetcode.cn/problems/count-collisions-on-a-road/solutions/1352569/da-an-hui-bei-zhuang-ting-de-che-liang-s-yyfl/

    int directionsSize = strlen(directions);
    char stack[directionsSize + 1];
    memset(stack, 0, sizeof(stack));
#define STACK_EMPTY (-1)
    int stackTop = -1;
    int i;
    for (i = 0; i < directionsSize; ++i) {
        if (directions[i] == 'L') {
            if (stackTop == STACK_EMPTY) {
                continue;
            }
            while ((stackTop != STACK_EMPTY) && (stack[stackTop] == 'R')) {
                retVal += 1;
                stack[stackTop--] = 0;
            }
            retVal += 1;
            stack[++stackTop] = 'S';
        } else if (directions[i] == 'R') {
            stack[++stackTop] = directions[i];
        } else if (directions[i] == 'S') {
            while ((stackTop != STACK_EMPTY) && (stack[stackTop] == 'R')) {
                retVal += 1;
                stack[stackTop--] = 0;
            }
            stack[++stackTop] = directions[i];
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char directions[MAX_SIZE];
    } testCase[] = {{"RLRSLL"}, {"LLRR"}, {"SSRSSRLLRSLLRSRSSRLRRRRLLRRLSSRR"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: directions = "RLRSLL"
     *  Output: 5
     *
     *  Input: directions = "LLRR"
     *  Output: 0
     *
     *  Input: directions = "SSRSSRLLRSLLRSRSSRLRRRRLLRRLSSRR"
     *  Output: 20
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].directions);

        answer = countCollisions(testCase[i].directions);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
