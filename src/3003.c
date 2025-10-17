#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxPartitionsAfterOperations(char* s, int k) {
    int retVal = 0;

    int sSize = strlen(s);

    int left[sSize][3];
    memset(left, 0, sizeof(left));
    int right[sSize][3];
    memset(right, 0, sizeof(right));
    int num, mask, count, binary;

    num = 0;
    mask = 0;
    count = 0;
    for (int i = 0; i < sSize - 1; i++) {
        binary = 1 << (s[i] - 'a');
        if (!(mask & binary)) {
            count++;
            if (count <= k) {
                mask |= binary;
            } else {
                num++;
                mask = binary;
                count = 1;
            }
        }
        left[i + 1][0] = num;
        left[i + 1][1] = mask;
        left[i + 1][2] = count;
    }

    num = 0;
    mask = 0;
    count = 0;
    for (int i = sSize - 1; i > 0; i--) {
        binary = 1 << (s[i] - 'a');
        if (!(mask & binary)) {
            count++;
            if (count <= k) {
                mask |= binary;
            } else {
                num++;
                mask = binary;
                count = 1;
            }
        }
        right[i - 1][0] = num;
        right[i - 1][1] = mask;
        right[i - 1][2] = count;
    }

    int maxLetters = 26;  // s consists only of lowercase English letters.
    int seg, totMask, totCount, minVal;
    for (int i = 0; i < sSize; i++) {
        seg = left[i][0] + right[i][0] + 2;
        totMask = left[i][1] | right[i][1];
        totCount = 0;
        while (totMask) {
            totMask = totMask & (totMask - 1);
            totCount++;
        }

        if ((left[i][2] == k) && (right[i][2] == k) && (totCount < maxLetters)) {
            seg++;
        } else {
            minVal = fmin(totCount + 1, maxLetters);
            if (minVal <= k) {
                seg--;
            }
        }
        retVal = fmax(retVal, seg);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char s[MAX_SIZE];
        int k;
    } testCase[] = {{"accca", 2}, {"aabaab", 3}, {"xxyz", 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "accca", k = 2
     *  Output: 3
     *
     *  Input: s = "aabaab", k = 3
     *  Output: 1
     *
     *  Input: s = "xxyz", k = 1
     *  Output: 4
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; i++) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        answer = maxPartitionsAfterOperations(testCase[i].s, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
