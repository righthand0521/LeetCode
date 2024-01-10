#include <math.h>
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

    int len1 = strlen(version1);
    int len2 = strlen(version2);
    int idx1 = 0;
    int idx2 = 0;
    int len = fmax(len1, len2);
    char buf1[len];
    char buf2[len];
    char tmp[len];
    int count;
    int count1;
    int count2;
    int i;
    while ((idx1 < len1) || (idx2 < len2)) {
        //
        count1 = 0;
        memset(buf1, 0, sizeof(buf1));
        while ((idx1 < len1) && (version1[idx1] != '.')) {
            buf1[count1++] = version1[idx1];
            ++idx1;
        }
        ++idx1;

        count2 = 0;
        memset(buf2, 0, sizeof(buf2));
        while ((idx2 < len2) && (version2[idx2] != '.')) {
            buf2[count2++] = version2[idx2];
            ++idx2;
        }
        ++idx2;

        //
        count = fmax(count1, count2);

        memset(tmp, 0, sizeof(tmp));
        memcpy(tmp, buf1, sizeof(tmp));
        for (i = 0; i < count - count1; ++i) {
            buf1[i] = '0';
        }
        for (i = 0; i < count1; ++i) {
            buf1[i + count - count1] = tmp[i];
        }

        memset(tmp, 0, sizeof(tmp));
        memcpy(tmp, buf2, sizeof(tmp));
        for (i = 0; i < count - count2; ++i) {
            buf2[i] = '0';
        }
        for (i = 0; i < count2; ++i) {
            buf2[i + count - count2] = tmp[i];
        }

        //
        for (i = 0; i < count; ++i) {
            if (buf1[i] < buf2[i]) {
                retVal = COMPARE_SMALL;
                return retVal;
            } else if (buf1[i] > buf2[i]) {
                retVal = COMPARE_LARGE;
                return retVal;
            }
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
