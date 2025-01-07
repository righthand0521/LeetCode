#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void computeLPSArray(char* substring, int substringSize, int* lps) {
    int length = 0;
    int currentIndex = 1;
    while (currentIndex < substringSize) {
        if (substring[currentIndex] == substring[length]) {
            length++;
            lps[currentIndex] = length;
            currentIndex++;
            continue;
        }

        if (length > 0) {
            length = lps[length - 1];  // Backtrack using LPS array to find a shorter match.
        } else {
            currentIndex++;
        }
    }
}
bool isSubstringOf(char* substring, int substringSize, char* main, int mainSize, int* lps) {
    bool retVal = false;

    int mainIndex = 0;
    int substringIndex = 0;
    while (mainIndex < mainSize) {
        if (main[mainIndex] == substring[substringIndex]) {
            substringIndex++;
            mainIndex++;
            if (substringIndex == substringSize) {
                retVal = true;
                return retVal;
            }
            continue;
        }

        if (substringIndex > 0) {
            substringIndex = lps[substringIndex - 1];  // Use the LPS to skip unnecessary comparisons.
        } else {
            mainIndex++;
        }
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** stringMatching(char** words, int wordsSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (char**)malloc(sizeof(char*) * wordsSize);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int* pLPS = NULL;
    int currentWordSize, otherWordSize;
    int currentWordIndex, otherWordIndex;
    for (currentWordIndex = 0; currentWordIndex < wordsSize; currentWordIndex++) {
        currentWordSize = strlen(words[currentWordIndex]);
        pLPS = (int*)calloc(currentWordSize, sizeof(int));
        if (pLPS == NULL) {
            perror("calloc");
            return pRetVal;
        }
        computeLPSArray(words[currentWordIndex], currentWordSize, pLPS);

        // Compare the current word with all other words.
        for (otherWordIndex = 0; otherWordIndex < wordsSize; otherWordIndex++) {
            if (currentWordIndex == otherWordIndex) {
                continue;  // Skip comparing the word with itself.
            }

            // Check if the current word is a substring of another word.
            currentWordSize = strlen(words[currentWordIndex]);
            otherWordSize = strlen(words[otherWordIndex]);
            if (isSubstringOf(words[currentWordIndex], currentWordSize, words[otherWordIndex], otherWordSize, pLPS) ==
                true) {
                pRetVal[(*returnSize)++] = words[currentWordIndex];
                break;  // No need to check further for this word.
            }
        }

        free(pLPS);
        pLPS = NULL;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        int returnSize;
    } testCase[] = {{{"mass", "as", "hero", "superhero"}, 4, 0},
                    {{"leetcode", "et", "code"}, 3, 0},
                    {{"blue", "green", "bu"}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["mass","as","hero","superhero"]
     *  Output: ["as","hero"]
     *
     *  Input: words = ["leetcode","et","code"]
     *  Output: ["et","code"]
     *
     *  Input: words = ["blue","green","bu"]
     *  Output: []
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        pAnswer = stringMatching(testCase[i].words, testCase[i].wordsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
