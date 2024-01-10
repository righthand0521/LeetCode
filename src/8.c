#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myAtoi(char *s) {
    int retVal = 0;

    int sSize = strlen(s);

    bool signStatus = false;
    bool numberStatus = false;
    bool isMinus = false;
    long sum = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if ((s[i] == '-') || (s[i] == '+') || (s[i] == ' ')) {
            if ((signStatus == true) || (numberStatus == true)) {
                break;
            }

            if (s[i] == '-') {
                isMinus = true;
            }

            if (s[i] != ' ') {
                signStatus = true;
            }
        } else if ((s[i] > '9') || (s[i] < '0')) {
            break;
        } else {
            numberStatus = true;
            sum = 10 * sum + (s[i] - '0');
            if (sum > INT_MAX) {
                break;
            }
        }
    }

    if (isMinus == true) {
        sum = -(sum);
    }

    /* 5. If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1],
     *  then clamp the integer so that it remains in the range.
     *  Specifically, integers less than -2^31 should be clamped to -2^31,
     *  and integers greater than 2^31 - 1 should be clamped to 2^31 - 1.
     */
    if (sum > INT_MAX) {
        retVal = INT_MAX;
    } else if (sum < INT_MIN) {
        retVal = INT_MIN;
    } else {
        retVal = sum;
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"42"},
                    {"   -42"},
                    {"4193 with words"},
                    {"words and 987"},
                    {"+-12"},
                    {"20000000000000000000"},
                    {"  0000000000012345678"},
                    {"00000-42a1234"},
                    {"  +  413"},
                    {"-91283472332"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "42"
     *  Output: 42
     *
     *  Input: s = "   -42"
     *  Output: -42
     *
     *  Input: s = "4193 with words"
     *  Output: 4193
     *
     *  Input: s = "words and 987"
     *  Output: 0
     *
     *  Input: s = "+-12"
     *  Output: 0
     *
     *  Input: s = "20000000000000000000"
     *  Output: 2147483647
     *
     *  Input: s = "  0000000000012345678"
     *  Output: 12345678
     *
     *  Input: s = "00000-42a1234"
     *  Output: 0
     *
     *  Input: s = "  +  413"
     *  Output: 0
     *
     *  Input: s = "-91283472332"
     *  Output: -2147483648
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = myAtoi(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
