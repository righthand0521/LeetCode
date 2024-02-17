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
