#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/design-add-and-search-words-data-structure/solutions/1440451/c-by-codee-3-nka1/
#define MAX_CHAR (26)  // word in addWord consists of lowercase English letters.
typedef struct WordDictionary {
    struct WordDictionary* child[MAX_CHAR];
    bool isEnd;
} WordDictionary;
WordDictionary* wordDictionaryCreate() {
    WordDictionary* pRetVal = (WordDictionary*)malloc(sizeof(WordDictionary));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal->child, 0, MAX_CHAR * sizeof(WordDictionary*));
    pRetVal->isEnd = false;

    return pRetVal;
}
void wordDictionaryAddWord(WordDictionary* obj, char* word) {
    int len = strlen(word);

    int ch;
    int i;
    for (i = 0; i < len; ++i) {
        ch = word[i] - 'a';
        if (obj->child[ch] != NULL) {
            obj = obj->child[ch];
            continue;
        }
        obj->child[ch] = (WordDictionary*)malloc(sizeof(WordDictionary));
        obj = obj->child[ch];
        memset(obj->child, 0, sizeof(obj->child));
        obj->isEnd = false;
    }

    obj->isEnd = true;
}
bool wordDictionarySearch(WordDictionary* obj, char* word) {
    bool retVal = false;

    if (obj == NULL) {
        return retVal;
    }

    int len = strlen(word);
    if (len == 0) {
        retVal = obj->isEnd;
        return retVal;
    }

    if (word[0] != '.') {
        retVal = wordDictionarySearch(obj->child[word[0] - 'a'], word + 1);
        return retVal;
    }

    int i;
    for (i = 0; i < MAX_CHAR; i++) {
        if (wordDictionarySearch(obj->child[i], word + 1)) {
            retVal = true;
            break;
        }
    }

    return retVal;
}
void wordDictionaryFree(WordDictionary* obj) {
    int i;
    for (i = 0; i < MAX_CHAR; i++) {
        if (obj->child[i]) {
            wordDictionaryFree(obj->child[i]);
        }
    }
    free(obj);
}
/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);
 * bool param_2 = wordDictionarySearch(obj, word);
 * wordDictionaryFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (25 + 3)
    struct testCaseType {
        char* methods[MAX_SIZE];
        char* value[MAX_SIZE];
        int calls;
    } testCase[] = {{{"WordDictionary", "addWord", "addWord", "addWord", "search", "search", "search", "search"},
                     {"", "bad", "dad", "mad", "pad", "bad", ".ad", "b.."},
                     8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example:
     *  Input
     *  ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
     *  [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
     *  Output
     *  [null,null,null,null,false,true,true,true]
     */

    WordDictionary* obj = NULL;
    bool retBool;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[\"%s\"]", (j == 0) ? "" : ", ", testCase[i].value[j]);
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "WordDictionary") == 0) {
                obj = wordDictionaryCreate();
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "addWord") == 0) {
                wordDictionaryAddWord(obj, testCase[i].value[j]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "search") == 0) {
                retBool = wordDictionarySearch(obj, testCase[i].value[j]);
                printf("%s%s", (j == 0) ? "" : ", ", (retBool == true ? "true" : "false"));
            }
        }
        printf("]\n");

        wordDictionaryFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
