#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isCircularSentence(char* sentence) {
    bool retVal = false;

    int sentenceSize = strlen(sentence);
    if (sentence[0] != sentence[sentenceSize - 1]) {
        return retVal;
    }
    // A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
    int i;
    for (i = 0; i < sentenceSize; ++i) {
        if ((sentence[i] == ' ') && (sentence[i - 1] != sentence[i + 1])) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        char sentence[MAX_SIZE];
    } testCase[] = {{"leetcode exercises sound delightful"}, {"eetcode"}, {"Leetcode is cool"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: sentence = "leetcode exercises sound delightful"
     *  Output: true
     *
     *  Input: sentence = "eetcode"
     *  Output: true
     *
     *  Input: sentence = "Leetcode is cool"
     *  Output: false
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: sentence = \"%s\"\n", testCase[i].sentence);

        answer = isCircularSentence(testCase[i].sentence);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
