#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

typedef struct {
    char key[16];
    UT_hash_handle hh;
} HashItem;
bool hashInsert(HashItem** obj, const char* str) {
    bool retVal = false;

    HashItem* pEntry = (HashItem*)malloc(sizeof(HashItem));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    strcpy(pEntry->key, str);
    HASH_ADD_STR(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
bool hashFind(HashItem** obj, const char* str) {
    bool retVal = false;

    HashItem* pEntry = NULL;
    HASH_FIND_STR(*obj, str, pEntry);
    if (pEntry == NULL) {
        return retVal;
    }
    retVal = true;

    return retVal;
}
void hashFree(HashItem** obj) {
    HashItem* curr;
    HashItem* tmp;

    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}
int minMutation(char* start, char* end, char** bank, int bankSize) {
    int retVal = -1;

    int i, j, k;

    if (strcmp(start, end) == 0) {
        retVal = 0;
        return retVal;
    }

    HashItem* cnt = NULL;
    for (i = 0; i < bankSize; ++i) {
        hashInsert(&cnt, bank[i]);
    }
    if (hashFind(&cnt, end) == false) {
        hashFree(&cnt);
        cnt = NULL;
        return retVal;
    }

    char** queue = (char**)malloc(bankSize * sizeof(char*));
    if (queue == NULL) {
        perror("malloc");
        hashFree(&cnt);
        cnt = NULL;
        return retVal;
    }

    int head = 0;
    int tail = 0;
    queue[tail] = (char*)malloc(16 * sizeof(char));
    if (queue[tail] == NULL) {
        perror("malloc");
        hashFree(&cnt);
        cnt = NULL;
        free(queue);
        queue = NULL;
        return retVal;
    }
    strcpy(queue[tail], start);
    tail++;

    HashItem* visited = NULL;
    hashInsert(&visited, start);

    char keys[4] = {'A', 'C', 'G', 'T'};
    int step = 1;
    int sz;
    char* curr;
    char* next;
    while (head != tail) {
        sz = tail - head;

        for (i = 0; i < sz; ++i) {
            curr = queue[head++];

            for (j = 0; j < 8; ++j) {
                for (k = 0; k < 4; ++k) {
                    if (keys[k] == curr[j]) {
                        continue;
                    }

                    next = (char*)malloc(16 * sizeof(char));
                    if (next == NULL) {
                        perror("malloc");
                        goto exit;
                    }
                    strcpy(next, curr);

                    next[j] = keys[k];
                    if ((hashFind(&visited, next) == false) && (hashFind(&cnt, next) == true)) {
                        if (strcmp(next, end) == 0) {
                            free(next);
                            next = NULL;
                            retVal = step;
                            goto exit;
                        }
                        queue[tail++] = next;
                        hashInsert(&visited, next);
                    } else {
                        free(next);
                        next = NULL;
                    }
                }
            }
            free(curr);
            curr = NULL;
        }
        step++;
    }

exit:
    hashFree(&cnt);
    cnt = NULL;
    hashFree(&visited);
    visited = NULL;
    //
    free(curr);
    curr = NULL;
    //
    while (head != tail) {
        free(queue[head]);
        queue[head] = NULL;
        head++;
    }
    free(queue);
    queue = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10)
#define MAX_LENGTH (8 + 4)
    struct testCaseType {
        char start[MAX_LENGTH];
        char end[MAX_LENGTH];
        char* bank[MAX_SIZE];
        int bankSize;
    } testCase[] = {{"AACCGGTT", "AACCGGTA", {"AACCGGTA"}, 1},
                    {"AACCGGTT", "AAACGGTA", {"AACCGGTA", "AACCGCTA", "AAACGGTA"}, 3},
                    {"AAAAACCC", "AACCCCCC", {"AAAACCCC", "AAACCCCC", "AACCCCCC"}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
     *  Output: 1
     *
     *  Input: start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
     *  Output: 2
     *
     *  Input: start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
     *  Output: 3
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: start = %s, end = %s, bank = [", testCase[i].start, testCase->end);
        for (j = 0; j < testCase[i].bankSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", testCase[i].bank[j]);
        }
        printf("]\n");

        answer = minMutation(testCase[i].start, testCase[i].end, testCase[i].bank, testCase[i].bankSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
