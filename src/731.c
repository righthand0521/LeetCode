#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CALLS (1000 + 4)  // At most 1000 calls will be made to book.
typedef struct {
    int bookings[MAX_CALLS][2];
    int bookingsIndex;
    int overlapBookings[MAX_CALLS][2];
    int overlapBookingsIndex;
} MyCalendarTwo;
MyCalendarTwo* myCalendarTwoCreate() {
    MyCalendarTwo* pObj = NULL;

    pObj = (MyCalendarTwo*)malloc(sizeof(MyCalendarTwo));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    memset(pObj, 0, sizeof(MyCalendarTwo));
    pObj->bookingsIndex = 0;
    pObj->overlapBookingsIndex = 0;

    return pObj;
}
// Return true if the booking [start1, end1) & [start2, end2) overlaps.
bool doesOverlap(MyCalendarTwo* obj, int start1, int end1, int start2, int end2) {
    bool retVal = false;

    int maxStart = fmax(start1, start2);
    int minEnd = fmin(end1, end2);
    if (maxStart < minEnd) {
        retVal = true;
    }

    return retVal;
}
// Return overlapping booking between [start1, end1) & [start2, end2).
void getOverlapped(MyCalendarTwo* obj, int start1, int end1, int start2, int end2) {
    obj->overlapBookings[obj->overlapBookingsIndex][0] = fmax(start1, start2);
    obj->overlapBookings[obj->overlapBookingsIndex][1] = fmin(end1, end2);
    obj->overlapBookingsIndex += 1;
}
bool myCalendarTwoBook(MyCalendarTwo* obj, int start, int end) {
    bool retVal = false;

    int i;

    // Returns false if the new booking overlaps with the existing double-booked bookings.
    for (i = 0; i < obj->overlapBookingsIndex; ++i) {
        if (doesOverlap(obj, obj->overlapBookings[i][0], obj->overlapBookings[i][1], start, end) == true) {
            return retVal;
        }
    }

    // Add the double overlapping if any with the new booking.
    int bookStart, bookEnd;
    for (i = 0; i < obj->bookingsIndex; ++i) {
        bookStart = obj->bookings[i][0];
        bookEnd = obj->bookings[i][1];
        if (doesOverlap(obj, bookStart, bookEnd, start, end) == true) {
            getOverlapped(obj, bookStart, bookEnd, start, end);
        }
    }

    // Add the booking to the list of bookings.
    obj->bookings[obj->bookingsIndex][0] = start;
    obj->bookings[obj->bookingsIndex][1] = end;
    obj->bookingsIndex += 1;
    retVal = true;

    return retVal;
}
void myCalendarTwoFree(MyCalendarTwo* obj) {
    free(obj);
    obj = NULL;
}
/**
 * Your MyCalendarTwo struct will be instantiated and called as such:
 * MyCalendarTwo* obj = myCalendarTwoCreate();
 * bool param_1 = myCalendarTwoBook(obj, start, end);
 * myCalendarTwoFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][2];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"MyCalendarTwo", "book", "book", "book", "book", "book", "book"},
                     {{}, {10, 20}, {50, 60}, {10, 40}, {5, 15}, {5, 10}, {25, 55}},
                     {1, 2, 2, 2, 2, 2, 2},
                     7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["MyCalendarTwo", "book", "book", "book", "book", "book", "book"]
     *  [[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
     *  Output
     *  [null, true, true, true, false, true, true]
     */

    MyCalendarTwo* obj = NULL;
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

            if (strcmp(testCase[i].methods[j], "MyCalendarTwo") == 0) {
                obj = myCalendarTwoCreate();
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "book") == 0) {
                retVal = myCalendarTwoBook(obj, testCase[i].val[j][0], testCase[i].val[j][1]);
                printf("%s%s", (j == 0) ? "" : " ", (retVal == true ? "true" : "false"));
            }
        }
        printf("]\n");

        myCalendarTwoFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
