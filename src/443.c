#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compress(char* chars, int charsSize) {
    int retVal = 0;

    // 1 <= chars.length <= 2000 and Integer range: [2, 2147483647]
    char buf[12];
    int count = 1;
    int i, j;
    for (i = 1; i < charsSize; ++i) {
        if (chars[i - 1] == chars[i]) {
            ++count;
            continue;
        }

        chars[retVal++] = chars[i - 1];
        if (count != 1) {
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%d", count);
            for (j = 0; j < strlen(buf); ++j) {
                chars[retVal++] = buf[j];
            }
        }
        count = 1;
    }
    chars[retVal++] = chars[i - 1];
    if (count != 1) {
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%d", count);
        for (j = 0; j < strlen(buf); ++j) {
            chars[retVal++] = buf[j];
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        char chars[MAX_SIZE];
        int charsSize;
    } testCase[] = {{{'a', 'a', 'b', 'b', 'c', 'c', 'c'}, 7},
                    {{'a'}, 1},
                    {{'a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'}, 13}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: chars = ["a","a","b","b","c","c","c"]
     *  Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
     *
     *  Input: chars = ["a"]
     *  Output: Return 1, and the first character of the input array should be: ["a"]
     *
     *  Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
     *  Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: chars = [");
        for (j = 0; j < testCase[i].charsSize; ++j) {
            printf("%s\"%c\"", (j == 0 ? "" : ","), testCase[i].chars[j]);
        }
        printf("]\n");

        answer = compress(testCase[i].chars, testCase[i].charsSize);
        printf("Output: %d, [", answer);
        for (j = 0; j < answer; ++j) {
            printf("%s\"%c\"", (j == 0 ? "" : ","), testCase[i].chars[j]);
        }
        printf("]\n");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
