#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool lemonadeChange(int* bills, int billsSize) {
    bool retVal = true;

    int five = 0;
    int ten = 0;
    int bill;
    int i;
    for (i = 0; i < billsSize; ++i) {
        bill = bills[i];
        if (bill == 5) {
            five += 1;
        } else if (bill == 10) {
            if (five == 0) {
                retVal = false;
                break;
            }
            five -= 1;
            ten += 1;
        } else if (bill == 20) {
            if ((ten >= 1) && (five >= 1)) {
                ten -= 1;
                five -= 1;
            } else if (five >= 3) {
                five -= 3;
            } else {
                retVal = false;
                break;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int bills[MAX_SIZE];
        int billsSize;
    } testCase[] = {{{5, 5, 5, 10, 20}, 5}, {{5, 5, 10, 10, 20}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: bills = [5,5,5,10,20]
     *  Output: true
     *
     *  Input: bills = [5,5,10,10,20]
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: bills = [");
        for (j = 0; j < testCase[i].billsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].bills[j]);
        }
        printf("]\n");

        answer = lemonadeChange(testCase[i].bills, testCase[i].billsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
