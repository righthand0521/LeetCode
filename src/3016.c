#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS (26)  // word consists of lowercase English letters.
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int minimumPushes(char* word) {
    int retVal = 0;

    int frequency[MAX_LETTERS];
    memset(frequency, 0, sizeof(frequency));

    int wordSize = strlen(word);
    int i;
    for (i = 0; i < wordSize; ++i) {
        ++frequency[word[i] - 'a'];
    }
    qsort(frequency, MAX_LETTERS, sizeof(int), compareInteger);

    for (i = 0; i < MAX_LETTERS; ++i) {
        if (frequency[i] == 0) {
            break;
        }
        retVal += (i / 8 + 1) * frequency[i];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char word[MAX_SIZE];
    } testCase[] = {{"abcde"}, {"xyzxyzxyzxyz"}, {"aabbccddeeffgghhiiiiii"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "abcde"
     *  Output: 5
     *
     *  Input: word = "xyzxyzxyzxyz"
     *  Output: 12
     *
     *  Input: word = "aabbccddeeffgghhiiiiii"
     *  Output: 24
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\"\n", testCase[i].word);

        answer = minimumPushes(testCase[i].word);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
