#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/find-median-from-data-stream/solutions/1429457/by-goodgoodday-rcen/
#ifndef HEAP_H
#define HEAP_H

typedef struct Heap {
    int* array;
    int capacity;
    int len;
} Heap;
int HeapLen(Heap* hp) {
    int retVal = hp->len;

    return retVal;
}
bool HeapEmpty(Heap* hp) {
    bool retVal = true;

    if (HeapLen(hp) == 1) {
        return retVal;
    }
    retVal = false;

    return retVal;
}
bool HeapFull(Heap* hp) {
    bool retVal = true;

    if (hp->capacity == hp->len) {
        return retVal;
    }
    retVal = false;

    return retVal;
}
void HeapSwap(int* pLeft, int* pRight) {
    int temp = *pLeft;
    *pLeft = *pRight;
    *pRight = temp;
}
int HeapGetTop(Heap* hp) {
    int retVal = hp->array[1];

    return retVal;
}
Heap* CreateHeap(int size) {
    Heap* heap = NULL;

    heap = (Heap*)malloc(sizeof(Heap));
    if (heap == NULL) {
        perror("malloc");
        return heap;
    }

    int heapLen = size + 1;
    heap->array = (int*)malloc(sizeof(int) * heapLen);
    if (heap->array == NULL) {
        perror("malloc");
        free(heap);
        heap = NULL;
        return heap;
    }
    heap->capacity = heapLen;
    heap->len = 1;

    return heap;
}
void HeapAdjustDown(Heap* hp, int parent, bool isMax) {
    int child = 2 * parent;
    int len = hp->len;
    while (child < len) {
        if (isMax == true) {
            if ((child + 1 < len) && hp->array[child] < hp->array[child + 1]) {
                child = child + 1;
            }

            if (hp->array[child] > hp->array[parent]) {
                HeapSwap(&hp->array[child], &hp->array[parent]);
                parent = child;
                child = parent << 1;
            } else {
                return;
            }
        } else {
            if ((child + 1 < len) && hp->array[child] > hp->array[child + 1]) {
                child = child + 1;
            }

            if (hp->array[child] < hp->array[parent]) {
                HeapSwap(&hp->array[child], &hp->array[parent]);
                parent = child;
                child = parent << 1;
            } else {
                return;
            }
        }
    }
}
void HeapAdjustUp(Heap* hp, int child, bool isMax) {
    int parent = child / 2;
    while (child > 1) {
        if (isMax == true) {
            if (hp->array[child] > hp->array[parent]) {
                HeapSwap(&hp->array[child], &hp->array[parent]);
                child = parent;
                parent = child / 2;
            } else {
                return;
            }
        } else {
            if (hp->array[child] < hp->array[parent]) {
                HeapSwap(&hp->array[child], &hp->array[parent]);
                child = parent;
                parent = child / 2;
            } else {
                return;
            }
        }
    }
}
void HeapDelete(Heap* hp, bool isMax) {
    if (HeapEmpty(hp) == true) {
        return;
    }

    hp->array[1] = hp->array[hp->len - 1];
    hp->len--;
    HeapAdjustDown(hp, 1, isMax);
}
void HeapInsert(Heap* hp, int dat, bool isMax) {
    if (HeapFull(hp) == true) {
        hp->capacity <<= 1;
        hp->array = (int*)realloc(hp->array, hp->capacity * sizeof(int));
    }
    hp->array[hp->len++] = dat;
    HeapAdjustUp(hp, hp->len - 1, isMax);
}
void heapFree(Heap* hp) {
    free(hp->array);
    hp->array = NULL;
    free(hp);
    hp = NULL;
}

