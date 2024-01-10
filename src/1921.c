#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareDouble(const void* n1, const void* n2) {
    // ascending order
    return (*(double*)n1 > *(double*)n2);
}
int eliminateMaximum(int* dist, int distSize, int* speed, int speedSize) {
    int retVal = 0;

    double arrival[distSize];
    memset(arrival, 0, sizeof(arrival));

    int i;
    for (i = 0; i < distSize; ++i) {
        arrival[i] = (double)dist[i] / speed[i];
    }

    qsort(arrival, distSize, sizeof(double), compareDouble);

    for (i = 0; i < distSize; ++i) {
        if (arrival[i] <= i) {
            break;
        }
        retVal += 1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int dist[MAX_SIZE];
        int distSize;
        int speed[MAX_SIZE];
        int speedSize;
    } testCase[] = {{{1, 3, 4}, 3, {1, 1, 1}, 3},
                    {{1, 1, 2, 3}, 4, {1, 1, 1, 1}, 4},
                    {{3, 2, 4}, 3, {5, 3, 2}, 3},
                    {{4, 2, 3}, 3, {2, 1, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: dist = [1,3,4], speed = [1,1,1]
     *  Output: 3
     *
     *  Input: dist = [1,1,2,3], speed = [1,1,1,1]
     *  Output: 1
     *
     *  Input: dist = [3,2,4], speed = [5,3,2]
     *  Output: 1
     *
     *  Input: dist = [4,2,3], speed = [2,1,1]
     *  Output: 3
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: dist = [");
        for (j = 0; j < testCase[i].distSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].dist[j]);
        }
        printf("], speed = [");
        for (j = 0; j < testCase[i].speedSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].speed[j]);
        }
        printf("]\n");

        answer = eliminateMaximum(testCase[i].dist, testCase[i].distSize, testCase[i].speed, testCase[i].speedSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
