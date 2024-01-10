#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM (1001)  // 1 <= num <= 1000
typedef struct {
    int record[MAX_NUM];
} SmallestInfiniteSet;
SmallestInfiniteSet* smallestInfiniteSetCreate() {
    SmallestInfiniteSet* pRetVal = (SmallestInfiniteSet*)malloc(sizeof(SmallestInfiniteSet));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    int i;
    for (i = 0; i < MAX_NUM; ++i) {
        pRetVal->record[i] = 1;
    }

    return pRetVal;
}
int smallestInfiniteSetPopSmallest(SmallestInfiniteSet* obj) {
    int retVal = 0;

    int i;
    for (i = 1; i < MAX_NUM; ++i) {
        if (obj->record[i] == 1) {
            retVal = i;
            obj->record[i] = 0;
            break;
        }
    }

    return retVal;
}
void smallestInfiniteSetAddBack(SmallestInfiniteSet* obj, int num) {
    if (num > MAX_NUM) {
        return;
    }
    obj->record[num] = 1;
}
void smallestInfiniteSetFree(SmallestInfiniteSet* obj) {
    free(obj);
    obj = NULL;
}
/**
 * Your SmallestInfiniteSet struct will be instantiated and called as such:
 * SmallestInfiniteSet* obj = smallestInfiniteSetCreate();
 * int param_1 = smallestInfiniteSetPopSmallest(obj);
 * smallestInfiniteSetAddBack(obj, num);
 * smallestInfiniteSetFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE];
        int calls;
    } testCase[] = {{{"SmallestInfiniteSet", "addBack", "popSmallest", "popSmallest", "popSmallest", "addBack",
                      "popSmallest", "popSmallest", "popSmallest"},
                     {INT_MIN, 2, INT_MIN, INT_MIN, INT_MIN, 1, INT_MIN, INT_MIN, INT_MIN},
                     9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    SmallestInfiniteSet* obj = NULL;
    int retInt;
    char displayStr[8];
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
            if (testCase[i].val[j] == INT_MIN) {
                printf("%s[]", (j == 0) ? "" : ", ");
                continue;
            }
            printf("%s[%d]", (j == 0) ? "" : ", ", testCase[i].val[j]);
        }
        printf("]\n");
        /* Example
         *  Input
         *  ["SmallestInfiniteSet", "addBack", "popSmallest", "popSmallest", "popSmallest", "addBack", "popSmallest",
         * "popSmallest", "popSmallest"]
         *  [[], [2], [], [], [], [1], [], [], []]
         *  Output
         *  [null, null, 1, 2, 3, null, 1, 4, 5]
         */

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            memset(displayStr, 0, sizeof(displayStr));
            if (strcmp(testCase[i].methods[j], "SmallestInfiniteSet") == 0) {
                obj = smallestInfiniteSetCreate();
                snprintf(displayStr, sizeof(displayStr), "%s", "null");
            } else if (strcmp(testCase[i].methods[j], "addBack") == 0) {
                smallestInfiniteSetAddBack(obj, testCase[i].val[j]);
                snprintf(displayStr, sizeof(displayStr), "%s", "null");
            } else if (strcmp(testCase[i].methods[j], "popSmallest") == 0) {
                retInt = smallestInfiniteSetPopSmallest(obj);
                snprintf(displayStr, sizeof(displayStr), "%d", retInt);
            }
            printf("%s%s", (j == 0) ? "" : ", ", displayStr);
        }
        printf("]\n");

        smallestInfiniteSetFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