#endif  // HEAP_H
typedef struct {
    Heap* maxLHeap;
    Heap* minRHeap;
} MedianFinder;
MedianFinder* medianFinderCreate() {
    MedianFinder* pRetVal = NULL;

    pRetVal = (MedianFinder*)malloc(sizeof(MedianFinder));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->maxLHeap = CreateHeap(128);
    pRetVal->minRHeap = CreateHeap(128);

    return pRetVal;
}
void medianFinderAddNum(MedianFinder* obj, int num) {
    int maxLHeapSize = obj->maxLHeap->len;
    int minRHeapSize = obj->minRHeap->len;

    int moveValue;

    if (maxLHeapSize <= minRHeapSize) {
        if (HeapEmpty(obj->minRHeap) == false) {
            if (num > obj->minRHeap->array[1]) {
                moveValue = obj->minRHeap->array[1];
                obj->minRHeap->array[1] = num;
                HeapAdjustDown(obj->minRHeap, 1, false);
                HeapInsert(obj->maxLHeap, moveValue, true);

                return;
            }
        }
        HeapInsert(obj->maxLHeap, num, true);

        return;
    }

    if (HeapEmpty(obj->maxLHeap) == false) {
        if (num < obj->maxLHeap->array[1]) {
            moveValue = obj->maxLHeap->array[1];
            obj->maxLHeap->array[1] = num;
            HeapAdjustDown(obj->maxLHeap, 1, true);
            HeapInsert(obj->minRHeap, moveValue, false);

            return;
        }
    }
    HeapInsert(obj->minRHeap, num, false);
}
double medianFinderFindMedian(MedianFinder* obj) {
    double retVal = 0;

    int maxLHeapSize = obj->maxLHeap->len;
    int minRHeapSize = obj->minRHeap->len;
    if (maxLHeapSize == minRHeapSize) {
        retVal = (double)(obj->minRHeap->array[1] + obj->maxLHeap->array[1]) / 2;
    } else {
        retVal = (double)(obj->maxLHeap->array[1]);
    }

    return retVal;
}
void medianFinderFree(MedianFinder* obj) {
    heapFree(obj->maxLHeap);
    obj->maxLHeap = NULL;
    heapFree(obj->minRHeap);
    obj->minRHeap = NULL;
    free(obj);
    obj = NULL;
}
/*
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 * double param_2 = medianFinderFindMedian(obj);
 * medianFinderFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE];
        int calls;
    } testCase[] = {{{"MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"},
                     {INT_MIN, 1, 2, INT_MIN, 3, INT_MIN},
                     6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
     *  [[], [1], [2], [], [3], []]
     *  Output
     *  [null, null, null, 1.5, null, 2.0]
     */

#define STR_EMPTY ""
#define STR_COMMA ", "
    char displayStr[16];
    MedianFinder* MedianFinder;
    double retValue;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0 ? STR_EMPTY : STR_COMMA), testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            memset(displayStr, 0, sizeof(displayStr));
            snprintf(displayStr, sizeof(displayStr), "%d", testCase[i].val[j]);
            printf("%s[%s]", (j == 0 ? STR_EMPTY : STR_COMMA), (testCase[i].val[j] == INT_MIN) ? "" : displayStr);
        }
        printf("]\n");

        MedianFinder = NULL;
        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "MedianFinder") == 0) {
                MedianFinder = medianFinderCreate();
                printf("%s%s", "null", (j == (testCase[i].calls - 1) ? STR_EMPTY : STR_COMMA));
            } else if (strcmp(testCase[i].methods[j], "addNum") == 0) {
                medianFinderAddNum(MedianFinder, testCase[i].val[j]);
                printf("%s%s", "null", (j == (testCase[i].calls - 1) ? STR_EMPTY : STR_COMMA));
            } else if (strcmp(testCase[i].methods[j], "findMedian") == 0) {
                retValue = medianFinderFindMedian(MedianFinder);
                printf("%.01f%s", retValue, (j == (testCase[i].calls - 1) ? STR_EMPTY : STR_COMMA));
            }
        }
        printf("]\n");
        medianFinderFree(MedianFinder);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
