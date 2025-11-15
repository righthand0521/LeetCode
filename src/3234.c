#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numberOfSubstrings(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

    int pre[sSize + 1];
    memset(pre, 0, sizeof(pre));
    pre[0] = -1;
    for (int i = 0; i < sSize; i++) {
        if ((i == 0) || ((i > 0) && (s[i - 1] == '0'))) {
            pre[i + 1] = i;
        } else {
            pre[i + 1] = pre[i];
        }
    }

    for (int i = 1; i <= sSize; i++) {
        int cnt0 = (s[i - 1] == '0') ? (1) : (0);
        int j = i;
        while ((j > 0) && (cnt0 * cnt0 <= sSize)) {
            int cnt1 = (i - pre[j]) - cnt0;
            if (cnt0 * cnt0 <= cnt1) {
                int add = j - pre[j];
                if (cnt1 - cnt0 * cnt0 + 1 < add) {
                    add = cnt1 - cnt0 * cnt0 + 1;
                }
                retVal += add;
            }
            j = pre[j];
            cnt0++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"00011"}, {"101101"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "00011"
     *  Output: 5
     *
     *  Input: s = "101101"
     *  Output: 16
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = numberOfSubstrings(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
