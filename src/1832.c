#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOWERCASE_MIN_LENGTH (26)
#define LOWERCASE_HASH_TABLE (0x3ffffff)
bool checkIfPangram(char *sentence) {
    bool retVal = false;

    if (strlen(sentence) < LOWERCASE_MIN_LENGTH) {
        return retVal;
    }

    unsigned int record = 0;
    while (*sentence) {
        record |= (1 << (*(sentence) - 'a'));
        sentence++;
    }

    if (record == LOWERCASE_HASH_TABLE) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char sentence[MAX_SIZE];
    } testCase[] = {{"thequickbrownfoxjumpsoverthelazydog"}, {"leetcode"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: sentence = \"%s\"\n", testCase[i].sentence);

        answer = checkIfPangram(testCase[i].sentence);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
