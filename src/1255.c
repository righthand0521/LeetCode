#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS (26)  // words[i], letters[i] contains only lower case English letters.
// Check if adding this word exceeds the frequency of any letter
bool isValidWord(int* subsetLetters, int subsetLettersSize, int* freq, int freqSize) {
    bool retVal = true;

    int c;
    for (c = 0; c < subsetLettersSize; c++) {
        if (freq[c] < subsetLetters[c]) {
            retVal = false;
            break;
        }
    }

    return retVal;
}
void check(int w, char** words, int wordsSize, int* score, int scoreSize, int* subsetLetters, int subsetLettersSize,
           int* freq, int freqSize, int totalScore, int* maxScore) {
    if (w == -1) {
        // If all words have been iterated, check the score of this subset
        (*maxScore) = fmax((*maxScore), totalScore);
        return;
    }

    // Not adding words[w] to the current subset
    check(w - 1, words, wordsSize, score, scoreSize, subsetLetters, subsetLettersSize, freq, freqSize, totalScore,
          maxScore);

    // Adding words[w] to the current subset
    int L = strlen(words[w]);
    int i, c;
    for (int i = 0; i < L; i++) {
        c = words[w][i] - 'a';
        subsetLetters[c]++;
        totalScore += score[c];
    }

    if (isValidWord(subsetLetters, subsetLettersSize, freq, freqSize) == true) {
        // Consider the next word if this subset is still valid
        check(w - 1, words, wordsSize, score, scoreSize, subsetLetters, subsetLettersSize, freq, freqSize, totalScore,
              maxScore);
    }

    // Rollback effects of this word
    for (i = 0; i < L; i++) {
        c = words[w][i] - 'a';
        subsetLetters[c]--;
        totalScore -= score[c];
    }
}
int maxScoreWords(char** words, int wordsSize, char* letters, int lettersSize, int* score, int scoreSize) {
    int retVal = 0;

    // Count how many times each letter occurs
    int pFreqSize = MAX_LETTERS;
    int* pFreq = (int*)calloc(pFreqSize, sizeof(int));
    if (pFreq == NULL) {
        perror("calloc");
        return retVal;
    }
    int i;
    for (i = 0; i < lettersSize; ++i) {
        pFreq[letters[i] - 'a']++;
    }

    int pSubsetLettersSize = MAX_LETTERS;
    int* pSubsetLetters = (int*)calloc(pSubsetLettersSize, sizeof(int));
    if (pSubsetLetters == NULL) {
        perror("calloc");
        free(pFreq);
        pFreq = NULL;
        return retVal;
    }
    check(wordsSize - 1, words, wordsSize, score, scoreSize, pSubsetLetters, pSubsetLettersSize, pFreq, pFreqSize, 0,
          &retVal);

    //
    free(pFreq);
    pFreq = NULL;
    free(pSubsetLetters);
    pSubsetLetters = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        char letters[MAX_SIZE];
        int lettersSize;
        int score[MAX_SIZE];
        int scoreSize;
    } testCase[] = {{{"dog", "cat", "dad", "good"},
                     4,
                     {'a', 'a', 'c', 'd', 'd', 'd', 'g', 'o', 'o'},
                     9,
                     {1, 0, 9, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     26},
                    {{"xxxz", "ax", "bx", "cx"},
                     4,
                     {'z', 'a', 'b', 'c', 'x', 'x', 'x'},
                     7,
                     {4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 10},
                     26},
                    {{"leetcode"},
                     1,
                     {'l', 'e', 't', 'c', 'o', 'd'},
                     6,
                     {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                     26}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["dog","cat","dad","good"], letters = ["a","a","c","d","d","d","g","o","o"],
     *  score = [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]
     *  Output: 23
     *
     *  Input: words = ["xxxz","ax","bx","cx"], letters = ["z","a","b","c","x","x","x"],
     *  score = [4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,10]
     *  Output: 27
     *
     *  Input: words = ["leetcode"], letters = ["l","e","t","c","o","d"],
     *  score = [0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("], letters = [");
        for (j = 0; j < testCase[i].lettersSize; ++j) {
            printf("%s\"%c\"", (j == 0) ? "" : ",", testCase[i].letters[j]);
        }
        printf("], score = [");
        for (j = 0; j < testCase[i].scoreSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].score[j]);
        }
        printf("]\n");

        answer = maxScoreWords(testCase[i].words, testCase[i].wordsSize, testCase[i].letters, testCase[i].lettersSize,
                               testCase[i].score, testCase[i].scoreSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
