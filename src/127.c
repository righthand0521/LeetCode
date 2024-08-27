#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS (26 + 2)  // beginWord, endWord, and wordList[i] consist of lowercase English letters.
#define MAX_WORDLISTSIZE (60000 + 4)
#define MAX_EDGE (50000 + 4)
struct Trie {
    int ch[MAX_LETTERS];
    int val;
};
void insert(char* s, int* num, struct Trie* pObj, int* pObjIdx) {
    int sSize = strlen(s);

    int add = 0;
    int x;
    int i;
    for (i = 0; i < sSize; ++i) {
        x = s[i] - '`';
        if (pObj[add].ch[x] == 0) {
            (*pObjIdx) += 1;
            pObj[add].ch[x] = (*pObjIdx);
            memset(pObj[(*pObjIdx)].ch, 0, MAX_LETTERS * sizeof(int));
            pObj[(*pObjIdx)].val = -1;
        }
        add = pObj[add].ch[x];
    }
    pObj[add].val = (*num);
}
int find(char* s, struct Trie* pObj, int* pObjIdx) {
    int retVal = -1;

    int add = 0;
    int sSize = strlen(s);
    int x;
    int i;
    for (i = 0; i < sSize; ++i) {
        x = s[i] - '`';
        if (pObj[add].ch[x] == 0) {
            return retVal;
        }
        add = pObj[add].ch[x];
    }
    retVal = pObj[add].val;

    return retVal;
}
int addWord(char* word, struct Trie* pObj, int* pObjIdx, int* nodeNum) {
    int retVal = 0;

    if (find(word, pObj, pObjIdx) == -1) {
        insert(word, nodeNum, pObj, pObjIdx);
        (*nodeNum) += 1;
    }
    retVal = find(word, pObj, pObjIdx);

    return retVal;
}
void addEdge(char* word, struct Trie* pObj, int* pObjIdx, int* nodeNum, int** pEdge, int* pEdgeSize) {
    int id1 = addWord(word, pObj, pObjIdx, nodeNum);
    int id2;
    char tmp;
    int wordSize = strlen(word);
    int i;
    for (i = 0; i < wordSize; ++i) {
        tmp = word[i];
        word[i] = '`';

        id2 = addWord(word, pObj, pObjIdx, nodeNum);
        pEdge[id1][pEdgeSize[id1]++] = id2;
        pEdge[id2][pEdgeSize[id2]++] = id1;

        word[i] = tmp;
    }
}
int ladderLength(char* beginWord, char* endWord, char** wordList, int wordListSize) {
    int retVal = 0;

    int i, j;

    int trieIdx = 0;
    struct Trie* pTrie = NULL;
    pTrie = (struct Trie*)malloc(MAX_WORDLISTSIZE * sizeof(struct Trie));
    if (pTrie == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pTrie[trieIdx].ch, 0, sizeof(pTrie[trieIdx].ch));
    pTrie[trieIdx].val = -1;

    int* pEdgeSize = NULL;
    pEdgeSize = (int*)malloc(MAX_EDGE * sizeof(int));
    if (pEdgeSize == NULL) {
        perror("malloc");
        free(pTrie);
        pTrie = NULL;
        return retVal;
    }
    memset(pEdgeSize, 0, (MAX_EDGE * sizeof(int)));

    int** pEdge = NULL;
    pEdge = (int**)malloc(MAX_EDGE * sizeof(int*));
    if (pEdge == NULL) {
        perror("malloc");
        free(pEdgeSize);
        pEdgeSize = NULL;
        free(pTrie);
        pTrie = NULL;
        return retVal;
    }
    for (i = 0; i < MAX_EDGE; ++i) {
        pEdge[i] = (int*)malloc(MAX_LETTERS * sizeof(int));
        if (pEdge[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pEdge[j]);
                pEdge[j] = NULL;
            }
            free(pEdge);
            pEdge = NULL;
            free(pEdgeSize);
            pEdgeSize = NULL;
            free(pTrie);
            pTrie = NULL;
            return retVal;
        }
        memset(pEdge[i], 0, (MAX_LETTERS * sizeof(int)));
    }

    int nodeNum = 0;
    for (i = 0; i < wordListSize; ++i) {
        addEdge(wordList[i], pTrie, &trieIdx, &nodeNum, pEdge, pEdgeSize);
    }
    addEdge(beginWord, pTrie, &trieIdx, &nodeNum, pEdge, pEdgeSize);

    int endId = find(endWord, pTrie, &trieIdx);
    if (endId == -1) {
        for (i = 0; i < MAX_EDGE; ++i) {
            free(pEdge[i]);
            pEdge[i] = NULL;
        }
        free(pEdge);
        pEdge = NULL;
        free(pEdgeSize);
        pEdgeSize = NULL;
        free(pTrie);
        pTrie = NULL;
        return retVal;
    }

    int distance[nodeNum];
    memset(distance, -1, sizeof(distance));
    int beginId = find(beginWord, pTrie, &trieIdx);
    distance[beginId] = 0;

    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    int bfsQueue[nodeNum];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    bfsQueue[bfsQueueTail++] = beginId;
    int x;
    while (bfsQueueHead < bfsQueueTail) {
        x = bfsQueue[bfsQueueHead++];
        for (i = 0; i < pEdgeSize[x]; ++i) {
            if (distance[pEdge[x][i]] != -1) {
                continue;
            }
            distance[pEdge[x][i]] = distance[x] + 1;

            if (pEdge[x][i] == endId) {
                retVal = distance[pEdge[x][i]] / 2 + 1;
                for (i = 0; i < MAX_EDGE; ++i) {
                    free(pEdge[i]);
                    pEdge[i] = NULL;
                }
                free(pEdge);
                pEdge = NULL;
                free(pEdgeSize);
                pEdgeSize = NULL;
                free(pTrie);
                pTrie = NULL;
                return retVal;
            }

            bfsQueue[bfsQueueTail++] = pEdge[x][i];
        }
    }

    //
    for (i = 0; i < MAX_EDGE; ++i) {
        free(pEdge[i]);
        pEdge[i] = NULL;
    }
    free(pEdge);
    pEdge = NULL;
    free(pEdgeSize);
    pEdgeSize = NULL;
    free(pTrie);
    pTrie = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
