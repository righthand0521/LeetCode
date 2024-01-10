#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minCost(char* colors, int* neededTime, int neededTimeSize) {
    int retVal = 0;

    int colorsSize = strlen(colors);

    int maxNeededTime, cost;
    char previous;
    int i = 0;
    while (i < colorsSize) {
        previous = colors[i];
        maxNeededTime = 0;
        cost = 0;
        while ((i < colorsSize) && (colors[i] == previous)) {
            maxNeededTime = fmax(maxNeededTime, neededTime[i]);
            cost += neededTime[i];
            ++i;
        }
        retVal += (cost - maxNeededTime);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char colors[MAX_SIZE];
        int neededTime[MAX_SIZE];
        int neededTimeSize;
    } testCase[] = {{"abaac", {1, 2, 3, 4, 5}, 5}, {"abc", {1, 2, 3}, 3}, {"aabaa", {1, 2, 3, 4, 1}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: colors = "abaac", neededTime = [1,2,3,4,5]
     *  Output: 3
     *
     *  Input: colors = "abc", neededTime = [1,2,3]
     *  Output: 0
     *
     *  Input: colors = "aabaa", neededTime = [1,2,3,4,1]
     *  Output: 2
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: colors = \"%s\"", testCase[i].colors);
        printf(", neededTime = [");
        for (j = 0; j < testCase[i].neededTimeSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].neededTime[j]);
        }
        printf("]\n");

        answer = minCost(testCase[i].colors, testCase[i].neededTime, testCase[i].neededTimeSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
