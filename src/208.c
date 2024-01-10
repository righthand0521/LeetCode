#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR (26)  // word and prefix consist only of lowercase English letters.
typedef struct Trie {
    struct Trie* children[MAX_CHAR];
    bool isEnd;
} Trie;
Trie* trieCreate() {
    Trie* pRetVal = (Trie*)malloc(sizeof(Trie));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal->children, 0, sizeof(pRetVal->children));
    pRetVal->isEnd = false;

    return pRetVal;
}
void trieInsert(Trie* obj, char* word) {
    int len = strlen(word);

    int ch;
    int i;
    for (i = 0; i < len; ++i) {
        ch = word[i] - 'a';
        if (obj->children[ch] == NULL) {
            obj->children[ch] = trieCreate();
            if (obj->children[ch] == NULL) {
                return;
            }
        }
        obj = obj->children[ch];
    }
    obj->isEnd = true;
}
bool trieSearch(Trie* obj, char* word) {
    bool retVal = false;

    int len = strlen(word);

    int ch;
    int i;
    for (i = 0; i < len; ++i) {
        ch = word[i] - 'a';
        if (obj->children[ch] == NULL) {
            return retVal;
        }
        obj = obj->children[ch];
    }
    retVal = obj->isEnd;

    return retVal;
}
bool trieStartsWith(Trie* obj, char* prefix) {
    bool retVal = false;

    int len = strlen(prefix);

    int ch;
    int i;
    for (i = 0; i < len; ++i) {
        ch = prefix[i] - 'a';
        if (obj->children[ch] == NULL) {
            return retVal;
        }
        obj = obj->children[ch];
    }
    retVal = true;

    return retVal;
}
void trieFree(Trie* obj) {
    int i;
    for (i = 0; i < MAX_CHAR; ++i) {
        if (obj->children[i]) {
            trieFree(obj->children[i]);
        }
    }
    free(obj);
}
/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 * bool param_2 = trieSearch(obj, word);
 * bool param_3 = trieStartsWith(obj, prefix);
 * trieFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (30000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        char* val[MAX_SIZE];
        int calls;
    } testCase[] = {{{"Trie", "insert", "search", "search", "startsWith", "insert", "search"},
                     {"", "apple", "apple", "app", "app", "app", "app"},
                     7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
     *  [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
     *  Output
     *  [null, null, true, false, true, null, true]
     */

    Trie* obj = NULL;
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
            printf("%s[\"%s\"]", (j == 0) ? "" : ", ", testCase[i].val[j]);
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "Trie") == 0) {
                obj = trieCreate();
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "insert") == 0) {
                trieInsert(obj, testCase[i].val[j]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "search") == 0) {
                retBool = trieSearch(obj, testCase[i].val[j]);
                printf("%s%s", (j == 0) ? "" : ", ", (retBool == true ? "true" : "false"));
            } else if (strcmp(testCase[i].methods[j], "startsWith") == 0) {
                retBool = trieStartsWith(obj, testCase[i].val[j]);
                printf("%s%s", (j == 0) ? "" : ", ", (retBool == true ? "true" : "false"));
            }
        }
        printf("]\n");

        trieFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
