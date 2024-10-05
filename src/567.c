#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS_SIZE (26)  // s1 and s2 consist of lowercase English letters.
bool isCountEqual(int* pCount1, int* pCount2) {
    bool retVal = false;

    int i;
    for (i = 0; i < MAX_LETTERS_SIZE; ++i) {
        if (pCount1[i] != pCount2[i]) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}
bool checkInclusion(char* s1, char* s2) {
    bool retVal = false;

    int s1Size = strlen(s1);
    int s2Size = strlen(s2);
    if (s2Size < s1Size) {
        return retVal;
    }

    int count1[MAX_LETTERS_SIZE];
    memset(count1, 0, sizeof(count1));
    int count2[MAX_LETTERS_SIZE];
    memset(count2, 0, sizeof(count2));

    int i;
    for (i = 0; i < s1Size; ++i) {
        ++count1[(unsigned int)(s1[i] - 'a')];
        ++count2[(unsigned int)(s2[i] - 'a')];
    }
    if (isCountEqual(count1, count2) == true) {
        retVal = true;
        return retVal;
    }

    for (i = s1Size; i < s2Size; ++i) {
        ++count2[(unsigned int)(s2[i] - 'a')];
        --count2[(unsigned int)(s2[i - s1Size] - 'a')];
        if (isCountEqual(count1, count2) == true) {
            retVal = true;
            return retVal;
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
    /* Example
     *  Input: s1 = "ab", s2 = "eidbaooo"
     *  Output: true
     *
     *  Input: s1 = "ab", s2 = "eidboaoo"
     *  Output: false
     */

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
