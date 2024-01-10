#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order by Array[][0]
    return ((p1[0] > p2[0]) ? (1) : (-1));
}
bool canAttendMeetings(int** intervals, int intervalsSize, int* intervalsColSize) {
    bool retVal = true;

    qsort(intervals, intervalsSize, sizeof(intervals[0]), compareIntArray);

    int i;
    for (i = 1; i < intervalsSize; ++i) {
        if (intervals[i - 1][1] > intervals[i][0]) {
            retVal = false;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int intervals[MAX_SIZE][2];
        int intervalsSize;
        int intervalsColSize[MAX_SIZE];
    } testCase[] = {{{{0, 30}, {5, 10}, {15, 20}}, 3, {2, 2, 2}}, {{{7, 10}, {2, 4}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pIntervals = NULL;
    bool answer = false;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: intervals = [");
        for (j = 0; j < testCase[i].intervalsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].intervalsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].intervals[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pIntervals = (int**)malloc(testCase[i].intervalsSize * sizeof(int*));
        if (pIntervals == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].intervalsSize; ++j) {
            pIntervals[j] = (int*)malloc(testCase[i].intervalsColSize[j] * sizeof(int));
            if (pIntervals[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pIntervals[k]);
                }
                free(pIntervals);
                return EXIT_FAILURE;
            }
            memset(pIntervals[j], 0, (testCase[i].intervalsColSize[j] * sizeof(int)));
            memcpy(pIntervals[j], testCase[i].intervals[j], (testCase[i].intervalsColSize[j] * sizeof(int)));
        }
        answer = canAttendMeetings(pIntervals, testCase[i].intervalsSize, testCase[i].intervalsColSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        for (j = 0; j < testCase[i].intervalsSize; ++j) {
            free(pIntervals[j]);
        }
        free(pIntervals);
        pIntervals = NULL;
    }

    return EXIT_SUCCESS;
}
