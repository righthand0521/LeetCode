#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int maxSatisfaction(int* satisfaction, int satisfactionSize) {
    int retVal = 0;

    qsort(satisfaction, satisfactionSize, sizeof(int), compareInteger);

    int sum = 0;
    int i;
    for (i = 0; i < satisfactionSize; ++i) {
        sum += satisfaction[i];
        if (sum < 0) {
            break;
        }
        retVal += sum;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int satisfaction[MAX_SIZE];
        int satisfactionSize;
    } testCase[] = {{{-1, -8, 0, 5, -9}, 5}, {{4, 3, 2}, 3}, {{-1, -4, -5}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: satisfaction = [-1,-8,0,5,-9]
     *  Output: 14
     *
     *  Input: satisfaction = [4,3,2]
     *  Output: 20
     *
     *  Input: satisfaction = [-1,-4,-5]
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: satisfaction = [");
        for (j = 0; j < testCase[i].satisfactionSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].satisfaction[j]);
        }
        printf("]\n");

        answer = maxSatisfaction(testCase[i].satisfaction, testCase[i].satisfactionSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
