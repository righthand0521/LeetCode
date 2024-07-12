#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximumGain(char* s, int x, int y) {
    int retVal = 0;

    int sSize = strlen(s);

    // Ensure "ab" always has more points than "ba"
    int left = 0;
    int right = sSize - 1;
    int temp;
    if (x < y) {
        temp = x;
        x = y;
        y = temp;
        while (left < right) {
            temp = s[left];
            s[left++] = s[right];
            s[right--] = temp;
        }
    }

    int aCount = 0;
    int bCount = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == 'a') {
            ++aCount;
        } else if (s[i] == 'b') {
            if (aCount > 0) {
                --aCount;
                retVal += x;
            } else {
                ++bCount;
            }
        } else {
            retVal += fmin(bCount, aCount) * y;
            aCount = 0;
            bCount = 0;
        }
    }
    retVal += fmin(bCount, aCount) * y;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        int x;
        int y;
    } testCase[] = {{"cdbcbbaaabab", 4, 5}, {"aabbaaxybbaabb", 5, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "cdbcbbaaabab", x = 4, y = 5
     *  Output: 19
     *
     *  Input: s = "aabbaaxybbaabb", x = 5, y = 4
     *  Output: 20
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", x = %d, y = %d\n", testCase[i].s, testCase[i].x, testCase[i].y);

        answer = maximumGain(testCase[i].s, testCase[i].x, testCase[i].y);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
