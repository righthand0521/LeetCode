#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool CanPartition(int num, int target) {
    bool retVal = false;

    if ((target < 0) || (target > num)) {
        return retVal;
    } else if (num == target) {
        retVal = true;
        return retVal;
    }
    retVal = CanPartition(num / 10, target - num % 10);
    retVal = retVal || CanPartition(num / 100, target - num % 100);
    retVal = retVal || CanPartition(num / 1000, target - num % 1000);

    return retVal;
}
int punishmentNumber(int n) {
    int retVal = 0;

    int currentNum, squareNum;
    for (currentNum = 1; currentNum <= n; currentNum++) {
        squareNum = currentNum * currentNum;
        if (CanPartition(squareNum, currentNum) == true) {
            retVal += squareNum;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{10}, {37}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 10
     *  Output: 182
     *
     *  Input: n = 37
     *  Output: 1478
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = punishmentNumber(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
