#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE (26)  // fromi and toi consist of uppercase English letters.
int str2id(char *a) {
    int retVal = 0;

    // fromi.length == 3, toi.length == 3, fromi and toi consist of uppercase English letters.
    int i;
    for (i = 0; i < 3; i++) {
        retVal = retVal * BUF_SIZE + a[i] - 'A';
    }

    return retVal;
}
int compareIntArray(const void *_a, const void *_b) {
    int **a = (int **)_a;
    int **b = (int **)_b;

    // descending order
    if ((*b)[0] == (*a)[0]) {
        return ((*a)[1] < (*b)[1]);
    }

    return ((*a)[0] < (*b)[0]);
}
void dfs(int departs, int **flight, int *flightSize, int *stack, int *stackSize) {
    int tmp;
    while (flightSize[departs] > 0) {
        tmp = flight[departs][--flightSize[departs]];
        dfs(tmp, flight, flightSize, stack, stackSize);
    }
    stack[(*stackSize)++] = departs;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **findItinerary(char ***tickets, int ticketsSize, int *ticketsColSize, int *returnSize) {
    char **pRetVal = NULL;

    (*returnSize) = 0;

    int i;

    //
    char *id2str[BUF_SIZE * BUF_SIZE * BUF_SIZE];
    int *tickets_tmp[ticketsSize];
    for (int i = 0; i < ticketsSize; i++) {
        tickets_tmp[i] = (int *)malloc(sizeof(int) * 2);
        tickets_tmp[i][0] = str2id(tickets[i][0]);
        tickets_tmp[i][1] = str2id(tickets[i][1]);
        id2str[tickets_tmp[i][0]] = tickets[i][0];
        id2str[tickets_tmp[i][1]] = tickets[i][1];
    }
    qsort(tickets_tmp, ticketsSize, sizeof(int *), compareIntArray);

    //
    int **flight = (int **)malloc((BUF_SIZE * BUF_SIZE * BUF_SIZE) * sizeof(int *));
    int *flightSize = (int *)malloc((BUF_SIZE * BUF_SIZE * BUF_SIZE) * sizeof(int));
    memset(flightSize, 0, ((BUF_SIZE * BUF_SIZE * BUF_SIZE) * sizeof(int)));
    int flightFree[BUF_SIZE * BUF_SIZE * BUF_SIZE];
    memset(flightFree, 0, sizeof(flightFree));
    int flightFreeSize = 0;
    int adds, start;
    int add = 0;
    while (add < ticketsSize) {
        adds = add + 1;
        start = tickets_tmp[add][0];
        while ((adds < ticketsSize) && (start == tickets_tmp[adds][0])) {
            adds++;
        }

        flightSize[start] = adds - add;
        flight[start] = (int *)malloc(sizeof(int) * flightSize[start]);
        memset(flight[start], 0, (sizeof(int) * flightSize[start]));
        flightFree[flightFreeSize++] = start;

        for (i = add; i < adds; i++) {
            flight[start][i - add] = tickets_tmp[i][1];
        }
        add = adds;
    }

    //
    int *stack = (int *)malloc(sizeof(int) * (ticketsSize + 1));
    int stackSize = 0;
    dfs(str2id("JFK"), flight, flightSize, stack, &stackSize);

    //
    (*returnSize) = ticketsSize + 1;
    pRetVal = (char **)malloc(sizeof(char *) * (ticketsSize + 1));
    for (i = 0; i <= ticketsSize; i++) {
        pRetVal[ticketsSize - i] = id2str[stack[i]];
    }

    //
    free(stack);
    stack = NULL;
    for (i = 0; i < flightFreeSize; i++) {
        free(flight[flightFree[i]]);
        flight[i] = NULL;
    }
    free(flight);
    flight = NULL;
    free(flightSize);
    flightSize = NULL;
    for (i = 0; i < ticketsSize; i++) {
        free(tickets_tmp[i]);
        tickets_tmp[i] = NULL;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        char *tickets[MAX_SIZE][2];
        int ticketsSize;
        int ticketsColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {
        {{{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}}, 4, {2, 2, 2, 2}, 0},
        {{{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}}, 5, {2, 2, 2, 2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
     *  Output: ["JFK","MUC","LHR","SFO","SJC"]
     *
     *  Input: tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
     *  Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
     */

    char ***pTickets = NULL;
    char **pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: tickets = [");
        for (j = 0; j < testCase[i].ticketsSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", "[");
            for (k = 0; k < testCase[i].ticketsColSize[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", testCase[i].tickets[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pTickets = (char ***)malloc(testCase[i].ticketsSize * sizeof(char **));
        if (pTickets == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].ticketsSize; ++j) {
            pTickets[j] = (char **)malloc(testCase[i].ticketsColSize[j] * sizeof(char *));
            if (pTickets[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pTickets[k]);
                    pTickets[k] = NULL;
                }
                free(pTickets);
                pTickets = NULL;
                return EXIT_FAILURE;
            }
            memset(pTickets[j], 0, (testCase[i].ticketsColSize[j] * sizeof(char *)));
            memcpy(pTickets[j], testCase[i].tickets[j], (testCase[i].ticketsColSize[j] * sizeof(char *)));
        }
        pAnswer = findItinerary(pTickets, testCase[i].ticketsSize, testCase[i].ticketsColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].ticketsSize; ++j) {
            free(pTickets[j]);
            pTickets[j] = NULL;
        }
        free(pTickets);
        pTickets = NULL;
    }

    return EXIT_SUCCESS;
}
