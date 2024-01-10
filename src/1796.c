#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int secondHighest(char* s) {
    int retVal = -1;

    // use hash table to record appeared numerical digit
    int hashTable[10] = {0};
    while (*s) {
        if ((*s >= '0') && (*s <= '9')) {
            ++hashTable[*s - '0'];
        }
        ++s;
    }

    // travel hash table to return the second largest
    int count = 0;
    int i;
    for (i = 9; i >= 0; --i) {
        if (hashTable[i] != 0) {
            ++count;
            if (count == 2) {
                retVal = i;
                break;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"dfa12321afd"}, {"abc1111"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = secondHighest(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
