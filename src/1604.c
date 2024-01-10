#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_NAME_LENGTH (10 + 2)  // 1 <= keyName[i].length <= 10
struct hash_struct {
    char name[MAX_NAME_LENGTH];
    struct ListNode* timeList;  // use list instead of array to avoid Time Limit Exceeded
    UT_hash_handle hh;
};
void freeTimeList(struct ListNode* pFree) {
    struct ListNode* pCurrent = NULL;
    while (pFree != NULL) {
        pCurrent = pFree;
        pFree = pFree->next;
        free(pCurrent);
        pCurrent = NULL;
    }
}
void freeAll(struct hash_struct* pFree) {
    struct hash_struct* current;
    struct hash_struct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        freeTimeList(current->timeList);
        free(current);
    }
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int compareString(const void* str1, const void* str2) {
    char* const* p1 = str1;
    char* const* p2 = str2;

    // ascending order
    return strcmp(*p1, *p2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** alertNames(char** keyName, int keyNameSize, char** keyTime, int keyTimeSize, int* returnSize) {
    char** pRetVal = NULL;

    //
    (*returnSize) = 0;

    // hashTable(name, time)
    struct hash_struct* hashTable = NULL;
    struct hash_struct* pTmp;
    struct ListNode* pNode;
    int i;
    for (i = 0; i < keyNameSize; ++i) {
        pTmp = NULL;
        HASH_FIND_STR(hashTable, keyName[i], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hash_struct*)malloc(sizeof(struct hash_struct));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(hashTable);
                hashTable = NULL;
                return pRetVal;
            }
            snprintf(pTmp->name, MAX_NAME_LENGTH, "%s", keyName[i]);
            pTmp->timeList = NULL;
            HASH_ADD_STR(hashTable, name, pTmp);
        }
        pNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pNode == NULL) {
            perror("malloc");
            freeAll(hashTable);
            hashTable = NULL;
            return pRetVal;
        }
        pNode->val = 60 * ((keyTime[i][0] - '0') * 10 + (keyTime[i][1] - '0')) +
                     ((keyTime[i][3] - '0') * 10 + (keyTime[i][4] - '0'));
        pNode->next = pTmp->timeList;
        pTmp->timeList = pNode;
    }

    // malloc return value
    pRetVal = (char**)malloc(keyNameSize * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        freeAll(hashTable);
        hashTable = NULL;
        return pRetVal;
    }

    //
    int timeSize = 0;
    int timeArray[keyNameSize];
    struct ListNode* pNext;
    struct hash_struct* pCurrent;
    pTmp = NULL;
    HASH_ITER(hh, hashTable, pCurrent, pTmp) {
        timeSize = 0;
        memset(timeArray, 0, sizeof(timeArray));
        for (pNext = pCurrent->timeList; pNext; pNext = pNext->next) {
            timeArray[timeSize++] = pNext->val;
        }
        qsort(timeArray, timeSize, sizeof(int), compareInteger);

        for (i = 2; i < timeSize; ++i) {
            if (timeArray[i] - timeArray[i - 2] <= 60) {
                pRetVal[(*returnSize)] = (char*)malloc(MAX_NAME_LENGTH * sizeof(char));
                if (pRetVal[(*returnSize)] == NULL) {
                    perror("malloc");
                    freeAll(hashTable);
                    hashTable = NULL;
                    for (i = 0; i < (*returnSize); ++i) {
                        free(pRetVal[i]);
                        pRetVal[i] = NULL;
                    }
                    free(pRetVal);
                    pRetVal = NULL;
                    (*returnSize) = 0;
                    return pRetVal;
                }
                memset(pRetVal[(*returnSize)], 0, (MAX_NAME_LENGTH * sizeof(char)));
                snprintf(pRetVal[(*returnSize)], (MAX_NAME_LENGTH * sizeof(char)), "%s", pCurrent->name);
                (*returnSize)++;
                break;
            }
        }
    }
    qsort(pRetVal, (*returnSize), sizeof(char*), compareString);

    //
    freeAll(hashTable);
    hashTable = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
