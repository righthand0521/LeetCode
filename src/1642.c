#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HEAP_H
#define HEAP_H

//
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
//
typedef struct {
    int* data;     // Array to store the heap elements
    int size;      // Current size of the heap
    int capacity;  // Maximum capacity of the heap
} MinHeap;
//
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = NULL;

    minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (minHeap == NULL) {
        perror("malloc");
        return minHeap;
    }

    minHeap->data = (int*)malloc(capacity * sizeof(int));
    if (minHeap == NULL) {
        perror("malloc");
        free(minHeap);
        minHeap = NULL;
        return minHeap;
    }
    minHeap->size = 0;
    minHeap->capacity = capacity;

    return minHeap;
}
void heapifyMinHeap(MinHeap* minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Function to heapify the heap starting from the given index
    if ((left < minHeap->size) && (minHeap->data[left] < minHeap->data[smallest])) {
        smallest = left;
    }

    if ((right < minHeap->size) && (minHeap->data[right] < minHeap->data[smallest])) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&minHeap->data[index], &minHeap->data[smallest]);
        heapifyMinHeap(minHeap, smallest);
    }
}
void pushMinHeap(MinHeap* minHeap, int value) {
    if (minHeap->size == minHeap->capacity) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    int index = minHeap->size++;
    minHeap->data[index] = value;

    // Fix the min heap property by comparing the value with its parent
    while ((index != 0) && (minHeap->data[(index - 1) / 2] > minHeap->data[index])) {
        swap(&minHeap->data[(index - 1) / 2], &minHeap->data[index]);
        index = (index - 1) / 2;
    }
}
int popMinHeap(MinHeap* minHeap) {
    int retVal = -1;

    if (minHeap->size == 0) {
        printf("Heap is empty. Cannot remove elements.\n");
        return retVal;
    }

    retVal = minHeap->data[0];
    minHeap->data[0] = minHeap->data[minHeap->size - 1];
    minHeap->size--;
    heapifyMinHeap(minHeap, 0);

    return retVal;
}
void printMinHeap(MinHeap* minHeap) {
    printf("Min Heap: ");
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->data[i]);
    }
    printf("\n");
}
void freeMinHeap(MinHeap* minHeap) {
    free(minHeap->data);
    minHeap->data = NULL;
    free(minHeap);
    minHeap = NULL;
}

#endif  // HEAP_H
int furthestBuilding(int* heights, int heightsSize, int bricks, int ladders) {
    int retVal = 0;

    int brickSum = 0;
    MinHeap* pLaddersHeap = createMinHeap(heightsSize);
    if (pLaddersHeap == NULL) {
        return retVal;
    }

    int diff;
    int i;
    for (i = 1; i < heightsSize; ++i) {
        diff = heights[i] - heights[i - 1];
        if (diff <= 0) {
            continue;
        }

        pushMinHeap(pLaddersHeap, diff);
        if (pLaddersHeap->size > ladders) {
            brickSum += popMinHeap(pLaddersHeap);
        }

        if (brickSum > bricks) {
            retVal = i - 1;
            goto exit;
        }
    }
    retVal = heightsSize - 1;

exit:
    //
    freeMinHeap(pLaddersHeap);
    pLaddersHeap = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int heights[MAX_SIZE];
        int heightsSize;
        int bricks;
        int ladders;
    } testCase[] = {
        {{4, 2, 7, 6, 9, 14, 12}, 7, 5, 1}, {{4, 12, 2, 7, 3, 18, 20, 3, 19}, 9, 10, 2}, {{14, 3, 19, 3}, 4, 17, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
     *  Output: 4
     *
     *  Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
     *  Output: 7
     *
     *  Input: heights = [14,3,19,3], bricks = 17, ladders = 0
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: heights = [");
        for (j = 0; j < testCase[i].heightsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].heights[j]);
        }
        printf("], bricks = %d, ladders = %d\n", testCase[i].bricks, testCase[i].ladders);

        answer =
            furthestBuilding(testCase[i].heights, testCase[i].heightsSize, testCase[i].bricks, testCase[i].ladders);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
