#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* robotWithString(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);

    pRetVal = (char*)malloc((sSize + 1) * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((sSize + 1) * sizeof(char)));
    int returnSize = 0;

    int frequency[26] = {0};  // s consists of only English lowercase letters.
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; i < sSize; i++) {
        frequency[s[i] - 'a']++;
    }

    int characterStackTop = 0;
    char* characterStack = (char*)malloc(sSize * sizeof(char));
    if (characterStack == NULL) {
        perror("malloc");
        return pRetVal;
    }
    char minCharacter = 'a';
    for (int i = 0; i < sSize; i++) {
        characterStack[characterStackTop++] = s[i];
        frequency[s[i] - 'a']--;

        while ((minCharacter != 'z') && (frequency[minCharacter - 'a'] == 0)) {
            minCharacter++;
        }

        while ((characterStackTop > 0) && (characterStack[characterStackTop - 1] <= minCharacter)) {
            pRetVal[returnSize++] = characterStack[--characterStackTop];
        }
    }
    pRetVal[returnSize] = '\0';

    //
    free(characterStack);
    characterStack = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"zza"}, {"bac"}, {"bdda"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "zza"
     *  Output: "azz"
     *
     *  Input: s = "bac"
     *  Output: "abc"
     *
     *  Input: s = "bdda"
     *  Output: "addb"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = robotWithString(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
