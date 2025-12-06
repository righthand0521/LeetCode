#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
#ifndef DEQUE_H
#define DEQUE_H

typedef struct {
    int* data;
    int front;
    int rear;
    int capacity;
} Deque;
Deque* createDeque(int capacity) {
    Deque* pRetVal = NULL;

    pRetVal = (Deque*)malloc(sizeof(Deque));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->data = (int*)malloc(capacity * sizeof(int));
    if (pRetVal->data == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    pRetVal->front = 0;
    pRetVal->rear = -1;
    pRetVal->capacity = capacity;

    return pRetVal;
}
bool isEmpty(Deque* dq) {
    bool retVal = false;

    if (dq->rear < dq->front) {
        retVal = true;
    }

    return retVal;
}
void pushBack(Deque* dq, int value) {
    if (dq->rear < dq->capacity - 1) {
        dq->data[++dq->rear] = value;
    }
}
void popBack(Deque* dq) {
    if (isEmpty(dq) == false) {
        dq->rear--;
    }
}
void popFront(Deque* dq) {
    if (isEmpty(dq) == false) {
        dq->front++;
    }
}
int front(Deque* dq) {
    int retVal = -1;

    if (isEmpty(dq) == false) {
        retVal = dq->data[dq->front];
    }

    return retVal;
}
int back(Deque* dq) {
    int retVal = -1;

    if (isEmpty(dq) == false) {
        retVal = dq->data[dq->rear];
    }

    return retVal;
}

#endif  // DEQUE_H
int countPartitions(int* nums, int numsSize, int k) {
    int retVal = 0;

    long long dp[numsSize + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    long long prefix[numsSize + 1];
    memset(prefix, 0, sizeof(prefix));
    prefix[0] = 1;
    Deque* minQueue = createDeque(numsSize);
    Deque* maxQueue = createDeque(numsSize);

    int j = 0;
    for (int i = 0; i < numsSize; i++) {
        // maintain the maximum value queue
        while ((isEmpty(maxQueue) == false) && (nums[back(maxQueue)] <= nums[i])) {
            popBack(maxQueue);
        }
        pushBack(maxQueue, i);

        // maintain the minimum value queue
        while ((isEmpty(minQueue) == false) && (nums[back(minQueue)] >= nums[i])) {
            popBack(minQueue);
        }
        pushBack(minQueue, i);

        // adjust window
        while ((isEmpty(maxQueue) == false) && (isEmpty(minQueue) == false) &&
               (nums[front(maxQueue)] - nums[front(minQueue)] > k)) {
            if (front(maxQueue) == j) {
                popFront(maxQueue);
            }
            if (front(minQueue) == j) {
                popFront(minQueue);
            }
            j++;
        }

        if (j > 0) {
            dp[i + 1] = (prefix[i] - prefix[j - 1] + MODULO) % MODULO;
        } else {
            dp[i + 1] = prefix[i] % MODULO;
        }
        prefix[i + 1] = (prefix[i] + dp[i + 1]) % MODULO;
    }
    retVal = (int)dp[numsSize];

    //
    free(minQueue->data);
    free(minQueue);
    free(maxQueue->data);
    free(maxQueue);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{9, 4, 1, 3, 7}, 5, 4}, {{3, 3, 4}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [9,4,1,3,7], k = 4
     *  Output: 6
     *
     *  Input: nums = [3,3,4], k = 0
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = countPartitions(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
