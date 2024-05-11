#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/minimum-cost-to-hire-k-workers/solutions/1817466/by-heshan-5-ygtm/
#ifndef HEAP_H
#define HEAP_H

typedef struct heap {
    int capacity;
    int size;
    int *elements;
} priorityQueue;
priorityQueue *createQueue(int maxsize) {
    priorityQueue *pRetVal = NULL;

    pRetVal = (priorityQueue *)malloc(sizeof(priorityQueue));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->capacity = maxsize + 1;
    pRetVal->size = 0;
    pRetVal->elements = (int *)malloc(maxsize * sizeof(int));
    if (pRetVal->elements == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(pRetVal->elements, 0, (maxsize * sizeof(int)));

    return pRetVal;
}
void pushQuee(int val, priorityQueue *obj) {
    int i;
    for (i = obj->size + 1; ((i > 1) && (val > obj->elements[i / 2])); i /= 2) {
        obj->elements[i] = obj->elements[i / 2];
    }
    obj->elements[i] = val;
    obj->size++;
}
int popQuee(priorityQueue *obj) {
    int retVal = obj->elements[1];

    int last = obj->elements[obj->size];

    obj->size--;
    if (obj->size == 0) {
        obj->elements[1] = 0;
        return retVal;
    }

    int maxChild = 0;
    int i;
    for (i = 1; i * 2 <= obj->size; i = maxChild) {
        maxChild = i * 2;
        if ((maxChild != obj->size) && (obj->elements[maxChild] < obj->elements[maxChild + 1])) {
            maxChild++;
        }
        if (last >= obj->elements[maxChild]) {
            break;
        }
        obj->elements[i] = obj->elements[maxChild];
    }
    obj->elements[i] = last;

    return retVal;
}
void freeQueue(priorityQueue *obj) {
    free(obj->elements);
    obj->elements = NULL;
    free(obj);
    obj = NULL;
}

#endif  // HEAP_H
struct node {
    double weight;
    int quality;
};
int compareStruct(const void *a, const void *b) {
    struct node c = *(struct node *)a;
    struct node d = *(struct node *)b;

    double tmp = c.weight - d.weight;
    if (tmp < -1e-7) {
        return -1;
    } else if (tmp > 1e-7) {
        return 1;
    } else {
        return 0;
    }
}
double mincostToHireWorkers(int *quality, int qualitySize, int *wage, int wageSize, int k) {
    double retVal = DBL_MAX;

    int i;

    //
    int minWage = wage[0];
    if (k == 1) {
        for (i = 0; i < wageSize; ++i) {
            if (wage[i] < minWage) {
                minWage = wage[i];
            }
        }
        retVal = 1.0 * minWage;

        return retVal;
    }

    //
    struct node member[qualitySize];
    for (i = 0; i < qualitySize; ++i) {
        member[i].quality = quality[i];
        member[i].weight = 1.0 * wage[i] / quality[i];
    }
    qsort(member, qualitySize, sizeof(member[0]), compareStruct);

    //
    priorityQueue *pObj = createQueue(qualitySize + 1);
    if (pObj == NULL) {
        return retVal;
    }

    int totalQuality = 0;
    for (i = 0; i < k - 1; i++) {
        totalQuality += member[i].quality;
        pushQuee(member[i].quality, pObj);
    }

    double tmp;
    for (i = k - 1; i < qualitySize; ++i) {
        totalQuality += member[i].quality;
        pushQuee(member[i].quality, pObj);
        tmp = member[i].weight * totalQuality;
        totalQuality -= popQuee(pObj);
        if (tmp - retVal < -1e-7) {
            retVal = tmp;
        }
    }

    //
    freeQueue(pObj);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int quality[MAX_SIZE];
        int qualitySize;
        int wage[MAX_SIZE];
        int wageSize;
        int k;
    } testCase[] = {{{10, 20, 5}, 3, {70, 50, 30}, 3, 2}, {{3, 1, 10, 10, 1}, 5, {4, 8, 2, 2, 7}, 5, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: quality = [10,20,5], wage = [70,50,30], k = 2
     *  Output: 105.00000
     *
     *  Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], k = 3
     *  Output: 30.66667
     */

    int i, j;
    double answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: quality = [");
        for (j = 0; j < testCase[i].qualitySize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].quality[j]);
        }
        printf("], nums2 = [");
        for (j = 0; j < testCase[i].wageSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].wage[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = mincostToHireWorkers(testCase[i].quality, testCase[i].qualitySize, testCase[i].wage,
                                      testCase[i].wageSize, testCase[i].k);
        printf("Output: %.5f\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
