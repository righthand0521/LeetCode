#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* convert(char* s, int numRows) {
    char* pRetVal = NULL;

    int len = strlen(s);

    int returnSize = len + 1;
    pRetVal = (char*)calloc(returnSize, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    if (numRows == 1) {
        memcpy(pRetVal, s, returnSize * sizeof(char));
        return pRetVal;
    }

    /* numRows - 1 + numRows - 1 = 2 x numRows - 2 = 2 x (numRows - 1)
     *
     *  n = 3: 2x(3-1) = 4
     *  +-------+-------+----+
     *  | 0 |   | 4 |   | 8  |
     *  | 1 | 3 | 5 | 7 | 9  | ...
     *  | 2 |   | 6 |   | 10 |
     *  +-------+-------+----+
     *
     *  n = 4: 2x(4-1) = 6
     *  +-----------+-------------+----+
     *  | 0 |   |   | 6 |    |    | 12 |
     *  | 1 |   | 5 | 7 |    | 11 | 13 | ...
     *  | 2 | 4 |   | 8 | 10 |    | 14 |
     *  | 3 |   |   | 9 |    |    | 15 |
     *  +-----------+-------------+----+
     *
     *  n = 5: 2x(5-1) = 8
     *  +---------------+-------------------+----+
     *  | 0 |   |   |   |  8 |    |    |    | 16 |
     *  | 1 |   |   | 7 |  9 |    |    | 15 | 17 |
     *  | 2 |   | 6 |   | 10 |    | 14 |    | 18 | ...
     *  | 3 | 5 |   |   | 11 | 13 |    |    | 19 |
     *  | 4 |   |   |   | 12 |    |    |    | 20 |
     *  +---------------+-------------------+----+
     */
    int charsInSection = 2 * (numRows - 1);

    int returnIdx = 0;
    int sIdx, innerIdx;
    int row;
    for (row = 0; row < numRows; ++row) {
        sIdx = row;

        while (sIdx < len) {
            pRetVal[returnIdx++] = s[sIdx];

            if ((row != 0) && (row != numRows - 1)) {
                innerIdx = sIdx + charsInSection - (2 * row);
                if (innerIdx < len) {
                    pRetVal[returnIdx++] = s[innerIdx];
                }
            }

            sIdx += charsInSection;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char s[MAX_SIZE];
        int numRows;
    } testCase[] = {{"PAYPALISHIRING", 3}, {"PAYPALISHIRING", 4}, {"A", 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "PAYPALISHIRING", numRows = 3
     *  Output: "PAHNAPLSIIGYIR"
     *
     *  Input: s = "PAYPALISHIRING", numRows = 4
     *  Output: "PINALSIGYAHRPI"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", numRows = %d\n", testCase[i].s, testCase[i].numRows);

        pAnswer = convert(testCase[i].s, testCase[i].numRows);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
