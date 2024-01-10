#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int start;
    int time;
    int idx;
} Task;
typedef struct {
    Task *task;
    int idx;
} Heap;
int cmpTask1(const void *a, const void *b) {
    Task *pA = (Task *)a;
    Task *pB = (Task *)b;

    if (pA->start == pB->start) {
        return (pA->time > pB->time);
    }

    return (pA->start > pB->start);
}
int cmpTask2(Task *a, Task *b) {
    if (a->time == b->time) {
        return (a->idx > b->idx);
    }

    return (a->time > b->time);
}
void swap(Task *a, Task *b) {
    Task tmp = *a;
    *a = *b;
    *b = tmp;
}
void push(Heap *heap, Task *t) {
    heap->task[heap->idx++] = *t;

    int p;
    int x = heap->idx - 1;
    while (x > 0) {
        p = (x - 1) / 2;
        if (cmpTask2(&heap->task[p], &heap->task[x])) {
            swap(&heap->task[p], &heap->task[x]);
            x = p;
        } else {
            break;
        }
    }
}
Task pop(Heap *heap) {
    Task res = heap->task[0];
    heap->task[0] = heap->task[--heap->idx];

    int min, l, r;
    int i = 0;
    int n = heap->idx;
    while (i < n) {
        min = i;

        l = 2 * min + 1;
        r = 2 * min + 2;
        if (l < n && cmpTask2(&heap->task[min], &heap->task[l])) {
            min = l;
        }

        if (r < n && cmpTask2(&heap->task[min], &heap->task[r])) {
            min = r;
        }

        if (min != i) {
            swap(&heap->task[min], &heap->task[i]);
            i = min;
        } else {
            break;
        }
    }

    return res;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getOrder(int **tasks, int tasksSize, int *tasksColSize, int *returnSize) {
    int *pRetVal = NULL;

    // malloc returned array
    (*returnSize) = tasksSize;
    pRetVal = (int *)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    // malloc Heap
    Heap *pHeap = (Heap *)malloc(sizeof(Heap));
    if (pHeap == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    pHeap->task = (Task *)malloc((*returnSize) * sizeof(Task));
    if (pHeap->task == NULL) {
        perror("malloc");
        free(pHeap);
        pHeap = NULL;
        (*returnSize) = 0;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    pHeap->idx = 0;

    // malloc Task
    Task *pTask = (Task *)malloc((*returnSize) * sizeof(Task));
    if (pTask == NULL) {
        perror("malloc");
        free(pHeap->task);
        pHeap->task = NULL;
        free(pHeap);
        pHeap = NULL;
        (*returnSize) = 0;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    int i, j;

    for (i = 0; i < (*returnSize); i++) {
        Task pTmp = {tasks[i][0], tasks[i][1], i};
        pTask[i] = pTmp;
    }
    qsort(pTask, (*returnSize), sizeof(pTask[0]), cmpTask1);

    long cur = 0;
    j = 0;
    for (i = 0; i < (*returnSize); i++) {
        if (pHeap->idx == 0) {
            cur = fmax(cur, pTask[i].start);
        }

        while (j < (*returnSize) && pTask[j].start <= cur) {
            push(pHeap, &pTask[j]);
            j++;
        }

        Task pTmp = pop(pHeap);
        pRetVal[i] = pTmp.idx;
        cur += pTmp.time;
    }

    free(pHeap->task);
    pHeap->task = NULL;
    free(pHeap);
    pHeap = NULL;
    free(pTask);
    pTask = NULL;

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int tasks[MAX_SIZE][2];
        int tasksSize;
        int tasksColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{{{1, 2}, {2, 4}, {3, 2}, {4, 1}}, 4, {2, 2, 2, 2}, 0},
                    {{{7, 10}, {7, 12}, {7, 5}, {7, 4}, {7, 2}}, 5, {2, 2, 2, 2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int **pTasks = NULL;
    int *pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: tasks = [");
        for (j = 0; j < testCase[i].tasksSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].tasksColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].tasks[j][k]);
            }
            printf("]");
        }
        printf("\n");

        pTasks = (int **)malloc(testCase[i].tasksSize * sizeof(int *));
        if (pTasks == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].tasksSize; ++j) {
            pTasks[j] = (int *)malloc(testCase[i].tasksColSize[j] * sizeof(int));
            if (pTasks[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pTasks[k]);
                    pTasks[k] = NULL;
                }
                free(pTasks);
                pTasks = NULL;
                return EXIT_FAILURE;
            }
            memset(pTasks[j], 0, testCase[i].tasksColSize[j] * sizeof(int));
        }
        for (j = 0; j < testCase[i].tasksSize; ++j) {
            for (k = 0; k < testCase[i].tasksColSize[j]; ++k) {
                pTasks[j][k] = testCase[i].tasks[j][k];
            }
        }
        pAnswer = getOrder(pTasks, testCase[i].tasksSize, testCase[i].tasksColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].tasksSize; ++j) {
            free(pTasks[j]);
        }
        free(pTasks);
        pTasks = NULL;
    }

    return EXIT_SUCCESS;
}
