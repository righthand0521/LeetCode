#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF_SIZE (1024)
#define MAX_LETTERS (26)  // dictionary[i] consists of only lower-case letters.
typedef struct Trie {
    bool isEnd;
    struct Trie *children[MAX_LETTERS];
} Trie;
Trie *creatTrie() {
    Trie *pRetVal = NULL;

    pRetVal = (Trie *)malloc(sizeof(Trie));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i;
    for (i = 0; i < MAX_LETTERS; i++) {
        pRetVal->children[i] = NULL;
    }
    pRetVal->isEnd = false;

    return pRetVal;
}
void freeTrie(Trie *root) {
    int i;
    for (i = 0; i < MAX_LETTERS; i++) {
        if (root->children[i] != NULL) {
            freeTrie(root->children[i]);
        }
    }
    free(root);
    root = NULL;
}
void findRoot(const char *word, Trie *trie, char *pRetVal) {
    int wordSize = strlen(word);
    Trie *pCurrent = trie;

    int idx = 0;
    char c;
    int i;
    for (i = 0; i < wordSize; i++) {
        if (pCurrent->isEnd == true) {
            pRetVal[idx] = 0;
            return;
        }

        c = word[i];
        if (pCurrent->children[c - 'a'] == NULL) {
            snprintf(pRetVal, MAX_BUF_SIZE, "%s", word);
            return;
        }
        pRetVal[idx++] = c;
        pCurrent = pCurrent->children[c - 'a'];
    }
    pRetVal[idx] = 0;
}
char *replaceWords(char **dictionary, int dictionarySize, char *sentence) {
    char *pRetVal = NULL;

    //
    int sentenceSize = strlen(sentence);
    pRetVal = (char *)malloc((sentenceSize + 4) * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((sentenceSize + 1) * sizeof(char)));

    //
    Trie *pDictionaryTrie = creatTrie();
    Trie *pCurrent;
    char c;
    int len;
    int i, j;
    for (i = 0; i < dictionarySize; i++) {
        pCurrent = pDictionaryTrie;
        len = strlen(dictionary[i]);
        for (j = 0; j < len; j++) {
            c = dictionary[i][j];
            if (pCurrent->children[c - 'a'] == NULL) {
                pCurrent->children[c - 'a'] = creatTrie();
            }
            pCurrent = pCurrent->children[c - 'a'];
        }
        pCurrent->isEnd = true;
    }

    //
    int idx = 0;
    char *pTmp = NULL;
#define SEPARATED (" ")
    char *pStr = strtok(sentence, SEPARATED);
    while (pStr != NULL) {
        pTmp = (char *)malloc(MAX_BUF_SIZE * sizeof(char));
        if (pTmp == NULL) {
            perror("malloc");
            break;
        }
        memset(pTmp, 0, (MAX_BUF_SIZE * sizeof(char)));

        findRoot(pStr, pDictionaryTrie, pTmp);
        idx += sprintf(pRetVal + idx, "%s ", pTmp);

        free(pTmp);
        pTmp = NULL;

        pStr = strtok(NULL, SEPARATED);
    }
    if (idx >= 1) {
        pRetVal[idx - 1] = '\0';
    }

    //
    freeTrie(pDictionaryTrie);
    pDictionaryTrie = NULL;

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_DICTIONARY_SIZE (1000)
#define MAX_SENTENCE_SIZE (int)(1e6)
    struct testCaseType {
        char *dictionary[MAX_DICTIONARY_SIZE];
        int dictionarySize;
        char sentence[MAX_SENTENCE_SIZE];
    } testCase[] = {{{"cat", "bat", "rat"}, 3, "the cattle was rattled by the battery"},
                    {{"a", "b", "c"}, 3, "aadsfasf absbs bbab cadsfafs"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
     *  Output: "the cat was rat by the bat"
     *
     *  Input: dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
     *  Output: "a a b c"
     */

    char *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: dictionary = [");
        for (j = 0; j < testCase[i].dictionarySize; ++j) {
            printf("%s\"%s\"", (j == 0 ? "" : ","), testCase[i].dictionary[j]);
        }
        printf("], sentence = \"%s\"\n", testCase[i].sentence);

        pAnswer = replaceWords(testCase[i].dictionary, testCase[i].dictionarySize, testCase[i].sentence);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
