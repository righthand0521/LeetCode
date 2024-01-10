#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
bool asteroidsDestroyed(int mass, int* asteroids, int asteroidsSize) {
    bool retVal = true;

    qsort(asteroids, asteroidsSize, sizeof(int), compareInteger);
    long long sum = mass;  // 1 <= asteroids.length <= 10^5, 1 <= asteroids[i] <= 10^5.
    int i;
    for (i = 0; i < asteroidsSize; ++i) {
        if (sum < asteroids[i]) {
            retVal = false;
            break;
        }
        sum += asteroids[i];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int mass;
        int asteroids[MAX_SIZE];
        int asteroidsSize;
    } testCase[] = {{10, {3, 9, 19, 5, 21}, 5}, {5, {4, 9, 23, 4}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: mass = 10, asteroids = [3,9,19,5,21]
     *  Output: true
     *
     *  Input: mass = 5, asteroids = [4,9,23,4]
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: mass = %d, asteroids = [", testCase[i].mass);
        for (j = 0; j < testCase[i].asteroidsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].asteroids[j]);
        }
        printf("]\n");

        answer = asteroidsDestroyed(testCase[i].mass, testCase[i].asteroids, testCase[i].asteroidsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
