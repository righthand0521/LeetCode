#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int possibleStringCount(char* word, int k) {
    int retVal = 1;

    int wordSize = strlen(word);
    int count = 1;
    int frequency[wordSize];
    memset(frequency, 0, sizeof(frequency));
    int frequencySize = 0;
    for (int i = 1; i < wordSize; ++i) {
        if (word[i] == word[i - 1]) {
            ++count;
        } else {
            frequency[frequencySize++] = count;
            count = 1;
        }
    }
    frequency[frequencySize++] = count;

    long long longlongAnswer = 1;
    for (int i = 0; i < frequencySize; ++i) {
        longlongAnswer = longlongAnswer * frequency[i] % MODULO;
    }

    if (frequencySize >= k) {
        retVal = longlongAnswer;
        return retVal;
    }

    int g[k];
    for (int i = 0; i < k; ++i) {
        g[i] = 1;
    }
    int fNext[k], gNext[k];
    for (int i = 0; i < frequencySize; ++i) {
        memset(fNext, 0, sizeof(fNext));
        for (int j = 1; j < k; ++j) {
            fNext[j] = g[j - 1];
            if (j - frequency[i] - 1 >= 0) {
                fNext[j] = (fNext[j] - g[j - frequency[i] - 1] + MODULO) % MODULO;
            }
        }

        memset(gNext, 0, sizeof(gNext));
        gNext[0] = fNext[0];
        for (int j = 1; j < k; ++j) {
            gNext[j] = (gNext[j - 1] + fNext[j]) % MODULO;
        }

        memcpy(g, gNext, sizeof(g));
    }

    retVal = (longlongAnswer - g[k - 1] + MODULO) % MODULO;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* word;
        int k;
    } testCase[] = {{"aabbccdd", 7}, {"aabbccdd", 8}, {"aaabbb", 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "aabbccdd", k = 7
     *  Output: 5
     *
     *  Input: word = "aabbccdd", k = 8
     *  Output: 1
     *
     *  Input: word = "aaabbb", k = 3
     *  Output: 8
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\", k = %d\n", testCase[i].word, testCase[i].k);

        answer = possibleStringCount(testCase[i].word, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
