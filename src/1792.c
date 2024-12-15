#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/maximum-average-pass-ratio/solutions/1413598/by-goodgoodday-sl2o/
#ifndef HEAP_H
#define HEAP_H

//
void swapDouble(double* pLeft, double* pRight) {
    double temp = *pLeft;
    *pLeft = *pRight;
    *pRight = temp;
}
void swapInt(int* pLeft, int* pRight) {
    int temp = *pLeft;
    *pLeft = *pRight;
    *pRight = temp;
}
//
typedef struct {
    double* gain;
    int* classes;
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

    pObj->gain = (double*)malloc(sizeof(double) * capacity);
    if (pObj->gain == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->classes = (int*)malloc(sizeof(int) * capacity);
    if (pObj->classes == NULL) {
        perror("malloc");
        free(pObj->gain);
        pObj->gain = NULL;
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->size = 1;
    pObj->capacity = capacity;

    return pObj;
}
void HeapAdjustDown(MaxHeap* pObj, int parent) {
    int child = 2 * parent;
    int size = pObj->size;
    while (child < size) {
        if ((child + 1 < size) && (pObj->gain[child] < pObj->gain[child + 1])) {
            child = child + 1;
        }

        if (pObj->gain[child] > pObj->gain[parent]) {
            swapDouble(&pObj->gain[child], &pObj->gain[parent]);
            swapInt(&pObj->classes[child], &pObj->classes[parent]);
            parent = child;
            child = parent << 1;
        } else {
            break;
        }
    }
}
void HeapAdjustUp(MaxHeap* pObj, int child) {
    int parent = child / 2;
    while (child > 1) {
        if (pObj->gain[child] > pObj->gain[parent]) {
            swapDouble(&pObj->gain[child], &pObj->gain[parent]);
            swapInt(&pObj->classes[child], &pObj->classes[parent]);
            child = parent;
            parent = child / 2;
        } else {
            break;
        }
    }
}
void pushMaxHeap(MaxHeap* pObj, double gain, int classes) {
    if (pObj->size == pObj->capacity) {
        printf("MaxHeap is full. Cannot insert more elements.\n");
        return;
    }

    int index = pObj->size++;
    pObj->gain[index] = gain;
    pObj->classes[index] = classes;

    HeapAdjustUp(pObj, pObj->size - 1);
}
void popMaxHeap(MaxHeap* pObj) {
    if (pObj->size == 1) {
        printf("MaxHeap is empty. Cannot remove elements.\n");
        return;
    }

    pObj->gain[1] = pObj->gain[pObj->size - 1];
    pObj->classes[1] = pObj->classes[pObj->size - 1];
    pObj->size--;

    HeapAdjustDown(pObj, 1);
}
void printMaxHeap(MaxHeap* pObj) {
    printf("Max Heap: ");
    for (int i = 1; i < pObj->size; i++) {
        printf("(%f,%d) ", pObj->gain[i], pObj->classes[i]);
    }
    printf("\n");
}
void freeMaxHeap(MaxHeap* pObj) {
    free(pObj->gain);
    pObj->gain = NULL;
    free(pObj->classes);
    pObj->classes = NULL;
    free(pObj);
    pObj = NULL;
}

#endif  // HEAP_H
double calculateGain(int passes, int totalStudents) {
    double retVal = 0;

    retVal = (double)(passes + 1) / (totalStudents + 1) - (double)passes / totalStudents;

    return retVal;
};
double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    double retVal = 0;

    // Max heap to store (-gain, passes, totalStudents)
    MaxHeap* pMaxHeap = createMaxHeap(classesSize + 1);
    if (pMaxHeap == NULL) {
        return retVal;
    }
    double gain = 0;
    for (int i = 0; i < classesSize; i++) {
        gain = calculateGain(classes[i][0], classes[i][1]);
        pushMaxHeap(pMaxHeap, gain, i);
    }
    // printMaxHeap(pMaxHeap);

    // Distribute extra students
    int topIndex;
    while (extraStudents--) {
        topIndex = pMaxHeap->classes[1];
        popMaxHeap(pMaxHeap);

        classes[topIndex][0]++;
        classes[topIndex][1]++;
        gain = calculateGain(classes[topIndex][0], classes[topIndex][1]);
        pushMaxHeap(pMaxHeap, gain, topIndex);
    }
    // printMaxHeap(pMaxHeap);

    // Calculate the final average pass ratio
    double totalPassRatio = 0;
    for (int i = 0; i < classesSize; i++) {
        totalPassRatio += ((double)classes[i][0] / classes[i][1]);
    }
    retVal = totalPassRatio / classesSize;

    //
    freeMaxHeap(pMaxHeap);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int classes[MAX_SIZE][2];
        int classesSize;
        int classesColSize[MAX_SIZE];
        int extraStudents;
    } testCase[] = {{{{1, 2}, {3, 5}, {2, 2}}, 3, {2, 2, 2}, 2},
                    {{{2, 4}, {3, 9}, {4, 5}, {2, 10}}, 4, {2, 2, 2, 2}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
     *  Output: 0.78333
     *
     *  Input: classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
     *  Output: 0.53485
     */

    int** pClasses = NULL;
    double answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("classes = [");
        for (j = 0; j < testCase[i].classesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].classesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].classes[j][k]);
            }
            printf("]");
        }
        printf("], extraStudents = %d\n", testCase[i].extraStudents);

        pClasses = (int**)malloc(testCase[i].classesSize * sizeof(int*));
        if (pClasses == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        memset(pClasses, 0, testCase[i].classesSize * sizeof(int*));
        for (j = 0; j < testCase[i].classesSize; ++j) {
            pClasses[j] = (int*)malloc(testCase[i].classesColSize[j] * sizeof(int));
            if (pClasses[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pClasses[k]);
                    pClasses[k] = NULL;
                }
                free(pClasses);
                pClasses = NULL;
            }
            memset(pClasses[j], 0, (testCase[i].classesColSize[j] * sizeof(int)));
            memcpy(pClasses[j], testCase[i].classes[j], (testCase[i].classesColSize[j] * sizeof(int)));
        }
        answer =
            maxAverageRatio(pClasses, testCase[i].classesSize, testCase[i].classesColSize, testCase[i].extraStudents);
        printf("Output: %.5f\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].classesSize; ++j) {
            free(pClasses[j]);
            pClasses[j] = NULL;
        }
        free(pClasses);
        pClasses = NULL;
    }

    return EXIT_SUCCESS;
}
