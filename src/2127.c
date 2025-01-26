#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximumInvitations(int* favorite, int favoriteSize) {
    int retVal = 0;

    // Calculate in-degree for each node
    int inDegree[favoriteSize];
    memset(inDegree, 0, sizeof(inDegree));
    for (int person = 0; person < favoriteSize; ++person) {
        inDegree[favorite[person]]++;
    }

    // Topological sorting to remove non-cycle nodes
    int TopologicalSortingQueueSize = 2 * favoriteSize + 1;
    int TopologicalSortingQueue[TopologicalSortingQueueSize];
    memset(TopologicalSortingQueue, 0, sizeof(TopologicalSortingQueue));
    int TopologicalSortingQueueFront = 0;
    int TopologicalSortingQueueRear = 0;
    for (int person = 0; person < favoriteSize; ++person) {
        if (inDegree[person] == 0) {
            TopologicalSortingQueue[TopologicalSortingQueueRear++] = person;
        }
    }

    int depth[favoriteSize];  // Depth of each node
    for (int i = 0; i < favoriteSize; ++i) {
        depth[i] = 1;
    }

    int currentNode, nextNode;
    while (TopologicalSortingQueueFront < TopologicalSortingQueueRear) {
        currentNode = TopologicalSortingQueue[TopologicalSortingQueueFront++];

        nextNode = favorite[currentNode];
        depth[nextNode] = fmax(depth[nextNode], depth[currentNode] + 1);

        inDegree[nextNode]--;
        if (inDegree[nextNode] == 0) {
            TopologicalSortingQueue[TopologicalSortingQueueRear++] = nextNode;
        }
    }

    // Detect cycles
    int cycleLength, current;
    int longestCycle = 0;
    int twoCycleInvitations = 0;
    for (int person = 0; person < favoriteSize; ++person) {
        if (inDegree[person] == 0) {  // Already processed
            continue;
        }

        cycleLength = 0;
        current = person;
        while (inDegree[current] != 0) {
            inDegree[current] = 0;  // Mark as visited
            cycleLength++;
            current = favorite[current];
        }

        if (cycleLength == 2) {  // For 2-cycles, add the depth of both nodes
            twoCycleInvitations += depth[person] + depth[favorite[person]];
        } else {
            longestCycle = fmax(longestCycle, cycleLength);
        }
    }

    retVal = fmax(longestCycle, twoCycleInvitations);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int favorite[MAX_SIZE];
        int favoriteSize;
    } testCase[] = {{{2, 2, 1, 2}, 4}, {{1, 2, 0}, 3}, {{3, 0, 1, 4, 1}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: favorite = [2,2,1,2]
     *  Output: 3
     *
     *  Input: favorite = [1,2,0]
     *  Output: 3
     *
     *  Input: favorite = [3,0,1,4,1]
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: favorite = [");
        for (j = 0; j < testCase[i].favoriteSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].favorite[j]);
        }
        printf("]\n");

        answer = maximumInvitations(testCase[i].favorite, testCase[i].favoriteSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
