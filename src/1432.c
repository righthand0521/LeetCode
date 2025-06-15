#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace(char* s, char x, char y) {
    for (int i = 0; s[i]; ++i) {
        if (s[i] == x) {
            s[i] = y;
        }
    }
}
int maxDiff(int num) {
    int retVal = 0;

#define MAX_NUMS_SIZE (16)  // 1 <= num <= 10^8

    // Find a high position and replace it with 9.
    char maxNum[MAX_NUMS_SIZE];
    snprintf(maxNum, sizeof(maxNum), "%d", num);
    for (int i = 0; maxNum[i]; ++i) {
        if (maxNum[i] != '9') {
            replace(maxNum, maxNum[i], '9');
            break;
        }
    }

    // Replace the most significant bit with 1
    // Or find a high-order digit that is not equal to the highest digit and replace it with 0.
    char minNum[MAX_NUMS_SIZE];
    snprintf(minNum, sizeof(minNum), "%d", num);
    for (int i = 0; minNum[i]; ++i) {
        char digit = minNum[i];
        if (i == 0) {
            if (digit != '1') {
                replace(minNum, digit, '1');
                break;
            }
        } else {
            if (digit != '0' && digit != minNum[0]) {
                replace(minNum, digit, '0');
                break;
            }
        }
    }

    retVal = atoi(maxNum) - atoi(minNum);

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int num;
    } testCase[] = {{555}, {9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = 555
     *  Output: 888
     *
     *  Input: num = 9
     *  Output: 8
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = %d\n", testCase[i].num);

        answer = maxDiff(testCase[i].num);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
