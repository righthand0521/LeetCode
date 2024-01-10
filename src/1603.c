#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int big;
    int medium;
    int small;
} ParkingSystem;
ParkingSystem* parkingSystemCreate(int big, int medium, int small) {
    ParkingSystem* pCreate = (ParkingSystem*)malloc(sizeof(ParkingSystem));
    if (pCreate == NULL) {
        perror("malloc");
        return pCreate;
    }
    pCreate->big = big;
    pCreate->medium = medium;
    pCreate->small = small;

    return pCreate;
}
bool parkingSystemAddCar(ParkingSystem* obj, int carType) {
    bool retVal = false;

    switch (carType) {
        case 1:
            if (obj->big > 0) {
                obj->big--;
                retVal = true;
            }
            break;
        case 2:
            if (obj->medium > 0) {
                obj->medium--;
                retVal = true;
            }
            break;
        case 3:
            if (obj->small > 0) {
                obj->small--;
                retVal = true;
            }
            break;
        default:
            break;
    }

    return retVal;
}
void parkingSystemFree(ParkingSystem* obj) {
    free(obj);
    obj = NULL;
}
/**
 * Your ParkingSystem struct will be instantiated and called as such:
 * ParkingSystem* obj = parkingSystemCreate(big, medium, small);
 * bool param_1 = parkingSystemAddCar(obj, carType);
 * parkingSystemFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][3];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"ParkingSystem", "addCar", "addCar", "addCar", "addCar"},
                     {{1, 1, 0}, {1}, {2}, {3}, {1}},
                     {3, 1, 1, 1, 1},
                     5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["ParkingSystem", "addCar", "addCar", "addCar", "addCar"]
     *  [[1, 1, 0], [1], [2], [3], [1]]
     *  Output
     *  [null, true, true, false, false]
     */

    ParkingSystem* obj = NULL;
    bool retBool;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[", (j == 0) ? "" : ", ");
            for (k = 0; k < testCase[i].valSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ", ", testCase[i].val[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "ParkingSystem") == 0) {
                obj = parkingSystemCreate(testCase[i].val[j][0], testCase[i].val[j][1], testCase[i].val[j][2]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "addCar") == 0) {
                retBool = parkingSystemAddCar(obj, testCase[i].val[j][0]);
                printf("%s%s", (j == 0) ? "" : ", ", (retBool == true ? "true" : "false"));
            }
        }
        printf("]\n");

        parkingSystemFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
