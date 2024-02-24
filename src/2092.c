#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    return (p1[2] > p2[2]);
}
void GetResult(int** meetings, int start, int num, int* returnValue, int* returnSize, int* flag) {
    int people;
    int i;
    int rule = 1;
    while (rule > 0) {
        rule = 0;
        for (i = 0; i < num; i++) {
            if (flag[meetings[i + start][0]] != flag[meetings[i + start][1]]) {
                people = flag[meetings[i + start][0]] ? meetings[i + start][1] : meetings[i + start][0];
                returnValue[(*returnSize)++] = people;
                flag[people] = 1;
                rule = 1;
            }
        }
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAllPeople(int n, int** meetings, int meetingsSize, int* meetingsColSize, int firstPerson, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    //
    pRetVal = (int*)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (n * sizeof(int)));
    pRetVal[0] = 0;
    pRetVal[1] = firstPerson;
    (*returnSize) = 2;

    //
    qsort(meetings, meetingsSize, sizeof(int*), compareIntArray);

    //
    int* flag = (int*)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(flag, 0, (n * sizeof(int)));
    flag[0] = 1;
    flag[firstPerson] = 1;

    int people;
    int start = 0;
    int num = 0;
    int i;
    for (i = 0; i < meetingsSize; i++) {
        if ((i > 0) && (meetings[i][2] != meetings[i - 1][2])) {
            start = i;
            num = 1;
        } else {
            num++;
        }

        if (flag[meetings[i][0]] != flag[meetings[i][1]]) {
            people = flag[meetings[i][0]] ? meetings[i][1] : meetings[i][0];
            pRetVal[(*returnSize)] = people;
            (*returnSize)++;
            flag[people] = 1;
        }

        if (((i < (meetingsSize - 1)) && (meetings[i][2] != meetings[i + 1][2])) || (i == (meetingsSize - 1))) {
            GetResult(meetings, start, num, pRetVal, returnSize, flag);
        }
    }

    //
    free(flag);
    flag = NULL;

    //
    qsort(pRetVal, (*returnSize), sizeof(int), compareInteger);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (int)(1e5)
#define MAX_COLUMN (3)
    struct testCaseType {
        int n;
        int meetings[MAX_ROW][MAX_COLUMN];
        int meetingsSize;
        int meetingsColSize[MAX_ROW];
        int firstPerson;
        int returnSize;
    } testCase[] = {{6, {{1, 2, 5}, {2, 3, 8}, {1, 5, 10}}, 3, {3, 3, 3}, 1, 0},
                    {4, {{3, 1, 3}, {1, 2, 2}, {0, 3, 3}}, 3, {3, 3, 3}, 3, 0},
                    {5, {{3, 4, 2}, {1, 2, 1}, {2, 3, 1}}, 3, {3, 3, 3}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
     *  Output: [0,1,2,3,5]
     *
     *  Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
     *  Output: [0,1,3]
     *
     *  Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
     *  Output: [0,1,2,3,4]
     */

    int** pMeetings = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, meetings = [", testCase[i].n);
        for (j = 0; j < testCase[i].meetingsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].meetingsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].meetings[j][k]);
            }
            printf("]");
        }
        printf("], firstPerson = %d\n", testCase[i].firstPerson);

        pMeetings = (int**)malloc(testCase[i].meetingsSize * sizeof(int*));
        if (pMeetings == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].meetingsSize; ++j) {
            pMeetings[j] = (int*)malloc(testCase[i].meetingsColSize[j] * sizeof(int));
            if (pMeetings[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pMeetings[k]);
                }
                free(pMeetings);
                return EXIT_FAILURE;
            }
            memset(pMeetings[j], 0, (testCase[i].meetingsColSize[j] * sizeof(int)));
            memcpy(pMeetings[j], testCase[i].meetings[j], (testCase[i].meetingsColSize[j] * sizeof(int)));
        }
        pAnswer = findAllPeople(testCase[i].n, pMeetings, testCase[i].meetingsSize, testCase[i].meetingsColSize,
                                testCase[i].firstPerson, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].meetingsSize; ++j) {
            free(pMeetings[j]);
        }
        free(pMeetings);
        pMeetings = NULL;
    }

    return EXIT_SUCCESS;
}
