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
MinHeap* createMinHeap(int capacity) {
    MinHeap* pObj = NULL;

    pObj = (MinHeap*)malloc(sizeof(MinHeap));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }

    pObj->data = (int*)malloc(capacity * sizeof(int));
    if (pObj->data == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->size = 0;
    pObj->capacity = capacity;

    return pObj;
}
void heapifyMinHeap(MinHeap* pObj, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Function to heapify the heap starting from the given index
    if ((left < pObj->size) && (pObj->data[left] < pObj->data[smallest])) {
        smallest = left;
    }

    if ((right < pObj->size) && (pObj->data[right] < pObj->data[smallest])) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&pObj->data[index], &pObj->data[smallest]);
        heapifyMinHeap(pObj, smallest);
    }
}
void pushMinHeap(MinHeap* pObj, int value) {
    if (pObj->size == pObj->capacity) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    int index = pObj->size++;
    pObj->data[index] = value;

    // Fix the min heap property by comparing the value with its parent
    while ((index != 0) && (pObj->data[(index - 1) / 2] > pObj->data[index])) {
        swap(&pObj->data[(index - 1) / 2], &pObj->data[index]);
        index = (index - 1) / 2;
    }
}
int popMinHeap(MinHeap* pObj) {
    int retVal = -1;

    if (pObj->size == 0) {
        printf("Heap is empty. Cannot remove elements.\n");
        return retVal;
    }

    retVal = pObj->data[0];
    pObj->data[0] = pObj->data[minHeap->size - 1];
    pObj->size--;
    heapifyMinHeap(pObj, 0);

    return retVal;
}
void printMinHeap(MinHeap* pObj) {
    printf("Min Heap: ");
    for (int i = 0; i < pObj->size; i++) {
        printf("%d ", pObj->data[i]);
    }
    printf("\n");
}
void freeMinHeap(MinHeap* pObj) {
    free(pObj->data);
    pObj->data = NULL;
    free(pObj);
    pObj = NULL;
}

//
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
    if (pObj->data == NULL) {
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
