#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HEAP_H
#define HEAP_H

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
typedef struct {
    int* data;     // Array to store the heap elements
    int size;      // Current size of the heap
    int capacity;  // Maximum capacity of the heap
} MaxHeap;
MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* pObj = NULL;

    pObj = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }

    pObj->data = (int*)malloc(capacity * sizeof(int));
    if (pObj == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->size = 0;
    pObj->capacity = capacity;

    return pObj;
}
void heapifyMaxHeap(MaxHeap* pObj, int index) {
    int biggest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Function to heapify the heap starting from the given index
    if ((left < pObj->size) && (pObj->data[left] > pObj->data[biggest])) {
        biggest = left;
    }

    if ((right < pObj->size) && (pObj->data[right] > pObj->data[biggest])) {
        biggest = right;
    }

    if (biggest != index) {
        swap(&pObj->data[index], &pObj->data[biggest]);
        heapifyMaxHeap(pObj, biggest);
    }
}
void pushMaxHeap(MaxHeap* pObj, int value) {
    if (pObj->size == pObj->capacity) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    int index = pObj->size++;
    pObj->data[index] = value;

    // Fix the max heap property by comparing the value with its parent
    while ((index != 0) && (pObj->data[(index - 1) / 2] < pObj->data[index])) {
        swap(&pObj->data[(index - 1) / 2], &pObj->data[index]);
        index = (index - 1) / 2;
    }
}
int popMaxHeap(MaxHeap* pObj) {
    int retVal = -1;

    if (pObj->size == 0) {
        printf("Heap is empty. Cannot remove elements.\n");
        return retVal;
    }

    retVal = pObj->data[0];
    pObj->data[0] = pObj->data[pObj->size - 1];
    pObj->size--;
    heapifyMaxHeap(pObj, 0);

    return retVal;
}
void printMaxHeap(MaxHeap* pObj) {
    printf("Max Heap: ");
    for (int i = 0; i < pObj->size; i++) {
        printf("%d ", pObj->data[i]);
    }
    printf("\n");
}
void freeMaxHeap(MaxHeap* pObj) {
    free(pObj->data);
    pObj->data = NULL;
    free(pObj);
    pObj = NULL;
}

#endif  // HEAP_H
long long pickGifts(int* gifts, int giftsSize, int k) {
    long long retVal = 0;

    MaxHeap* pGiftsHeap = createMaxHeap(giftsSize);
    if (pGiftsHeap == NULL) {
        return retVal;
    }
    for (int i = 0; i < giftsSize; ++i) {
        pushMaxHeap(pGiftsHeap, gifts[i]);
    }

    int maxElement;
    for (int i = 0; i < k; ++i) {
        maxElement = popMaxHeap(pGiftsHeap);
        pushMaxHeap(pGiftsHeap, sqrt(maxElement));
    }

    for (int i = 0; i < pGiftsHeap->size; ++i) {
        retVal += pGiftsHeap->data[i];
    }

    //
    freeMaxHeap(pGiftsHeap);
    pGiftsHeap = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e3)
    struct testCaseType {
        int gifts[MAX_SIZE];
        int giftsSize;
        int k;
    } testCase[] = {{{25, 64, 9, 4, 100}, 5, 4}, {{1, 1, 1, 1}, 4, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: gifts = [25,64,9,4,100], k = 4
     *  Output: 29
     *
     *  Input: gifts = [1,1,1,1], k = 4
     *  Output: 4
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: gifts = [");
        for (j = 0; j < testCase[i].giftsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].gifts[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = pickGifts(testCase[i].gifts, testCase[i].giftsSize, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
