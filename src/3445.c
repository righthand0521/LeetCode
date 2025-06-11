#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getStatus(int aCurrent, int bCurrent) {
    int retVal = ((aCurrent & 1) << 1) | (bCurrent & 1);

    return retVal;
}
int maxDifference(char* s, int k) {
    int retVal = INT_MIN;

    int best[4];
    int aCurrent, bCurrent, aPrevious, bPrevious;
    int left, right, leftStatus, rightStatus, current;
    int sSize = strlen(s);
    for (char a = '0'; a <= '4'; ++a) {      // s consists only of digits '0' to '4'.
        for (char b = '0'; b <= '4'; ++b) {  // s consists only of digits '0' to '4'.
            if (a == b) {
                continue;
            }

            for (int i = 0; i < 4; ++i) {
                best[i] = INT_MAX;
            }
            aCurrent = 0;
            bCurrent = 0;
            aPrevious = 0;
            bPrevious = 0;
            left = -1;
            for (right = 0; right < sSize; ++right) {
                aCurrent += ((s[right] == a) ? 1 : 0);
                bCurrent += ((s[right] == b) ? 1 : 0);
                while ((right - left >= k) && (bCurrent - bPrevious >= 2)) {
                    leftStatus = getStatus(aPrevious, bPrevious);
                    if (aPrevious - bPrevious < best[leftStatus]) {
                        best[leftStatus] = aPrevious - bPrevious;
                    }
                    ++left;
                    aPrevious += ((s[left] == a) ? 1 : 0);
                    bPrevious += ((s[left] == b) ? 1 : 0);
                }

                rightStatus = getStatus(aCurrent, bCurrent);
                if (best[rightStatus ^ 0b10] != INT_MAX) {
                    current = aCurrent - bCurrent - best[rightStatus ^ 0b10];
                    if (current > retVal) {
                        retVal = current;
                    }
                }
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(3 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
        int k;
    } testCase[] = {{"12233", 4}, {"1122211", 3}, {"110", 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "12233", k = 4
     *  Output: -1
     *
     *  Input: s = "1122211", k = 3
     *  Output: 1
     *
     *  Input: s = "110", k = 3
     *  Output: -1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; i++) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        answer = maxDifference(testCase[i].s, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
