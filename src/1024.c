#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int videoStitching(int** clips, int clipsSize, int* clipsColSize, int time) {
    int retVal = -1;

    int record[time];
    memset(record, 0, sizeof(record));

    int start, end;
    int i;
    for (i = 0; i < clipsSize; ++i) {
        start = clips[i][0];
        end = clips[i][1];
        if (start < time) {
            record[start] = fmax(record[start], end);
        }
    }

    retVal = 0;
    int lastEnd = 0;
    int previousEnd = 0;
    for (i = 0; i < time; ++i) {
        lastEnd = fmax(lastEnd, record[i]);
        if (i == lastEnd) {
            retVal = -1;
            break;
        } else if (i == previousEnd) {
            retVal += 1;
            previousEnd = lastEnd;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int clips[MAX_SIZE][2];
        int clipsSize;
        int clipsColSize[MAX_SIZE];
        int time;
    } testCase[] = {{{{0, 2}, {4, 6}, {8, 10}, {1, 9}, {1, 5}, {5, 9}}, 6, {2, 2, 2, 2, 2, 2}, 10},
                    {{{0, 1}, {1, 2}}, 2, {2, 2}, 5},
                    {{{0, 1},
                      {6, 8},
                      {0, 2},
                      {5, 6},
                      {0, 4},
                      {0, 3},
                      {6, 7},
                      {1, 3},
                      {4, 7},
                      {1, 4},
                      {2, 5},
                      {2, 6},
                      {3, 4},
                      {4, 5},
                      {5, 7},
                      {6, 9}},
                     16,
                     {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                     9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
     *  Output: 3
     *
     *  Input: clips = [[0,1],[1,2]], time = 5
     *  Output: -1
     *
     *  Input: clips =
     *  [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], time = 9
     *  Output: 3
     */

    int** pClips = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("clips = [");
        for (j = 0; j < testCase[i].clipsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].clipsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].clips[j][k]);
            }
            printf("]");
        }
        printf("], time = %d\n", testCase[i].time);

        pClips = (int**)malloc(testCase[i].clipsSize * sizeof(int*));
        if (pClips == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pClips, 0, testCase[i].clipsSize * sizeof(int*));
        for (j = 0; j < testCase[i].clipsSize; ++j) {
            pClips[j] = (int*)malloc(testCase[i].clipsColSize[j] * sizeof(int));
            if (pClips[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pClips[k]);
                    pClips[k] = NULL;
                }
                free(pClips);
                pClips = NULL;
            }
            memset(pClips[j], 0, (testCase[i].clipsColSize[j] * sizeof(int)));
            memcpy(pClips[j], testCase[i].clips[j], (testCase[i].clipsColSize[j] * sizeof(int)));
        }
        answer = videoStitching(pClips, testCase[i].clipsSize, testCase[i].clipsColSize, testCase[i].time);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].clipsSize; ++j) {
            free(pClips[j]);
            pClips[j] = NULL;
        }
        free(pClips);
        pClips = NULL;
    }

    return EXIT_SUCCESS;
}
