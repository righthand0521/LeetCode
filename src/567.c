#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT_SIZE (26)  // s1 and s2 consist of lowercase English letters.
bool IsCountEqual(int* pCount1, int* pCount2) {
    bool retVal = false;

    int i;
    for (i = 0; i < COUNT_SIZE; ++i) {
        if (pCount1[i] != pCount2[i]) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}
bool checkInclusion(char* s1, char* s2) {
    bool retVal = false;

    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len2 < len1) {
        return retVal;
    }

    int Count1[COUNT_SIZE];
    memset(Count1, 0, sizeof(Count1));
    int Count2[COUNT_SIZE];
    memset(Count2, 0, sizeof(Count2));

    int i;
    for (i = 0; i < len1; ++i) {
        ++Count1[(unsigned int)(s1[i] - 'a')];
        ++Count2[(unsigned int)(s2[i] - 'a')];
    }
    if (IsCountEqual(Count1, Count2) == true) {
        retVal = true;
        return retVal;
    }

    for (i = len1; i < len2; ++i) {
        ++Count2[(unsigned int)(s2[i] - 'a')];
        --Count2[(unsigned int)(s2[i - len1] - 'a')];
        if (IsCountEqual(Count1, Count2) == true) {
            retVal = true;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        char s1[MAX_SIZE];
        char s2[MAX_SIZE];
    } testCase[] = {{"ab", "eidbaooo"}, {"ab", "eidboaoo"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s1 = \"%s\", s2 = \"%s\"\n", testCase[i].s1, testCase[i].s2);

        answer = checkInclusion(testCase[i].s1, testCase[i].s2);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
