#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char type[8];
    int timestamp;
    char target[512];
} Event;
int compareEvents(const void* a, const void* b) {
    int retVal = 0;

    Event* e1 = (Event*)a;
    Event* e2 = (Event*)b;
    if (e1->timestamp != e2->timestamp) {
        retVal = e1->timestamp - e2->timestamp;
    } else {
        retVal = (strcmp(e1->type, "OFFLINE") == 0) ? (-1) : (1);
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countMentions(int numberOfUsers, char*** events, int eventsSize, int* eventsColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    Event* eventArr = (Event*)calloc(eventsSize, sizeof(Event));
    if (eventArr == NULL) {
        perror("calloc");
        return pRetVal;
    }
    for (int i = 0; i < eventsSize; i++) {
        strcpy(eventArr[i].type, events[i][0]);
        eventArr[i].timestamp = atoi(events[i][1]);
        strcpy(eventArr[i].target, events[i][2]);
    }
    qsort(eventArr, eventsSize, sizeof(Event), compareEvents);

    pRetVal = (int*)calloc(numberOfUsers, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        free(eventArr);
        return pRetVal;
    }

    int nextOnlineTime[numberOfUsers];
    memset(nextOnlineTime, 0, sizeof(nextOnlineTime));
    int curTime, idx;
    char *type, *target, *token;
    for (int i = 0; i < eventsSize; i++) {
        curTime = eventArr[i].timestamp;
        type = eventArr[i].type;
        target = eventArr[i].target;

        if (strcmp(type, "MESSAGE") == 0) {
            if (strcmp(target, "ALL") == 0) {
                for (int j = 0; j < numberOfUsers; j++) {
                    pRetVal[j]++;
                }
            } else if (strcmp(target, "HERE") == 0) {
                for (int j = 0; j < numberOfUsers; j++) {
                    if (nextOnlineTime[j] <= curTime) {
                        pRetVal[j]++;
                    }
                }
            } else {
                token = strtok(target, " ");
                while (token != NULL) {
                    idx = atoi(token + 2);
                    pRetVal[idx]++;
                    token = strtok(NULL, " ");
                }
            }
        } else {
            idx = atoi(target);
            nextOnlineTime[idx] = curTime + 60;
        }
    }
    (*returnSize) = numberOfUsers;

    //
    free(eventArr);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int numberOfUsers;
        char* events[MAX_SIZE][3];
        int eventsSize;
        int eventsColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {
        {2, {{"MESSAGE", "10", "id1 id0"}, {"OFFLINE", "11", "0"}, {"MESSAGE", "71", "HERE"}}, 3, {3, 3, 3}, 0},
        {2, {{"MESSAGE", "10", "id1 id0"}, {"OFFLINE", "11", "0"}, {"MESSAGE", "12", "ALL"}}, 3, {3, 3, 3}, 0},
        {2, {{"OFFLINE", "10", "0"}, {"MESSAGE", "12", "HERE"}}, 2, {3, 3}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]]
     *  Output: [2,2]
     *
     *  Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","12","ALL"]]
     *  Output: [2,2]
     *
     *  Input: numberOfUsers = 2, events = [["OFFLINE","10","0"],["MESSAGE","12","HERE"]]
     *  Output: [0,1]
     */

    char*** pEvents = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: numberOfUsers = %d, events = [", testCase[i].numberOfUsers);
        for (j = 0; j < testCase[i].eventsSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].eventsColSize[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", testCase[i].events[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pEvents = (char***)malloc(testCase[i].eventsSize * sizeof(char**));
        if (pEvents == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].eventsSize; ++j) {
            pEvents[j] = (char**)malloc(testCase[i].eventsColSize[j] * sizeof(char*));
            if (pEvents[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pEvents[k]) {
                        free(pEvents[k]);
                        pEvents[k] = NULL;
                    }
                }
                free(pEvents);
                pEvents = NULL;
                return EXIT_FAILURE;
            }
            memset(pEvents[j], 0, testCase[i].eventsColSize[j] * sizeof(char*));
            memcpy(pEvents[j], testCase[i].events[j], testCase[i].eventsColSize[j] * sizeof(char*));
        }
        pAnswer = countMentions(testCase[i].numberOfUsers, pEvents, testCase[i].eventsSize, testCase[i].eventsColSize,
                                &testCase[i].returnSize);
        printf("Output:[");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].eventsSize; ++j) {
            if (pEvents[j]) {
                free(pEvents[j]);
                pEvents[j] = NULL;
            }
        }
        free(pEvents);
        pEvents = NULL;
    }

    return EXIT_SUCCESS;
}
