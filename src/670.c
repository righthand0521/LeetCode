#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximumSwap(int num) {
    int retVal = 0;

    char numStr[32];
    memset(numStr, 0, sizeof(numStr));
    snprintf(numStr, sizeof(numStr), "%d", num);
    int numStrSize = strlen(numStr);

    int maxDigitIndex = -1;
    int swapIdx1 = -1;
    int swapIdx2 = -1;
    int i;
    for (i = numStrSize - 1; i >= 0; --i) {
        if ((maxDigitIndex == -1) || (numStr[i] > numStr[maxDigitIndex])) {
            maxDigitIndex = i;
        } else if (numStr[i] < numStr[maxDigitIndex]) {
            swapIdx1 = i;
            swapIdx2 = maxDigitIndex;
        }
    }

    int tmp;
    if ((swapIdx1 != -1) && (swapIdx2 != -1)) {
        tmp = numStr[swapIdx1];
        numStr[swapIdx1] = numStr[swapIdx2];
        numStr[swapIdx2] = tmp;
    }
    retVal = atoi(numStr);

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int num;
    } testCase[] = {{2736}, {9973}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = 2736
     *  Output: 7236
     *
     *  Input: num = 9973
     *  Output: 9973
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = %d\n", testCase[i].num);

        answer = maximumSwap(testCase[i].num);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
