#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DYNAMIC_PROGRAMMING (1)
#define FORMULA (1)
int uniquePaths(int m, int n) {
    int retVal = 0;

#if (DYNAMIC_PROGRAMMING)
    /* Example: 3x7
     *     |  0  1  2  3  4  5  6
     *  ---+----------------------
     *  0  |  1  1  1  1  1  1  1
     *  1  |  1  2  3  4  5  6  7
     *  2  |  1  3  6 10 15 21 28
     */
    printf("DYNAMIC_PROGRAMMING\n");

    int path[m][n];

    int i, j;
    for (i = 0; i < m; ++i) {
        path[i][0] = 1;
    }
    for (i = 0; i < n; ++i) {
        path[0][i] = 1;
    }

    for (i = 1; i < m; ++i) {
        for (j = 1; j < n; ++j) {
            path[i][j] = path[i - 1][j] + path[i][j - 1];
        }
    }
    retVal = path[m - 1][n - 1];
#elif (FORMULA)
    /* Example: 3x7
     *    ((3-1) + (7-1))!      (2 + 6)!        8!        8 x 7
     *  ------------------- = ----------- = ----------- = ----- = 28
     *  ((3-1)!) x ((7-1)!)   (2!) x (6!)   (2!) x (6!)   2 x 1
     */
    printf("FORMULA\n");

    int max = ((m > n) ? m : n);
    int min = ((m < n) ? m : n);

    unsigned long answer = 1;
    int i;
    for (i = 1; i <= (min - 1); ++i) {
        answer = answer * (max - 1 + i) / i;
    }
    retVal = answer;
#endif

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int m;
        int n;
    } testCase[] = {{3, 7}, {3, 2}, {5, 10}, {16, 16}, {13, 23}, {51, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: m = 3, n = 7
     *  Output: 28
     *
     *  Input: m = 3, n = 2
     *  Output: 3
     *
     *  Input: m = 5, n = 10
     *  Output: 715
     *
     *  Input: m = 16, n = 16
     *  Output: 155117520
     *
     *  Input: m = 13, n = 23
     *  Output: 548354040
     *
     *  Input: m = 51, n = 9
     *  Output: 1916797311
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: m = %d, n = %d\n", testCase[i].m, testCase[i].n);

        answer = uniquePaths(testCase[i].m, testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
