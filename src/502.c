#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/ipo/solutions/269573/liang-ge-shu-lie-fen-bie-pai-xu-by-ni8fun/
typedef struct {
    int profit;
    int capital;
} projectsNode_t;
int compareStructCapital(const void* a, const void* b) {
    projectsNode_t* p1 = (projectsNode_t*)a;
    projectsNode_t* p2 = (projectsNode_t*)b;

    // ascending order
    return (p1->capital > p2->capital);
}
int compareStructProfit(const void* a, const void* b) {
    projectsNode_t* p1 = (projectsNode_t*)a;
    projectsNode_t* p2 = (projectsNode_t*)b;

    // ascending order
    return (p1->profit > p2->profit);
}
int findMaximizedCapital(int k, int w, int* profits, int profitsSize, int* capital, int capitalSize) {
    int retVal = 0;

    int idxProjects = 0;
    projectsNode_t projects[profitsSize];
    memset(projects, 0, sizeof(projects));
    int i;
    for (i = 0; i < profitsSize; i++) {
        projects[i].profit = profits[i];
        projects[i].capital = capital[i];
    }
    qsort(projects, profitsSize, sizeof(projectsNode_t), compareStructCapital);

    int idxCopyProjects = 0;
    projectsNode_t copyProjects[profitsSize];
    memset(copyProjects, 0, sizeof(copyProjects));
    bool inserted;
    while (k > 0) {
        inserted = false;
        while ((idxProjects < profitsSize) && (projects[idxProjects].capital <= w)) {
            inserted = true;
            copyProjects[idxCopyProjects] = projects[idxProjects];
            idxCopyProjects++;
            idxProjects++;
        }

        if (idxCopyProjects > 0) {
            if (inserted == true) {
                qsort(copyProjects, idxCopyProjects, sizeof(projectsNode_t), compareStructProfit);
            }
            w += copyProjects[idxCopyProjects - 1].profit;
            idxCopyProjects--;
        }

        k--;
    }
    retVal = w;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int k;
        int w;
        int profits[MAX_SIZE];
        int profitsSize;
        int capital[MAX_SIZE];
        int capitalSize;
    } testCase[] = {{2, 0, {1, 2, 3}, 3, {0, 1, 1}, 3}, {3, 0, {1, 2, 3}, 3, {0, 1, 2}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
     *  Output: 4
     *
     *  Input: k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
     *  Output: 6
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: k = %d, w = %d, profits = [", testCase[i].k, testCase[i].w);
        for (j = 0; j < testCase[i].profitsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].profits[j]);
        }
        printf("], capital = [");
        for (j = 0; j < testCase[i].capitalSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].capital[j]);
        }
        printf("]\n");

        answer = findMaximizedCapital(testCase[i].k, testCase[i].w, testCase[i].profits, testCase[i].profitsSize,
                                      testCase[i].capital, testCase[i].capitalSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
