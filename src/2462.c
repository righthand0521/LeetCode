#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/total-cost-to-hire-k-workers/solutions/1954280/gu-yong-k-wei-gong-ren-de-zong-dai-jie-b-jj2g/
#define INVALID_INDEX (-1)
#define FATHER_NODE(x) ((0 == (x)) ? (INVALID_INDEX) : (((x)-1) >> 1))
#define LEFT_NODE(x) (((x) << 1) + 1)
#define RIGHT_NODE(x) (((x) << 1) + 2)
typedef struct {
    int *buffer;
    int bufferSize;
} HeapNode;
void heapPush(HeapNode *heap, int value) {
    int son = heap->bufferSize;
    int father = FATHER_NODE(son);

    heap->bufferSize++;
    while ((INVALID_INDEX != father) && (heap->buffer[father] > value)) {
        heap->buffer[son] = heap->buffer[father];
        son = father;
        father = FATHER_NODE(son);
    }
    heap->buffer[son] = value;
}
void heapPop(HeapNode *heap) {
    int father = 0;
    int left = LEFT_NODE(father);
    int right = RIGHT_NODE(father);
    int son = 0;
    int value = 0;

    heap->bufferSize--;
    value = heap->buffer[heap->bufferSize];
    while (((heap->bufferSize > left) && (heap->buffer[left] < value)) ||
           ((heap->bufferSize > right) && (heap->buffer[right] < value))) {
        son = ((heap->bufferSize > right) && (heap->buffer[right] < heap->buffer[left])) ? (right) : (left);
        heap->buffer[father] = heap->buffer[son];
        father = son;
        left = LEFT_NODE(father);
        right = RIGHT_NODE(father);
    }
    heap->buffer[father] = value;
}
long long totalCost(int *costs, int costsSize, int k, int candidates) {
    long long retVal = 0;

    int mostHeapSize = fmin(candidates << 1, costsSize);
    int buffer[mostHeapSize];
    memset(buffer, 0, sizeof(buffer));
    int x = 0;
    int value = 0;
    int leftCounter = 0;
    int rightCounter = 0;
    HeapNode heap;
    heap.bufferSize = 0;
    heap.buffer = buffer;
    x = fmin(candidates, costsSize);
    while (x > leftCounter) {
        value = costs[leftCounter] << 1;
        heapPush(&heap, value);
        leftCounter++;
    }
    x = fmin(candidates, costsSize - leftCounter);
    while (x > rightCounter) {
        value = (costs[costsSize - 1 - rightCounter] << 1) + 1;
        heapPush(&heap, value);
        rightCounter++;
    }

    x = 0;
    while ((k > x) && (0 < heap.bufferSize)) {
        value = heap.buffer[0];
        heapPop(&heap);
        retVal += (value >> 1);

        if (costsSize > leftCounter + rightCounter) {
            if (value & 1) {
                value = (costs[costsSize - 1 - rightCounter] << 1) + 1;
                heapPush(&heap, value);
                rightCounter++;
            } else {
                value = costs[leftCounter] << 1;
                heapPush(&heap, value);
                leftCounter++;
            }
        }

        x++;
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int costs[MAX_SIZE];
        int costsSize;
        int k;
        int candidates;
    } testCase[] = {{{17, 12, 10, 2, 7, 2, 11, 20, 8}, 9, 3, 4}, {{1, 2, 4, 1}, 4, 3, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: costs = [17,12,10,2,7,2,11,20,8], k = 3, candidates = 4
     *  Output: 11
     *
     *  Input: costs = [1,2,4,1], k = 3, candidates = 3
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: costs = [");
        for (j = 0; j < testCase[i].costsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].costs[j]);
        }
        printf("], k = %d, candidates = %d\n", testCase[i].k, testCase[i].candidates);

        answer = totalCost(testCase[i].costs, testCase[i].costsSize, testCase[i].k, testCase[i].candidates);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
