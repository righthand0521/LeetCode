#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL (20 + 4)  // 1 <= url.length <= 20
#define MAX_CALL (5000)   // At most 5000 calls will be made to visit, back, and forward.
typedef struct {
    char url[MAX_URL];
} DataType;
typedef struct {
    DataType pageStack[MAX_CALL];
    int top;
    int current;
} BrowserHistory;
BrowserHistory* browserHistoryCreate(char* homepage) {
    BrowserHistory* obj = NULL;

    obj = malloc(sizeof(BrowserHistory));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    memset(obj, 0, sizeof(BrowserHistory));

    strcpy(obj->pageStack[obj->top].url, homepage);
    (obj->top)++;

    return obj;
}
void browserHistoryVisit(BrowserHistory* obj, char* url) {
    if ((obj == NULL) || (url == NULL)) {
        return;
    }

    obj->top = obj->current + 1;
    strcpy(obj->pageStack[obj->top].url, url);
    (obj->top)++;
    (obj->current)++;
}
char* browserHistoryBack(BrowserHistory* obj, int steps) {
    char* retVal = NULL;

    if (obj == NULL) {
        return retVal;
    }

    if (steps > obj->current) {
        steps = obj->current;
    }
    obj->current = obj->current - steps;
    retVal = obj->pageStack[obj->current].url;

    return retVal;
}
char* browserHistoryForward(BrowserHistory* obj, int steps) {
    char* retVal = NULL;

    if (obj == NULL) {
        return retVal;
    }

    if (steps > obj->top - obj->current - 1) {
        steps = obj->top - obj->current - 1;
    }
    obj->current = obj->current + steps;
    retVal = obj->pageStack[obj->current].url;

    return retVal;
}
void browserHistoryFree(BrowserHistory* obj) {
    if (obj == NULL) {
        return;
    }

    free(obj);
}
/**
 * Your BrowserHistory struct will be instantiated and called as such:
 * BrowserHistory* obj = browserHistoryCreate(homepage);
 * browserHistoryVisit(obj, url);
 * char * param_2 = browserHistoryBack(obj, steps);
 * char * param_3 = browserHistoryForward(obj, steps);
 * browserHistoryFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        char* value1[MAX_SIZE];
        int value2[MAX_SIZE];
        int calls;
    } testCase[] = {
        {{"BrowserHistory", "visit", "visit", "visit", "back", "back", "forward", "visit", "forward", "back", "back"},
         {"leetcode.com", "google.com", "facebook.com", "youtube.com", "", "", "", "linkedin.com", "", "", ""},
         {0, 0, 0, 0, 1, 1, 1, 0, 2, 2, 7},
         11}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input:
     *  ["BrowserHistory","visit","visit","visit","back","back","forward","visit","forward","back","back"]
     *  [["leetcode.com"],["google.com"],["facebook.com"],["youtube.com"],[1],[1],[1],["linkedin.com"],[2],[2],[7]]
     *  Output:
     *  [null,null,null,null,"facebook.com","google.com","facebook.com",null,"linkedin.com","google.com","leetcode.com"]
     */

    BrowserHistory* obj = NULL;
    char* retStr;
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
            printf("%s[", (j == 0) ? "" : ", ");
            if (testCase[i].value2[j] == 0) {
                printf("\"%s\"", testCase[i].value1[j]);
            } else {
                printf("%d", testCase[i].value2[j]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "BrowserHistory") == 0) {
                obj = browserHistoryCreate(testCase[i].value1[j]);
                if (obj == NULL) {
                    return EXIT_FAILURE;
                }
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "visit") == 0) {
                browserHistoryVisit(obj, testCase[i].value1[j]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "back") == 0) {
                retStr = browserHistoryBack(obj, testCase[i].value2[j]);
                printf("%s\"%s\"", (j == 0) ? "" : ", ", retStr);
            } else if (strcmp(testCase[i].methods[j], "forward") == 0) {
                retStr = browserHistoryForward(obj, testCase[i].value2[j]);
                printf("%s\"%s\"", (j == 0) ? "" : ", ", retStr);
            }
        }
        printf("]\n");

        browserHistoryFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
