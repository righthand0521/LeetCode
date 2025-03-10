#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isVowel(char c) {
    bool retVal = (c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u');

    return retVal;
}
long long count(char* word, int k) {
    long long retVal = 0;

    int wordSize = strlen(word);

    int vowel[26];
    memset(vowel, 0, sizeof(vowel));
    int vowelSize = 0;
    int consonants = 0;
    for (int i = 0, j = 0; i < wordSize; i++) {
        while ((j < wordSize) && ((consonants < k) || (vowelSize < 5))) {
            if (isVowel(word[j]) == true) {
                vowel[word[j] - 'a']++;
                vowelSize += vowel[word[j] - 'a'] == 1;
            } else {
                consonants++;
            }
            j++;
        }

        if ((consonants >= k) && (vowelSize == 5)) {
            retVal += wordSize - j + 1;
        }

        if (isVowel(word[i]) == true) {
            vowel[word[i] - 'a']--;
            if (vowel[word[i] - 'a'] == 0) {
                vowelSize--;
            }
        } else {
            consonants--;
        }
    }

    return retVal;
}
long long countOfSubstrings(char* word, int k) {
    long long retVal = count(word, k) - count(word, k + 1);

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* word;
        int k;
    } testCase[] = {{"aeioqq", 1}, {"aeiou", 0}, {"ieaouqqieaouqq", 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "aeioqq", k = 1
     *  Output: 0
     *
     *  Input: word = "aeiou", k = 0
     *  Output: 1
     *
     *  Input: word = "ieaouqqieaouqq", k = 1
     *  Output: 3
     */

    long long answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\", k = %d\n", testCase[i].word, testCase[i].k);

        answer = countOfSubstrings(testCase[i].word, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
