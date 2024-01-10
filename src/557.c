#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reverseWords(char* s) {
    char* pRetVal = s;

    int begin = 0;
    int end = 0;
    char tmp;
    int len = strlen(s);
    int idx;
    for (idx = 0; idx <= len; ++idx) {
        if ((s[idx] != ' ') && (s[idx] != '\0')) {
            continue;
        }

        end = idx - 1;
        while (end > begin) {
            tmp = s[begin];
            s[begin++] = s[end];
            s[end--] = tmp;
        }
        begin = idx + 1;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"Let's take LeetCode contest"}, {"God Ding"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "Let's take LeetCode contest"
     *  Output: "s'teL ekat edoCteeL tsetnoc"
     *
     *  Input: s = "God Ding"
     *  Output: "doG gniD"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = reverseWords(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
