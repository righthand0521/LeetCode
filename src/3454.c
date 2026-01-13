#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* count;
    int* covered;
    int* xs;
    int n;
} SegmentTree;
typedef struct {
    int y;
    int delta;
    int xl;
    int xr;
} Event;
SegmentTree* createSegmentTree(int* xs, int xsSize) {
    SegmentTree* pObj = NULL;

    pObj = (SegmentTree*)malloc(sizeof(SegmentTree));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    memset(pObj, 0, sizeof(SegmentTree));

    pObj->xs = (int*)malloc(sizeof(int) * xsSize);
    if (pObj->xs == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    memcpy(pObj->xs, xs, sizeof(int) * xsSize);

    pObj->n = xsSize - 1;
    int size = 4 * pObj->n;

    pObj->count = (int*)calloc(size, sizeof(int));
    if (pObj->count == NULL) {
        perror("calloc");
        free(pObj->xs);
        pObj->xs = NULL;
        free(pObj);
        pObj = NULL;
        return pObj;
    }

    pObj->covered = (int*)calloc(size, sizeof(int));
    if (pObj->covered == NULL) {
        perror("calloc");
        free(pObj->count);
        pObj->count = NULL;
        free(pObj->xs);
        pObj->xs = NULL;
        free(pObj);
        pObj = NULL;
        return pObj;
    }

    return pObj;
}
void freeSegmentTree(SegmentTree* st) {
    free(st->count);
    st->count = NULL;
    free(st->covered);
    st->covered = NULL;
    free(st->xs);
    st->xs = NULL;
    free(st);
    st = NULL;
}
void modify(SegmentTree* st, int qleft, int qright, int qval, int left, int right, int pos) {
    if ((st->xs[right + 1] <= qleft) || (st->xs[left] >= qright)) {
        return;
    }

    int middle;
    if ((qleft <= st->xs[left]) && (st->xs[right + 1] <= qright)) {
        st->count[pos] += qval;
    } else {
        middle = (left + right) / 2;
        modify(st, qleft, qright, qval, left, middle, pos * 2 + 1);
        modify(st, qleft, qright, qval, middle + 1, right, pos * 2 + 2);
    }

    if (st->count[pos] > 0) {
        st->covered[pos] = st->xs[right + 1] - st->xs[left];
    } else {
        if (left == right) {
            st->covered[pos] = 0;
        } else {
            st->covered[pos] = st->covered[pos * 2 + 1] + st->covered[pos * 2 + 2];
        }
    }
}
void updateSegmentTree(SegmentTree* st, int qleft, int qright, int qval) {
    modify(st, qleft, qright, qval, 0, st->n - 1, 0);
}
int querySegmentTree(SegmentTree* st) {
    int retVal = st->covered[0];

    return retVal;
}
int compareEvents(const void* a, const void* b) {
    int retVal = 0;

    Event* e1 = (Event*)a;
    Event* e2 = (Event*)b;
    retVal = e1->y - e2->y;

    return retVal;
}
int compareInts(const void* a, const void* b) {
    int retVal = *(int*)a - *(int*)b;

    return retVal;
}
int binarySearch(long long* arr, int size, long long target) {
    int retVal = 0;

    int middle;
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        middle = left + (right - left) / 2;
        if (arr[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    retVal = left - 1;  // return the last position less than targe

    return retVal;
}
int unique(int* arr, int arrSize) {
    int retVal = 0;

    if (arrSize <= 1) {
        retVal = arrSize;
        return retVal;
    }

    int j = 0;
    for (int i = 1; i < arrSize; i++) {
        if (arr[i] != arr[j]) {
            j++;
            arr[j] = arr[i];
        }
    }
    retVal = j + 1;

    return retVal;
}
double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    double retVal = 0;

    Event* events = (Event*)malloc(sizeof(Event) * squaresSize * 2);
    if (events == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(events, 0, sizeof(Event) * squaresSize * 2);

    int* xs = (int*)malloc(sizeof(int) * squaresSize * 4);
    if (xs == NULL) {
        perror("malloc");
        free(events);
        events = NULL;
        return retVal;
    }
    memset(xs, 0, sizeof(int) * squaresSize * 4);

    int eventsSize = 0;
    int xsSize = 0;

    // collect all events and x coordinates
    int x, y, l, xr;
    for (int i = 0; i < squaresSize; i++) {
        x = squares[i][0];
        y = squares[i][1];
        l = squares[i][2];
        xr = x + l;

        xs[xsSize++] = x;
        xs[xsSize++] = xr;
        events[eventsSize++] = (Event){y, 1, x, xr};
        events[eventsSize++] = (Event){y + l, -1, x, xr};
    }

    // sort events by y-coordinate
    qsort(events, eventsSize, sizeof(Event), compareEvents);
    // sort and remove duplicates x-coordinate
    qsort(xs, xsSize, sizeof(int), compareInts);

    xsSize = unique(xs, xsSize);

    // create a segment tree
    SegmentTree* segTree = createSegmentTree(xs, xsSize);
    if (segTree == NULL) {
        free(events);
        events = NULL;
        free(xs);
        xs = NULL;
        return retVal;
    }

    // save prefix sums and widths
    long long* psum = (long long*)malloc(sizeof(long long) * eventsSize);
    if (psum == NULL) {
        perror("malloc");
        free(events);
        events = NULL;
        free(xs);
        xs = NULL;
        freeSegmentTree(segTree);
        segTree = NULL;
        return retVal;
    }
    memset(psum, 0, sizeof(long long) * eventsSize);

    int* widths = (int*)malloc(sizeof(int) * eventsSize);
    if (widths == NULL) {
        perror("malloc");
        free(events);
        events = NULL;
        free(xs);
        xs = NULL;
        free(psum);
        psum = NULL;
        freeSegmentTree(segTree);
        segTree = NULL;
        return retVal;
    }
    memset(widths, 0, sizeof(int) * eventsSize);

    long long totalArea = 0LL;
    int prev = events[0].y;

    // scan: calculate total area and record intermediate states
    int eventY, eventDelta, eventXl, eventXr;
    for (int i = 0; i < eventsSize; i++) {
        eventY = events[i].y;
        eventDelta = events[i].delta;
        eventXl = events[i].xl;
        eventXr = events[i].xr;

        totalArea += (double)querySegmentTree(segTree) * (eventY - prev);
        updateSegmentTree(segTree, eventXl, eventXr, eventDelta);

        // record prefix sums and widths
        psum[i] = totalArea;
        widths[i] = querySegmentTree(segTree);
        prev = eventY;
    }

    // calculate the target area (half rounded up)
    long long target = (long long)(totalArea + 1) / 2;
    // find the first position greater than or equal to target using binary search
    int idx = binarySearch(psum, eventsSize, (double)target);
    // get the corresponding area, width, and height
    double area = psum[idx];
    int width = widths[idx];
    int height = events[idx].y;

    retVal = height + (totalArea - area * 2) / (width * 2.0);

    //
    free(events);
    events = NULL;
    free(xs);
    xs = NULL;
    free(psum);
    psum = NULL;
    free(widths);
    widths = NULL;
    freeSegmentTree(segTree);
    segTree = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(5 * 10000)
    struct testCaseType {
        int squares[MAX_SIZE][3];
        int squaresSize;
        int squaresColSize[MAX_SIZE];
    } testCase[] = {{{{0, 0, 1}, {2, 2, 1}}, 2, {3, 3}}, {{{0, 0, 2}, {1, 1, 1}}, 2, {3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: squares = [[0,0,1],[2,2,1]]
     *  Output: 1.00000
     *
     *  Input: squares = [[0,0,2],[1,1,1]]
     *  Output: 1.00000
     */

    int** pSquares = NULL;
    double answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("squares = [");
        for (j = 0; j < testCase[i].squaresSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].squaresColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].squares[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pSquares = (int**)malloc(testCase[i].squaresSize * sizeof(int*));
        if (pSquares == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pSquares, 0, testCase[i].squaresSize * sizeof(int*));
        for (j = 0; j < testCase[i].squaresSize; ++j) {
            pSquares[j] = (int*)malloc(testCase[i].squaresColSize[j] * sizeof(int));
            if (pSquares[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pSquares[k]);
                    pSquares[k] = NULL;
                }
                free(pSquares);
                pSquares = NULL;
            }
            memset(pSquares[j], 0, (testCase[i].squaresColSize[j] * sizeof(int)));
            memcpy(pSquares[j], testCase[i].squares[j], (testCase[i].squaresColSize[j] * sizeof(int)));
        }
        answer = separateSquares(pSquares, testCase[i].squaresSize, testCase[i].squaresColSize);
        printf("Output: %.5f\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].squaresSize; ++j) {
            free(pSquares[j]);
            pSquares[j] = NULL;
        }
        free(pSquares);
        pSquares = NULL;
    }

    return EXIT_SUCCESS;
}