#define MAX_LENGTH (10)
    struct testCaseType {
        char keyName[MAX_SIZE][MAX_LENGTH];
        int keyNameSize;
        char keyTime[MAX_SIZE][MAX_LENGTH];
        int keyTimeSize;
        int returnSize;
    } testCase[] = {{{"daniel", "daniel", "daniel", "luis", "luis", "luis", "luis"},
                     7,
                     {"10:00", "10:40", "11:00", "09:00", "11:00", "13:00", "15:00"},
                     7,
                     0},
                    {{"alice", "alice", "alice", "bob", "bob", "bob", "bob"},
                     7,
                     {"12:01", "12:00", "18:00", "21:00", "21:20", "21:30", "23:00"},
                     7,
                     0},
                    {{"john", "john", "john"}, 3, {"23:58", "23:59", "00:01"}, 3, 0},
                    {{"leslie", "leslie", "leslie", "clare", "clare", "clare", "clare"},
                     7,
                     {"13:00", "13:20", "14:00", "18:00", "18:51", "19:30", "19:49"},
                     7,
                     0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char** pKeyName = NULL;
    char** pkeyTime = NULL;
    char** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: keyName =  [");
        for (j = 0; j < testCase[i].keyNameSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].keyName[j]);
        }
        printf("], keyTime =  [");
        for (j = 0; j < testCase[i].keyTimeSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].keyTime[j]);
        }
        printf("]\n");

        pKeyName = (char**)malloc(testCase[i].keyNameSize * sizeof(char*));
        if (pKeyName == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].keyNameSize; ++j) {
            pKeyName[j] = (char*)malloc((strlen(testCase[i].keyName[j]) + 1) * sizeof(char));
            if (pKeyName[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pKeyName[k]) {
                        free(pKeyName[k]);
                        pKeyName[k] = NULL;
                    }
                }
                free(pKeyName);
                pKeyName = NULL;
                return EXIT_FAILURE;
            }
            memset(pKeyName[j], 0, (strlen(testCase[i].keyName[j]) + 1) * sizeof(char));
            memcpy(pKeyName[j], testCase[i].keyName[j], (strlen(testCase[i].keyName[j]) + 1) * sizeof(char));
        }
        pkeyTime = (char**)malloc(testCase[i].keyTimeSize * sizeof(char*));
        if (pKeyName == NULL) {
            perror("malloc");
            for (j = 0; j < testCase[i].keyNameSize; ++j) {
                if (pKeyName[j]) {
                    free(pKeyName[j]);
                    pKeyName[j] = NULL;
                }
            }
            free(pKeyName);
            pKeyName = NULL;
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].keyTimeSize; ++j) {
            pkeyTime[j] = (char*)malloc((strlen(testCase[i].keyTime[j]) + 1) * sizeof(char));
            if (pkeyTime[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pkeyTime[k]) {
                        free(pkeyTime[k]);
                        pkeyTime[k] = NULL;
                    }
                }
                free(pkeyTime);
                pkeyTime = NULL;
                for (j = 0; j < testCase[i].keyNameSize; ++j) {
                    if (pKeyName[j]) {
                        free(pKeyName[j]);
                        pKeyName[j] = NULL;
                    }
                }
                free(pKeyName);
                pKeyName = NULL;
                return EXIT_FAILURE;
            }
            memset(pkeyTime[j], 0, (strlen(testCase[i].keyTime[j]) + 1) * sizeof(char));
            memcpy(pkeyTime[j], testCase[i].keyTime[j], (strlen(testCase[i].keyTime[j]) + 1) * sizeof(char));
        }
        pAnswer =
            alertNames(pKeyName, testCase[i].keyNameSize, pkeyTime, testCase[i].keyTimeSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].keyNameSize; ++j) {
            free(pKeyName[j]);
            pKeyName[j] = NULL;
        }
        free(pKeyName);
        pKeyName = NULL;
        for (j = 0; j < testCase[i].keyTimeSize; ++j) {
            free(pkeyTime[j]);
            pkeyTime[j] = NULL;
        }
        free(pkeyTime);
        pkeyTime = NULL;
    }

    return EXIT_SUCCESS;
}
