#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef HASH_H
#define HASH_H

typedef struct {
    char* key;
    int val;
    UT_hash_handle hh;
} HashItem;
HashItem* hashFindItem(HashItem** obj, const char* key) {
    HashItem* pEntry = NULL;
    HASH_FIND_STR(*obj, key, pEntry);
    return pEntry;
}
bool hashAddItem(HashItem** obj, char* key, int val) {
    if (hashFindItem(obj, key)) {
        return false;
    }
    HashItem* pEntry = (HashItem*)malloc(sizeof(HashItem));
    pEntry->key = strdup(key);
    pEntry->val = val;
    HASH_ADD_STR(*obj, key, pEntry);
    return true;
}
bool hashSetItem(HashItem** obj, char* key, int val) {
    HashItem* pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        hashAddItem(obj, key, val);
    } else {
        pEntry->val = val;
    }
    return true;
}
int hashGetItem(HashItem** obj, const char* key, int defaultVal) {
    HashItem* pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        return defaultVal;
    }
    return pEntry->val;
}
bool hashErase(HashItem** obj, char* key) {
    HashItem* pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        return false;
    }
    HASH_DEL(*obj, pEntry);
    free(pEntry->key);
    free(pEntry);
    return true;
}
void hashFree(HashItem** obj) {
    HashItem *curr = NULL, *tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr->key);
        free(curr);
    }
}

#endif  // HASH_H
typedef struct {
    HashItem* cellValues;
} Spreadsheet;
Spreadsheet* spreadsheetCreate(int rows) {
    Spreadsheet* obj = NULL;

    obj = (Spreadsheet*)malloc(sizeof(Spreadsheet));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->cellValues = NULL;

    return obj;
}
void spreadsheetSetCell(Spreadsheet* obj, char* cell, int value) {
    //
    hashSetItem(&obj->cellValues, cell, value);
}
void spreadsheetResetCell(Spreadsheet* obj, char* cell) {
    //
    hashErase(&obj->cellValues, cell);
}
int getCellVal(Spreadsheet* obj, const char* cell) {
    int retVal = 0;

    if (isalpha(cell[0])) {
        retVal = hashGetItem(&obj->cellValues, cell, 0);
    } else {
        retVal = atoi(cell);
    }

    return retVal;
}
int spreadsheetGetValue(Spreadsheet* obj, char* formula) {
    int retVal = 0;

    char* plus = strchr(formula, '+');

    char* cell1 = (char*)malloc(plus - formula);
    strncpy(cell1, formula + 1, plus - formula - 1);
    cell1[plus - formula - 1] = '\0';
    char* cell2 = strdup(plus + 1);

    retVal = getCellVal(obj, cell1) + getCellVal(obj, cell2);

    free(cell1);
    free(cell2);

    return retVal;
}
void spreadsheetFree(Spreadsheet* obj) {
    hashFree(&obj->cellValues);
    free(obj);
}
/**
 * Your Spreadsheet struct will be instantiated and called as such:
 * Spreadsheet* obj = spreadsheetCreate(rows);
 * spreadsheetSetCell(obj, cell, value);
 * spreadsheetResetCell(obj, cell);
 * int param_3 = spreadsheetGetValue(obj, formula);
 * spreadsheetFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* methods;
        char* cell;
        int value;
        char* formula;
    } testCase[] = {{"Spreadsheet", NULL, 3, NULL}, {"getValue", NULL, 0, "=5+7"},  {"setCell", "A1", 10, NULL},
                    {"getValue", NULL, 0, "=A1+6"}, {"setCell", "B2", 15, NULL},    {"getValue", NULL, 0, "=A1+B2"},
                    {"resetCell", "A1", 0, NULL},   {"getValue", NULL, 0, "=A1+B2"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input:
     *  ["Spreadsheet", "getValue", "setCell", "getValue", "setCell", "getValue", "resetCell", "getValue"]
     *  [[3], ["=5+7"], ["A1", 10], ["=A1+6"], ["B2", 15], ["=A1+B2"], ["A1"], ["=A1+B2"]]
     *  Output:
     *  [null, 12, null, 16, null, 25, null, 15]
     */

    printf("Input\n");
    printf("[");
    for (int i = 0; i < numberOfTestCase; ++i) {
        printf("%s\"%s\"", (i == 0) ? "" : ", ", testCase[i].methods);
    }
    printf("]\n");
    printf("[");
    for (int i = 0; i < numberOfTestCase; ++i) {
        printf("%s", (i == 0) ? "" : ", ");
        if (strcmp(testCase[i].methods, "Spreadsheet") == 0) {
            printf("[%d]", testCase[i].value);
        } else if (strcmp(testCase[i].methods, "getValue") == 0) {
            printf("[\"%s\"]", testCase[i].formula);
        } else if (strcmp(testCase[i].methods, "setCell") == 0) {
            printf("[\"%s\", %d]", testCase[i].cell, testCase[i].value);
        } else if (strcmp(testCase[i].methods, "resetCell") == 0) {
            printf("[\"%s\"]", testCase[i].cell);
        }
    }
    printf("]\n");

    Spreadsheet* pSpreadsheet = NULL;
    printf("Output\n");
    printf("[");
    for (int i = 0; i < numberOfTestCase; ++i) {
        if (strcmp(testCase[i].methods, "Spreadsheet") == 0) {
            pSpreadsheet = spreadsheetCreate(testCase[i].value);
            printf("%snull", (i == 0) ? "" : ", ");
        } else if (strcmp(testCase[i].methods, "getValue") == 0) {
            int ret = spreadsheetGetValue(pSpreadsheet, testCase[i].formula);
            printf("%s%d", (i == 0) ? "" : ", ", ret);
        } else if (strcmp(testCase[i].methods, "setCell") == 0) {
            spreadsheetSetCell(pSpreadsheet, testCase[i].cell, testCase[i].value);
            printf("%snull", (i == 0) ? "" : ", ");
        } else if (strcmp(testCase[i].methods, "resetCell") == 0) {
            spreadsheetResetCell(pSpreadsheet, testCase[i].cell);
            printf("%snull", (i == 0) ? "" : ", ");
        }
    }
    printf("]\n");
    spreadsheetFree(pSpreadsheet);
    pSpreadsheet = NULL;

    return EXIT_SUCCESS;
}
