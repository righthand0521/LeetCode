#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool areSentencesSimilar(char* sentence1, char* sentence2) {
    bool retVal = false;

#define STRTOK_PATTERN (" ")
    char* p = NULL;

    char* words1[strlen(sentence1)];
    int words1Size = 0;
    p = strtok(sentence1, STRTOK_PATTERN);
    while (p != NULL) {
        words1[words1Size++] = p;
        p = strtok(NULL, STRTOK_PATTERN);
    }

    char* words2[strlen(sentence2)];
    int words2Size = 0;
    p = strtok(sentence2, STRTOK_PATTERN);
    while (p != NULL) {
        words2[words2Size++] = p;
        p = strtok(NULL, STRTOK_PATTERN);
    }

    int head = 0;
    while ((head < words1Size) && (head < words2Size)) {
        if (strcmp(words1[head], words2[head]) != 0) {
            break;
        }
        ++head;
    }

    int tail = 0;
    while ((tail < words1Size - head) && (tail < words2Size - head)) {
        if (strcmp(words1[words1Size - 1 - tail], words2[words2Size - 1 - tail]) != 0) {
            break;
        }
        ++tail;
    }

    if ((head + tail) == fmin(words1Size, words2Size)) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char sentence1[MAX_SIZE];
        char sentence2[MAX_SIZE];
    } testCase[] = {{"My name is Haley", "My Haley"},
                    {"of", "A lot of words"},
                    {"Eating right now", "Eating"},
                    {"Luky", "Lucccky"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
     *  Output: true
     *
     *  Input: sentence1 = "of", sentence2 = "A lot of words"
     *  Output: false
     *
     *  Input: sentence1 = "Eating right now", sentence2 = "Eating"
     *  Output: true
     *
     *  Input: sentence1 = "Luky", sentence2 = "Lucccky"
     *  Output: false
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: sentence1 = \"%s\",  sentence2 = \"%s\"\n", testCase[i].sentence1, testCase[i].sentence2);

        answer = areSentencesSimilar(testCase[i].sentence1, testCase[i].sentence2);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
