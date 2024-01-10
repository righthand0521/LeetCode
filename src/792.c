#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node {
    int idx;
    int size;
    struct Node *next;
} Node;
typedef struct {
    struct Node *head;
    struct Node *tail;
    int size;
} myQueue;
myQueue *myQueueCreate() {
    myQueue *pRetVal = NULL;

    pRetVal = (myQueue *)malloc(sizeof(myQueue));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->size = 0;
    pRetVal->head = NULL;
    pRetVal->tail = NULL;

    return pRetVal;
}
bool myQueueEnQueue(myQueue *pObj, int idx, int size) {
    bool retVal = false;

    struct Node *pNew = (struct Node *)malloc(sizeof(struct Node));
    if (pNew == NULL) {
        perror("malloc");
        return retVal;
    }
    retVal = true;

    pNew->idx = idx;
    pNew->size = size;
    pNew->next = NULL;
    if (pObj->head == NULL) {
        pObj->head = pNew;
        pObj->tail = pNew;
    } else {
        pObj->tail->next = pNew;
        pObj->tail = pNew;
    }
    pObj->size++;

    return retVal;
}
bool myQueueDeQueue(myQueue *pObj) {
    bool retVal = false;

    if (pObj->size == 0) {
        return retVal;
    }
    retVal = true;

    struct Node *pFree = pObj->head;
    pObj->head = pObj->head->next;
    pObj->size--;
    free(pFree);
    pFree = NULL;

    return retVal;
}
Node *myQueueFront(myQueue *pObj) {
    struct Node *pRetVal = NULL;

    if (pObj->size == 0) {
        return pRetVal;
    }
    pRetVal = pObj->head;

    return pRetVal;
}
bool myQueueIsEmpty(myQueue *pObj) {
    bool retVal = false;

    if (pObj->size == 0) {
        retVal = true;
    }

    return retVal;
}
void myQueueQueueFree(myQueue *pObj) {
    struct Node *pFree = NULL;
    struct Node *pCurrent = pObj->head;
    while (pCurrent != NULL) {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        free(pFree);
        pFree = NULL;
    }
    free(pObj);
    pObj = NULL;
}
#endif  // QUEUE_H
int numMatchingSubseq(char *s, char **words, int wordsSize) {
    int retVal = 0;

    int i;

#define MAX_RECORD_SIZE (26)  // s and words[i] consist of only lowercase English letters.
    myQueue *record[MAX_RECORD_SIZE];
    for (i = 0; i < MAX_RECORD_SIZE; ++i) {
        record[i] = myQueueCreate();
        if (record[i] == NULL) {
            goto _exit;
        }
    }
    for (i = 0; i < wordsSize; ++i) {
        myQueueEnQueue(record[words[i][0] - 'a'], i, 0);
    }

    int recordSize;
    Node *pEntry;
    int size, idx;
    int wordLength;
    int sSize = strlen(s);
    for (i = 0; i < sSize; ++i) {
        recordSize = record[s[i] - 'a']->size;
        while (recordSize) {
            recordSize--;

            pEntry = myQueueFront(record[s[i] - 'a']);
            idx = pEntry->idx;
            size = pEntry->size;

            myQueueDeQueue(record[s[i] - 'a']);
            wordLength = strlen(words[idx]);
            if (size == wordLength - 1) {
                ++retVal;
            } else {
                ++size;
                myQueueEnQueue(record[words[idx][size] - 'a'], idx, size);
            }
        }
    }

_exit:
    for (i = 0; i < MAX_RECORD_SIZE; i++) {
        myQueueQueueFree(record[i]);
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_S_SIZE (50000)
#define MAX_WORDS_COUNT (5000)
#define MAX_WORDS_SIZE (50)
    struct testCaseType {
        char s[MAX_S_SIZE];
        char *words[MAX_WORDS_COUNT];
        int wordsSize;
    } testCase[] = {{"abcde", {"a", "bb", "acd", "ace"}, 4},
                    {"dsahjpjauf", {"ahjpjau", "ja", "ahbwzgqnuk", "tnmlanowax"}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abcde", words = ["a","bb","acd","ace"]
     *  Output: 3
     *
     *  Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", words = [", testCase[i].s);
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        answer = numMatchingSubseq(testCase[i].s, testCase[i].words, testCase[i].wordsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
