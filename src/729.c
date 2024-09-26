#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CALLS (1000 + 4)  // At most 1000 calls will be made to book.
typedef struct {
    int start[MAX_CALLS];
    int end[MAX_CALLS];
    int idx;
} MyCalendar;
MyCalendar* myCalendarCreate() {
    MyCalendar* pObj = NULL;

    pObj = (MyCalendar*)malloc(sizeof(MyCalendar));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    memset(pObj, -1, sizeof(MyCalendar));
    pObj->idx = 0;

    return pObj;
}
bool myCalendarBook(MyCalendar* obj, int start, int end) {
    bool retVal = false;

    if (obj->idx == 0) {
        obj->start[obj->idx] = start;
        obj->end[obj->idx] = end;
        obj->idx += 1;
        retVal = true;
        return retVal;
    }

    int i;
    for (i = 0; i < obj->idx; ++i) {
        if ((start >= obj->start[i]) && (start < obj->end[i])) {
            return retVal;
        } else if ((end > obj->start[i]) && (end < obj->end[i])) {
            return retVal;
        } else if ((start <= obj->start[i]) && (end >= obj->end[i])) {
            return retVal;
        }
    }

    obj->start[obj->idx] = start;
    obj->end[obj->idx] = end;
    obj->idx += 1;
    retVal = true;

    return retVal;
}
void myCalendarFree(MyCalendar* obj) {
    free(obj);
    obj = NULL;
}
/**
 * Your MyCalendar struct will be instantiated and called as such:
 * MyCalendar* obj = myCalendarCreate();
 * bool param_1 = myCalendarBook(obj, start, end);
 * myCalendarFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][2];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"MyCalendar", "book", "book", "book"}, {{}, {10, 20}, {15, 25}, {20, 30}}, {1, 2, 2, 2}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["MyCalendar", "book", "book", "book"]
     *  [[], [10, 20], [15, 25], [20, 30]]
     *  Output
     *  [null, true, false, true]
     */

    MyCalendar* obj = NULL;
    bool retVal;
    int i, j, k;
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
            for (k = 0; k < testCase[i].valSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].val[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s", (j == 0) ? "" : ",");

            if (strcmp(testCase[i].methods[j], "MyCalendar") == 0) {
                obj = myCalendarCreate();
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "book") == 0) {
                retVal = myCalendarBook(obj, testCase[i].val[j][0], testCase[i].val[j][1]);
                printf("%s%s", (j == 0) ? "" : " ", (retVal == true ? "true" : "false"));
            }
        }
        printf("]\n");

        myCalendarFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
