#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* largestGoodInteger(char* num) {
    char* pRetVal = NULL;

    int numSize = strlen(num);
    if (numSize < 3) {  // 3 <= num.length <= 1000
        return pRetVal;
    }

    int returnSize = 3 + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    char goodChar = 0;
    int i;
    for (i = 2; i < numSize; ++i) {
        if ((num[i - 2] != num[i - 1]) || (num[i - 1] != num[i])) {
            continue;
        } else if (goodChar >= num[i - 2]) {
            continue;
        }
        goodChar = num[i - 2];
    }
    if (goodChar != 0) {
        snprintf(pRetVal, returnSize, "%c%c%c", goodChar, goodChar, goodChar);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char num[MAX_SIZE];
    } testCase[] = {{"6777133339"}, {"2300019"}, {"42352338"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = "6777133339"
     *  Output: "777"
     *
     *  Input: num = "2300019"
     *  Output: "000"
     *
     *  Input: num = "42352338"
     *  Output: ""
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = \"%s\"\n", testCase[i].num);

        pAnswer = largestGoodInteger(testCase[i].num);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
