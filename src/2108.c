#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPalindrome(char *word, int wordSize) {
    bool retVal = true;

    int left = 0;
    int right = wordSize - 1;
    while (left < right) {
        if (word[left++] != word[right--]) {
            retVal = false;
            break;
        }
    }

    return retVal;
}
char *firstPalindrome(char **words, int wordsSize) {
    char *retVal = "";

    int i;
    for (i = 0; i < wordsSize; ++i) {
        if (isPalindrome(words[i], strlen(words[i])) == true) {
            retVal = words[i];
            break;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char *words[MAX_SIZE];
        int wordsSize;
    } testCase[] = {
        {{"abc", "car", "ada", "racecar", "cool"}, 5}, {{"notapalindrome", "racecar"}, 2}, {{"def", "ghi"}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["abc","car","ada","racecar","cool"]
     *  Output: "ada"
     *
     *  Input: words = ["notapalindrome","racecar"]
     *  Output: "racecar"
     *
     *  Input: words = ["def","ghi"]
     *  Output: ""
     */

    char *answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        answer = firstPalindrome(testCase[i].words, testCase[i].wordsSize);
        printf("Output: \"%s\"\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
