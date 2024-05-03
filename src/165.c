#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Return the following:
 *  If version1 < version2, return -1.
 *  If version1 > version2, return 1.
 *  Otherwise, return 0.
 */
#define COMPARE_SMALL (-1)
#define COMPARE_LARGE (1)
#define COMPARE_EQUAL (0)
int compareVersion(char* version1, char* version2) {
    int retVal = COMPARE_EQUAL;

    int version1Size = strlen(version1);
    int version2Size = strlen(version2);

    int sum1, sum2 = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < version1Size) || (idx2 < version2Size)) {
        sum1 = 0;
        while ((idx1 < version1Size) && (version1[idx1] != '.')) {
            sum1 = 10 * sum1 + (version1[idx1] - '0');
            idx1++;
        }
        idx1++;

        sum2 = 0;
        while ((idx2 < version2Size) && (version2[idx2] != '.')) {
            sum2 = 10 * sum2 + (version2[idx2] - '0');
            idx2++;
        }
        idx2++;

        if (sum1 > sum2) {
            retVal = COMPARE_LARGE;
            break;
        } else if (sum1 < sum2) {
            retVal = COMPARE_SMALL;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        char version1[MAX_SIZE];
        char version2[MAX_SIZE];
    } testCase[] = {{"1.01", "1.001"}, {"1.0", "1.0.0"}, {"0.1", "1.1"}, {"1.1", "1.10"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: version1 = "1.01", version2 = "1.001"
     *  Output: 0
     *
     *  Input: version1 = "1.0", version2 = "1.0.0"
     *  Output: 0
     *
     *  Input: version1 = "0.1", version2 = "1.1"
     *  Output: -1
     *
     *  Input: version1 = "1.1", version2 = "1.10"
     *  Output: -1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: version1 = \"%s\", version2 = \"%s\"\n", testCase[i].version1, testCase[i].version2);

        answer = compareVersion(testCase[i].version1, testCase[i].version2);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
