#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numDifferentIntegers(char* word) {
    int retVal = 0;

    int len = strlen(word);
    char Record[len][len];
    memset(Record, 0, sizeof(Record));
    int row = 0;
    int col = 0;

    int i, j;
    for (i = 0; i < len; ++i) {
        if ((word[i] >= '0') && (word[i] <= '9')) {
            // the leading zeros are ignored
            if ((col == 1) && (Record[row][0] == '0')) {
                --col;
            }
            Record[row][col] = word[i];
            ++col;
            continue;
        }
        if (col != 0) {
            ++row;
        }
        col = 0;
    }

    for (i = 0; i < len; ++i) {
        if (strlen(Record[i]) == 0) {
            break;
        }
        ++retVal;

        // check different integers
        for (j = 0; j < i; ++j) {
            if (strcmp(Record[i], Record[j]) == 0) {
                --retVal;
                break;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char word[MAX_SIZE];
    } testCase[] = {{"a123bc34d8ef34"},
                    {"leet1234code234"},
                    {"a1b01c001"},
                    {"a123bc34d8ef"},
                    {"0a0"},
                    {"4w31am0ets6sl5go5ufytjtjpb7b0sxqbee2blg9ss"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\"\n", testCase[i].word);

        answer = numDifferentIntegers(testCase[i].word);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
