#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool areAlmostEqual(char* s1, char* s2) {
    bool retVal = false;

    int s1Size = strlen(s1);
    int count = 0;
    int record[2] = {0};
    for (int i = 0; i < s1Size; ++i) {
        if (s1[i] == s2[i]) {
            continue;
        }
        record[0] |= (1 << (s1[i] - 'a'));
        record[1] |= (1 << (s2[i] - 'a'));
        ++count;
    }

    if (count == 0) {
        retVal = true;
    } else if ((count == 2) && (record[0] == record[1])) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s1[MAX_SIZE];
        char s2[MAX_SIZE];
        ;
    } testCase[] = {{"bank", "kanb"}, {"attack", "defend"}, {"kelb", "kelb"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s1 = "bank", s2 = "kanb"
     *  Output: true
     *
     *  Input: s1 = "attack", s2 = "defend"
     *  Output: false
     *
     *  Input: s1 = "kelb", s2 = "kelb"
     *  Output: true
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s1 = \"%s\", s2 = \"%s\"\n", testCase[i].s1, testCase[i].s2);

        answer = areAlmostEqual(testCase[i].s1, testCase[i].s2);
        printf("Output: %s\n", ((answer == true) ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
