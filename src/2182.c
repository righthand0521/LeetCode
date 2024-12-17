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
char* repeatLimitedString(char* s, int repeatLimit) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    int i;

    int returnSize = sSize + 1;
    pRetVal = (char*)calloc(returnSize, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    int frequencySize = 26;  // s consists of lowercase English letters.
    int frequency[frequencySize];
    memset(frequency, 0, sizeof(frequency));
    for (i = 0; i < sSize; ++i) {
        frequency[s[i] - 'a']++;
    }

    MaxHeap* pMaxHeap = createMaxHeap(frequencySize);
    if (pMaxHeap == NULL) {
        return pRetVal;
    }
    for (i = 0; i < frequencySize; ++i) {
        if (frequency[i] != 0) {
            pushMaxHeap(pMaxHeap, i);
        }
    }

    returnSize = 0;
    int charInt, nextCharInt;
    int count, use;
    while (pMaxHeap->size > 0) {
        charInt = popMaxHeap(pMaxHeap);

        count = frequency[charInt];
        use = fmin(count, repeatLimit);
        for (i = 0; i < use; ++i) {
            pRetVal[returnSize++] = charInt + 'a';
        }
        frequency[charInt] -= use;
        if ((frequency[charInt] > 0) && (pMaxHeap->size > 0)) {
            nextCharInt = popMaxHeap(pMaxHeap);

            pRetVal[returnSize++] = nextCharInt + 'a';
            frequency[nextCharInt]--;
            if (frequency[nextCharInt] > 0) {
                pushMaxHeap(pMaxHeap, nextCharInt);
            }

            pushMaxHeap(pMaxHeap, charInt);
        }
    }

    //
    freeMaxHeap(pMaxHeap);
    pMaxHeap = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        int repeatLimit;
    } testCase[] = {{"cczazcc", 3}, {"aababab", 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "cczazcc", repeatLimit = 3
     *  Output: "zzcccac"
     *
     *  Input: s = "aababab", repeatLimit = 2
     *  Output: "bbabaa"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", repeatLimit = %d\n", testCase[i].s, testCase[i].repeatLimit);

        pAnswer = repeatLimitedString(testCase[i].s, testCase[i].repeatLimit);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
