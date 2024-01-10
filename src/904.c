#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int totalFruit(int* fruits, int fruitsSize) {
    int retVal = 0;

    // 1 <= fruits.length <= 10^5, 0 <= fruits[i] < fruits.length.
#define MAX_HASHTABLE ((int)(1e5))
    int HashTable[MAX_HASHTABLE];
    memset(HashTable, 0, sizeof(HashTable));
    unsigned int countHashTable = 0;
    int head = 0;
    int tail = 0;
    /* Example
     *          +--------------------------------------------+-----------------------------+
     *          | 3 | 3 | 3 | 1 | 2 | 1 | 1 | 2 | 3 | 3 | 4  |                             |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  | 0 > 1 > 2 > 3 > 4                          | size: 1 > 1 > 1 > 2 > 3 |   |
     *    head  | 0                                          |  max: 1 > 2 > 3 > 4     | 4 |
     *          +--------------------------------------------+-------------------------+---|
     *    tail  |                 4                          | size: 3 > 3 > 3 > 2     |   |
     *    head  | 0 > 1 > 2 > 3                              |  max: 4 > 2             | 4 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                 4 > 5 > 6 > 7 > 8          | size: 2 > 2 > 2 > 2 > 3 |   |
     *    head  |             3                              |  max: 2 > 3 > 4 > 5     | 5 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                                 8          | size: 3 > 3 > 3 > 3 > 2 |   |
     *    head  |             3 > 4 > 5 > 6 > 7              |  max: 5 > 2             | 5 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                                 8 > 9 > 10 | size: 2 > 2 > 3         |   |
     *    head  |                             7              |  max: 2 > 3             | 5 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                                         10 | size: 3 > 2             |   |
     *    head  |                             7 > 8          |  max: 3 > 3             | 5 |
     *          +--------------------------------------------+-------------------------+---+
     */
    while (tail < fruitsSize) {
        if (HashTable[fruits[tail]] == 0) {
            ++countHashTable;
        }
        ++HashTable[fruits[tail]];

        while (countHashTable > 2) {
            --HashTable[fruits[head]];
            if (HashTable[fruits[head]] == 0) {
                --countHashTable;
            }
            ++head;
        }
        retVal = fmax(retVal, tail - head + 1);

        ++tail;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int fruits[MAX_SIZE];
        int fruitsSize;
    } testCase[] = {{{1, 2, 1}, 3}, {{0, 1, 2, 2}, 4}, {{1, 2, 3, 2, 2}, 5}, {{3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4}, 11}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: fruits  = [");
        for (j = 0; j < testCase[i].fruitsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].fruits[j]);
        }
        printf("]\n");

        answer = totalFruit(testCase[i].fruits, testCase[i].fruitsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
