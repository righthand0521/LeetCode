#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canConstruct(char* ransomNote, char* magazine) {
    bool retVal = false;

    int lenRansomNote = strlen(ransomNote);
    int lenMagazine = strlen(magazine);
    if (lenRansomNote > lenMagazine) {
        return retVal;
    }
    int RECORD[26] = {0};

    int i;
    for (i = 0; i < lenRansomNote; ++i) {
        --RECORD[ransomNote[i] - 'a'];
        ++RECORD[magazine[i] - 'a'];
    }
    for (i = lenRansomNote; i < lenMagazine; ++i) {
        ++RECORD[magazine[i] - 'a'];
    }

    for (i = 0; i < 26; ++i) {
        if (RECORD[i] < 0) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* ransomNote;
        char* magazine;
    } testCase[] = {{"a", "b"}, {"aa", "ab"}, {"aa", "aab"}, {"ihgg", "ch"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: ransomNote = \"%s\", magazine = \"%s\"\n", testCase[i].ransomNote, testCase[i].magazine);

        answer = canConstruct(testCase[i].ransomNote, testCase[i].magazine);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
