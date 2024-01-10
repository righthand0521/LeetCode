#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HEAP_H
#define HEAP_H  // Implementation of a priority queue using a min-heap.

//
#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)
#define PARENT(i) (i > 0 ? (((i)-1) / 2) : 0)

//
typedef struct {
    int *arr;
    int capacity;  // number of memory allocated for elements
    int size;      // number of elements
} Min_heap;

//
void heapify(Min_heap *heap, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int min_i = i;

    if ((l < heap->size) && (heap->arr[l] < heap->arr[min_i])) {
        min_i = l;
    }
    if ((r < heap->size) && (heap->arr[r] < heap->arr[min_i])) {
        min_i = r;
    }

    if (min_i != i) {
        int temp = heap->arr[min_i];
        heap->arr[min_i] = heap->arr[i];
        heap->arr[i] = temp;

        heapify(heap, min_i);
    }
}
void build_heap(Min_heap *heap) {
    for (int i = PARENT(heap->size - 1); i >= 0; --i) {
        heapify(heap, i);
    }
}
int insert(Min_heap *heap, int elem) {
    if (heap->size == heap->capacity) {
        return 1;
    }

    heap->arr[heap->size] = elem;
    heap->size++;

    int i = heap->size - 1;

    while (i > 0) {
        i = PARENT(i);
        heapify(heap, i);
    }

    return 0;
}
int extract_min(Min_heap *heap, int *result) {
    if (heap->size == 0) {
        return 1;
    }

    *result = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return 0;
}
int min_heap_init(Min_heap *heap, int capacity, int *inits, int n) {
    heap->arr = malloc(capacity * sizeof(int));

    if (heap->arr == NULL) {
        return 1;
    }

    heap->size = 0;
    heap->capacity = capacity;

    if (n > 0) {
        int i = 0;
        for (; i < n && i < capacity; ++i) {
            heap->arr[i] = inits[i];
        }
        heap->size = i;

        build_heap(heap);
    }

    return 0;
}
int min_heap_destroy(Min_heap *heap) {
    if (heap->arr == NULL) {
        return 1;
    }

    free(heap->arr);

    return 0;
}
long long min_heap_sum(Min_heap *heap) {
    long long result = 0;

    if (heap == NULL) {
        return result;
    }

    for (int i = 0; i < heap->size; ++i) {
        result += (long long)heap->arr[i];
    }

    return result;
}

#endif  // HEAP_H
typedef struct {
    int first;
    int second;
} pair;
int compareStruct(const void *lhs, const void *rhs) {
    const pair *lhs_pair = (const pair *)lhs;
    const pair *rhs_pair = (const pair *)rhs;

    if (lhs_pair->second < rhs_pair->second) {
        return 1;
    } else if (lhs_pair->second > rhs_pair->second) {
        return -1;
    } else {
        return 0;
    }
}
long long maxScore(int *nums1, int nums1Size, int *nums2, int nums2Size, int k) {
    long long retVal = 0;

    //
    pair *pairs = malloc(nums1Size * sizeof(pair));
    if (pairs == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < nums1Size; ++i) {
        pairs[i].first = nums1[i];
        pairs[i].second = nums2[i];
    }
    qsort(pairs, nums1Size, sizeof(pair), compareStruct);

    //
    int *topKNums1 = malloc(k * sizeof(pair));
    if (topKNums1 == NULL) {
        perror("malloc");
        free(pairs);
        pairs = NULL;
        return retVal;
    }
    for (int i = 0; i < k; ++i) {
        topKNums1[i] = pairs[i].first;
    }
    Min_heap topKNums1Heap;
    min_heap_init(&topKNums1Heap, k, topKNums1, k);

    //
    long long sumOfTopKNums1 = min_heap_sum(&topKNums1Heap);
    retVal = pairs[k - 1].second * sumOfTopKNums1;
    for (int i = k; i < nums1Size; ++i) {
        int popValue = 0;
        extract_min(&topKNums1Heap, &popValue);
        sumOfTopKNums1 -= popValue;
        sumOfTopKNums1 += pairs[i].first;
        insert(&topKNums1Heap, pairs[i].first);

        retVal = fmax(retVal, sumOfTopKNums1 * pairs[i].second);
    }

    //
    free(pairs);
    free(topKNums1);
    min_heap_destroy(&topKNums1Heap);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
        int k;
    } testCase[] = {{{1, 3, 3, 2}, 4, {2, 1, 3, 4}, 4, 3}, {{4, 2, 3, 1, 1}, 5, {7, 5, 10, 9, 6}, 5, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [1,3,3,2], nums2 = [2,1,3,4], k = 3
     *  Output: 12
     *
     *  Input: nums1 = [4,2,3,1,1], nums2 = [7,5,10,9,6], k = 1
     *  Output: 30
     */

    int i, j;
    long long answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums1 = [");
        for (j = 0; j < testCase[i].nums1Size; ++j) {
            printf("%d%s", testCase[i].nums1[j], (j == testCase[i].nums1Size - 1) ? "" : ",");
        }
        printf("], nums2 = [");
        for (j = 0; j < testCase[i].nums2Size; ++j) {
            printf("%d%s", testCase[i].nums2[j], (j == testCase[i].nums2Size - 1) ? "" : ",");
        }
        printf("], k = %d\n", testCase[i].k);

        answer =
            maxScore(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
