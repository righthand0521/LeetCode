#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int totalMoney(int n) {
    int retVal = 0;

    int weeks = n / 7;
    int days = n % 7;

    int firstWeek = (1 + 7) * 7 / 2;
    int lastWeek = firstWeek + (weeks - 1) * 7;
    int weeksMoney = (firstWeek + lastWeek) * weeks / 2;

    int dyasMoney = 0;
    int monday = 1 + weeks;
    int i;
    for (i = 0; i < days; ++i) {
        dyasMoney += (monday + i);
    }

    retVal = weeksMoney + dyasMoney;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{4}, {10}, {20}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4
     *  Output: 10
     *
     *  Input: n = 10
     *  Output: 37
     *
     *  Input: n = 20
     *  Output: 96
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = totalMoney(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
