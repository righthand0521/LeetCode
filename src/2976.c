#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// source, target consist of lowercase English letters. original[i], changed[i] are lowercase English letters.
#define MAX_LETTERS (26)
long long minimumCost(char* source, char* target, char* original, int originalSize, char* changed, int changedSize,
                      int* cost, int costSize) {
    long long retVal = 0;

    int i, j, k;

    long long distance[MAX_LETTERS][MAX_LETTERS];
    for (i = 0; i < MAX_LETTERS; i++) {
        for (j = 0; j < MAX_LETTERS; j++) {
            distance[i][j] = INT_MAX;
        }
        distance[i][i] = 0;
    }
    int originalIdx, changedIdx;
    for (i = 0; i < originalSize; i++) {
        originalIdx = original[i] - 'a';
        changedIdx = changed[i] - 'a';
        distance[originalIdx][changedIdx] = fmin(cost[i], distance[originalIdx][changedIdx]);
    }
    for (k = 0; k < MAX_LETTERS; k++) {
        for (i = 0; i < MAX_LETTERS; i++) {
            for (j = 0; j < MAX_LETTERS; j++) {
                distance[i][j] = fmin(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }

    int sourceIdx, targetIdx;
    int sourceSize = strlen(source);
    for (i = 0; i < sourceSize; i++) {
        if (source[i] == target[i]) {
            continue;
        }

        sourceIdx = source[i] - 'a';
        targetIdx = target[i] - 'a';
        if (distance[sourceIdx][targetIdx] >= INT_MAX) {
            retVal = -1;  // If it is impossible to convert source to target, return -1.
            return retVal;
        }
        retVal += (distance[sourceIdx][targetIdx]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        char* source;
        char* target;
        char original[MAX_SIZE];
        int originalSize;
        char changed[MAX_SIZE];
        int changedSize;
        int cost[MAX_SIZE];
        int costSize;
    } testCase[] = {
        {"abcd", "acbe", {'a', 'b', 'c', 'c', 'e', 'd'}, 6, {'b', 'c', 'b', 'e', 'b', 'e'}, 6, {2, 5, 5, 1, 2, 20}, 6},
        {"aaaa", "bbbb", {'a', 'c'}, 2, {'c', 'b'}, 2, {1, 2}, 2},
        {"abcd", "abce", {'a'}, 1, {'e'}, 1, {10000}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: source = "abcd", target = "acbe",
     *  original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
     *  Output: 28
     *
     *  Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
     *  Output: 12
     *
     *  Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
     *  Output: -1
     */

    int i, j;
    long long answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: source = \"%s\", target = \"%s\", original = [", testCase[i].source, testCase[i].target);
        for (j = 0; j < testCase[i].originalSize; ++j) {
            printf("%s\"%c\"", (j == 0) ? "" : ",", testCase[i].original[j]);
        }
        printf("], changed = [");
        for (j = 0; j < testCase[i].originalSize; ++j) {
            printf("%s\"%c\"", (j == 0) ? "" : ",", testCase[i].changed[j]);
        }
        printf("], cost = [");
        for (j = 0; j < testCase[i].costSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].cost[j]);
        }
        printf("]\n");

        answer = minimumCost(testCase[i].source, testCase[i].target, testCase[i].original, testCase[i].originalSize,
                             testCase[i].changed, testCase[i].changedSize, testCase[i].cost, testCase[i].costSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
