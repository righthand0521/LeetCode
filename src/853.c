#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/car-fleet/solutions/1117337/cyu-yan-jian-dan-bian-liang-mei-sha-suan-9lbs/
typedef struct {
    double distance;
    double speed;
    double time;
} CarInfo;
int compareStruct(const void *a1, const void *a2) {
    CarInfo *p1 = (CarInfo *)a1;
    CarInfo *p2 = (CarInfo *)a2;

    // ascending order
    return (p1->distance > p2->distance);
}
int carFleet(int target, int *position, int positionSize, int *speed, int speedSize) {
    int retVal = 0;

    int i;

    CarInfo *pCarInfo = malloc(sizeof(CarInfo) * positionSize);
    if (pCarInfo == NULL) {
        perror("malloc");
        return retVal;
    }
    for (i = 0; i < positionSize; i++) {
        pCarInfo[i].distance = target - position[i];
        pCarInfo[i].speed = speed[i];
        pCarInfo[i].time = pCarInfo[i].distance / pCarInfo[i].speed;
    }
    qsort(pCarInfo, positionSize, sizeof(CarInfo), compareStruct);

    double current = 0;
    for (i = 0; i < positionSize; i++) {
        if (pCarInfo[i].time > current) {
            retVal++;
            current = pCarInfo[i].time;
        }
    }

    free(pCarInfo);
    pCarInfo = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int target;
        int position[MAX_SIZE];
        int positionSize;
        int speed[MAX_SIZE];
        int speedSize;
    } testCase[] = {
        {12, {10, 8, 0, 5, 3}, 5, {2, 4, 1, 1, 3}, 5}, {10, {3}, 1, {3}, 1}, {100, {0, 2, 4}, 3, {4, 2, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
     *  Output: 3
     *
     *  Input: target = 10, position = [3], speed = [3]
     *  Output: 1
     *
     *  Input: target = 100, position = [0,2,4], speed = [4,2,1]
     *  Output: 1
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: target = %d, position = [", testCase[i].target);
        for (j = 0; j < testCase[i].positionSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].position[j]);
        }
        printf("], speed = [");
        for (j = 0; j < testCase[i].speedSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].speed[j]);
        }
        printf("]\n");

        answer = carFleet(testCase[i].target, testCase[i].position, testCase[i].positionSize, testCase[i].speed,
                          testCase[i].speedSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
