#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canConstruct(char* ransomNote, char* magazine) {
    bool retVal = false;

    int ransomNoteSize = strlen(ransomNote);
    int magazineSize = strlen(magazine);
    if (ransomNoteSize > magazineSize) {
        return retVal;
    }

    // ransomNote and magazine consist of lowercase English letters.
#define LETTER_SIZE (26)
    int hashTable[LETTER_SIZE];
    memset(hashTable, 0, sizeof(hashTable));

    int i;
    for (i = 0; i < ransomNoteSize; ++i) {
        --hashTable[ransomNote[i] - 'a'];
        ++hashTable[magazine[i] - 'a'];
    }
    for (i = ransomNoteSize; i < magazineSize; ++i) {
        ++hashTable[magazine[i] - 'a'];
    }

    for (i = 0; i < LETTER_SIZE; ++i) {
        if (hashTable[i] < 0) {
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
    /* Example
     *  Input: ransomNote = "a", magazine = "b"
     *  Output: false
     *
     *  Input: ransomNote = "aa", magazine = "ab"
     *  Output: false
     *
     *  Input: ransomNote = "aa", magazine = "aab"
     *  Output: true
     *
     *  Input: ransomNote = "ihgg", magazine = "ch"
     *  Output: true
     */

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