#define MAX_LENGTH (10 + 2)
    struct testCaseType {
        char beginWord[MAX_LENGTH];
        char endWord[MAX_LENGTH];
        char wordList[MAX_SIZE][MAX_LENGTH];
        int wordListSize;
    } testCase[] = {{"hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}, 6},
                    {"hit", "cog", {"hot", "dot", "dog", "lot", "log"}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
     *  Output: 5
     *
     *  Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
     *  Output: 0
     */

    char** pWordList = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: beginWord = \"%s\", endWord = \"%s\", wordList = [", testCase[i].beginWord, testCase[i].endWord);
        for (j = 0; j < testCase[i].wordListSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].wordList[j]);
        }
        printf("]\n");

        pWordList = (char**)malloc(testCase[i].wordListSize * sizeof(char*));
        if (pWordList == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].wordListSize; ++j) {
            pWordList[j] = (char*)malloc(MAX_LENGTH * sizeof(char));
            if (pWordList[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++j) {
                    free(pWordList[j]);
                    pWordList[j] = NULL;
                }
                free(pWordList);
                pWordList = NULL;
                return EXIT_FAILURE;
            }
            memset(pWordList[j], 0, MAX_LENGTH * sizeof(char));
            memcpy(pWordList[j], testCase[i].wordList[j], strlen(testCase[i].wordList[j]));
        }
        answer = ladderLength(testCase[i].beginWord, testCase[i].endWord, pWordList, testCase[i].wordListSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].wordListSize; ++j) {
            free(pWordList[j]);
            pWordList[j] = NULL;
        }
        free(pWordList);
        pWordList = NULL;
    }

    return EXIT_SUCCESS;
}
