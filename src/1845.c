#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/seat-reservation-manager/solutions/1778519/by-letcode_q-ad4q/
typedef struct {
    int* heap;
    int heapSize;
} SeatManager;
SeatManager* seatManagerCreate(int n) {
    SeatManager* pRetVal = NULL;

    pRetVal = (SeatManager*)malloc(sizeof(SeatManager));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int* heap = (int*)malloc(sizeof(int) * n);
    if (pRetVal == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    int i;
    for (i = 0; i < n; i++) {
        heap[i] = i + 1;
    }
    pRetVal->heap = heap;
    pRetVal->heapSize = n;

    return pRetVal;
}
int seatManagerReserve(SeatManager* seatManager) {
    int retVal = 0;

    int* heap = seatManager->heap;
    retVal = heap[0];
    heap[0] = heap[seatManager->heapSize - 1];
    seatManager->heapSize--;

    int tmp;
    int dad = 0;
    int son = 2 * dad + 1;
    while (son < seatManager->heapSize) {
        if (son + 1 < seatManager->heapSize && heap[son + 1] < heap[son]) {
            son++;
        }

        if (heap[dad] < heap[son]) {
            break;
        }

        if (heap[dad] > heap[son]) {
            tmp = heap[dad];
            heap[dad] = heap[son];
            heap[son] = tmp;
        }
        dad = son;
        son = 2 * dad + 1;
    }

    return retVal;
}
void seatManagerUnreserve(SeatManager* seatManager, int seatNumber) {
    int* heap = seatManager->heap;
    heap[seatManager->heapSize++] = seatNumber;

    int tmp;
    int son = seatManager->heapSize - 1;
    int dad = (son + 1) / 2 - 1;
    while (dad >= 0) {
        if (son + 1 < seatManager->heapSize && heap[son + 1] < heap[son]) {
            son++;
        }

        if (heap[dad] < heap[son]) {
            break;
        }

        if (heap[dad] > heap[son]) {
            tmp = heap[dad];
            heap[dad] = heap[son];
            heap[son] = tmp;
        }
        son = dad;
        dad = (son + 1) / 2 - 1;
    }
}
void seatManagerFree(SeatManager* obj) {
    free(obj->heap);
    obj->heap = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your SeatManager struct will be instantiated and called as such:
 * SeatManager* obj = seatManagerCreate(n);
 * int param_1 = seatManagerReserve(obj);
 * seatManagerUnreserve(obj, seatNumber);
 * seatManagerFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][3];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {
        {{"SeatManager", "reserve", "reserve", "unreserve", "reserve", "reserve", "reserve", "reserve", "unreserve"},
         {{5}, {}, {}, {2}, {}, {}, {}, {}, {5}},
         {1, 0, 0, 1, 0, 0, 0, 0, 1},
         9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["SeatManager", "reserve", "reserve", "unreserve", "reserve", "reserve", "reserve", "reserve", "unreserve"]
     *  [[5], [], [], [2], [], [], [], [], [5]]
     *  Output
     *  [null, 1, 2, null, 2, 3, 4, 5, null]
     */

    SeatManager* obj = NULL;
    int retInt;
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
                printf("%s%d", (k == 0) ? "" : ", ", testCase[i].val[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "SeatManager") == 0) {
                obj = seatManagerCreate(testCase[i].val[j][0]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "reserve") == 0) {
                retInt = seatManagerReserve(obj);
                printf("%s%d", (j == 0) ? "" : ", ", retInt);
            } else if (strcmp(testCase[i].methods[j], "unreserve") == 0) {
                seatManagerUnreserve(obj, testCase[i].val[j][0]);
                printf("%snull", (j == 0) ? "" : ", ");
            }
        }
        printf("]\n");

        seatManagerFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
