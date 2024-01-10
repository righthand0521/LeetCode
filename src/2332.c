#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int latestTimeCatchTheBus(int* buses, int busesSize, int* passengers, int passengersSize, int capacity) {
    int retVal = 0;

    //
    int busesIdx = 0;
    qsort(buses, busesSize, sizeof(int), compareInteger);
    int passengersIdx = 0;
    qsort(passengers, passengersSize, sizeof(int), compareInteger);
    int capacityIdx;

    //
    capacityIdx = 0;
    while ((busesIdx < (busesSize - 1)) && (passengersIdx < passengersSize)) {
        if ((passengers[passengersIdx] <= buses[busesIdx]) && (capacityIdx < capacity)) {
            ++passengersIdx;
            ++capacityIdx;
        } else {
            ++busesIdx;
            capacityIdx = 0;
        }
    }
    capacityIdx = 0;
    while ((passengersIdx < passengersSize) && (passengers[passengersIdx] <= buses[busesSize - 1]) &&
           (capacityIdx < capacity)) {
        ++passengersIdx;
        ++capacityIdx;
    }

    //
    if (capacityIdx < capacity) {
        retVal = buses[busesSize - 1];
    } else {
        retVal = passengers[passengersIdx - 1];
    }
    --passengersIdx;
    while ((passengersIdx >= 0) && (retVal == passengers[passengersIdx])) {
        retVal = passengers[passengersIdx] - 1;
        --passengersIdx;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int buses[MAX_SIZE];
        int busesSize;
        int passengers[MAX_SIZE];
        int passengersSize;
        int capacity;
    } testCase[] = {{{10, 20}, 2, {2, 17, 18, 19}, 4, 2}, {{20, 30, 10}, 3, {19, 13, 26, 4, 25, 11, 21}, 7, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: buses = [10,20], passengers = [2,17,18,19], capacity = 2
     *  Output: 16
     *
     *  Input: buses = [20,30,10], passengers = [19,13,26,4,25,11,21], capacity = 2
     *  Output: 20
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: buses = [");
        for (j = 0; j < testCase[i].busesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].buses[j]);
        }
        printf("], passengers = [");
        for (j = 0; j < testCase[i].passengersSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].passengers[j]);
        }
        printf("], capacity = %d\n", testCase[i].capacity);

        answer = latestTimeCatchTheBus(testCase[i].buses, testCase[i].busesSize, testCase[i].passengers,
                                       testCase[i].passengersSize, testCase[i].capacity);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
