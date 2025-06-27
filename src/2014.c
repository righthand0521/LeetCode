#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    char* str;
    int len;
} QueueNode;
typedef struct {
    QueueNode* data;
    int front, rear, size, capacity;
} Queue;
Queue* createQueue(int capacity) {
    Queue* obj = NULL;

    obj = (Queue*)malloc(sizeof(Queue));
    obj->data = (QueueNode*)malloc(capacity * sizeof(QueueNode));
    obj->front = obj->size = 0;
    obj->rear = capacity - 1;
    obj->capacity = capacity;

    return obj;
}
void enqueue(Queue* q, char* str, int len) {
    if (q->size == q->capacity) {
        //
        return;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear].str = strdup(str);
    q->data[q->rear].len = len;
    q->size++;
}
QueueNode dequeue(Queue* q) {
    QueueNode obj;

    if (q->size == 0) {
        obj.str = NULL;
        obj.len = 0;
        return obj;
    }

    obj = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;

    return obj;
}

#endif  // QUEUE_H
bool isKRepeatedSubsequence(const char* s, const char* t, int k) {
    bool retVal = false;

    int tSize = strlen(t);
    int pos = 0;
    int matched = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] != t[pos]) {
            continue;
        }

        pos++;
        if (pos != tSize) {
            continue;
        }

        pos = 0;
        matched++;
        if (matched == k) {
            retVal = true;
            break;
        }
    }

    return retVal;
}
char* longestSubsequenceRepeatedK(char* s, int k) {
    char* pRetVal = NULL;  // strdup("");

    int returnSize = strlen(s) + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    int letterSize = 26;  // s consists of lowercase English letters.
    int frequency[letterSize];
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; s[i]; i++) {
        frequency[s[i] - 'a']++;
    }

    char candidate[letterSize];
    int candidateSize = 0;
    for (int i = (letterSize - 1); i >= 0; i--) {
        if (frequency[i] >= k) {
            candidate[candidateSize++] = 'a' + i;
        }
    }

    int candidateQueueSize = 10000;
    Queue* candidateQueue = createQueue(candidateQueueSize);
    for (int i = 0; i < candidateSize; i++) {
        char str[2] = {candidate[i], '\0'};
        enqueue(candidateQueue, str, 1);
    }

    while (candidateQueue->size > 0) {
        QueueNode curr = dequeue(candidateQueue);
        if (curr.len > strlen(pRetVal)) {
            memset(pRetVal, 0, (returnSize * sizeof(char)));
            snprintf(pRetVal, returnSize - 1, "%s", curr.str);
        }

        // generate the next candidate string
        for (int i = 0; i < candidateSize; i++) {
            char next[curr.len + 2];
            memset(next, 0, sizeof(next));
            strcpy(next, curr.str);
            next[curr.len] = candidate[i];
            next[curr.len + 1] = '\0';
            if (isKRepeatedSubsequence(s, next, k) == true) {
                enqueue(candidateQueue, next, curr.len + 1);
            }
        }

        free(curr.str);
    }

    //
    free(candidateQueue->data);
    free(candidateQueue);

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
        int k;
    } testCase[] = {{"letsleetcode", 2}, {"bb", 2}, {"ab", 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "letsleetcode", k = 2
     *  Output: "let"
     *
     *  Input: s = "bb", k = 2
     *  Output: "b"
     *
     *  Input: s = "ab", k = 2
     *  Output: ""
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        pAnswer = longestSubsequenceRepeatedK(testCase[i].s, testCase[i].k);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
