#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEPTH_FIRST_SEARCH (0)
#define BREADTH_FIRST_SEARCH (1)
#if (DEPTH_FIRST_SEARCH)
void dfs(int** rooms, int roomsSize, int* roomsColSize, int enterRoomNumber, bool* visitedRoom, int* openedRoomCount) {
    visitedRoom[enterRoomNumber] = true;
    ++(*openedRoomCount);

    int romNumber;
    int i;
    for (i = 0; i < roomsColSize[enterRoomNumber]; ++i) {
        romNumber = rooms[enterRoomNumber][i];
        if (visitedRoom[romNumber] == false) {
            dfs(rooms, roomsSize, roomsColSize, romNumber, visitedRoom, openedRoomCount);
        }
    }
}
#elif (BREADTH_FIRST_SEARCH)
void bfs(int** rooms, int roomsSize, int* roomsColSize, int enterRoomNumber, bool* visitedRoom, int* openedRoomCount) {
    visitedRoom[enterRoomNumber] = true;

    int queue[roomsSize];
    memset(queue, 0, sizeof(queue));
    queue[0] = enterRoomNumber;
    int romNumber;
    int i;
    int left = 0;
    int right = 1;
    while (left < right) {
        enterRoomNumber = queue[left++];
        ++(*openedRoomCount);
        for (i = 0; i < roomsColSize[enterRoomNumber]; ++i) {
            romNumber = rooms[enterRoomNumber][i];
            if (visitedRoom[romNumber] == false) {
                visitedRoom[romNumber] = true;
                queue[right++] = romNumber;
            }
        }
    }
}
#endif
bool canVisitAllRooms(int** rooms, int roomsSize, int* roomsColSize) {
    bool retVal = false;

    bool visitedRoom[roomsSize];
    memset(visitedRoom, false, sizeof(visitedRoom));
    int openedRoomCount = 0;
#if (DEPTH_FIRST_SEARCH)
    printf("DEPTH_FIRST_SEARCH\n");

    dfs(rooms, roomsSize, roomsColSize, 0, visitedRoom, &openedRoomCount);
#elif (BREADTH_FIRST_SEARCH)
    printf("BREADTH_FIRST_SEARCH\n");

    bfs(rooms, roomsSize, roomsColSize, 0, visitedRoom, &openedRoomCount);
#endif
    if (openedRoomCount == roomsSize) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int rooms[MAX_SIZE][MAX_SIZE];
        int roomsSize;
        int roomsColSize[MAX_SIZE];
    } testCase[] = {{{{1}, {2}, {3}, {}}, 4, {1, 1, 1, 1}}, {{{1, 3}, {3, 0, 1}, {2}, {0}}, 4, {2, 3, 1, 1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: rooms = [[1],[2],[3],[]]
     *  Output: true
     *
     *  Input: rooms = [[1,3],[3,0,1],[2],[0]]
     *  Output: false
     */

    int** pRooms = NULL;
    bool answer = false;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: rooms = [");
        for (j = 0; j < testCase[i].roomsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].roomsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].rooms[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pRooms = (int**)malloc(testCase[i].roomsSize * sizeof(int*));
        if (pRooms == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].roomsSize; ++j) {
            pRooms[j] = malloc(testCase[i].roomsColSize[j] * sizeof(int));
            if (pRooms[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pRooms[k]);
                }
                free(pRooms);
                pRooms = NULL;
                return EXIT_FAILURE;
            }
            memset(pRooms[j], 0, testCase[i].roomsColSize[j] * sizeof(int));
            memcpy(pRooms[j], testCase[i].rooms[j], testCase[i].roomsColSize[j] * sizeof(int));
        }
        answer = canVisitAllRooms(pRooms, testCase[i].roomsSize, testCase[i].roomsColSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        for (j = 0; j < testCase[i].roomsSize; ++j) {
            free(pRooms[j]);
        }
        free(pRooms);
        pRooms = NULL;
    }

    return EXIT_SUCCESS;
}
