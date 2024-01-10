#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

// https://leetcode.cn/problems/design-underground-system/solutions/1041714/cyu-yan-liang-ge-hashbiao-by-suckerfish-zl9lj/
#define STATION_LEN (12)  // 1 <= stationName.length, startStation.length, endStation.length <= 10
typedef struct {
    char station[STATION_LEN + STATION_LEN];
    int cnt;
    double averageTime;
    UT_hash_handle hh;
} Hash;
Hash* g_res = NULL;
typedef struct {
    int id;
    int checkInTime;
    char checkInStation[STATION_LEN];
    UT_hash_handle hh;
} UndergroundSystem;
UndergroundSystem* g_checkIn = NULL;
UndergroundSystem* undergroundSystemCreate() {
    UndergroundSystem* pRetVal = NULL;

    g_checkIn = NULL;
    g_res = NULL;

    return pRetVal;
}
void undergroundSystemCheckIn(UndergroundSystem* obj, int id, char* stationName, int t) {
    UndergroundSystem* temp = (UndergroundSystem*)calloc(1, sizeof(UndergroundSystem));
    temp->id = id;
    temp->checkInTime = t;
    strcpy(temp->checkInStation, stationName);

    HASH_ADD_INT(g_checkIn, id, temp);
}
void undergroundSystemCheckOut(UndergroundSystem* obj, int id, char* stationName, int t) {
    Hash* data = NULL;
    char str[STATION_LEN + STATION_LEN] = {0};

    UndergroundSystem* temp = NULL;
    HASH_FIND_INT(g_checkIn, &id, temp);
    if (temp != NULL) {
        strcpy(str, temp->checkInStation);
        strcat(str, "-");
        strcat(str, stationName);
        HASH_FIND_STR(g_res, str, data);
        if (data != NULL) {
            data->averageTime = ((data->averageTime * data->cnt) + (t - temp->checkInTime)) / (data->cnt + 1.0f);
            data->cnt++;
        } else {
            data = (Hash*)calloc(1, sizeof(Hash));
            strcpy(data->station, str);
            data->cnt = 1;
            data->averageTime = t - temp->checkInTime;
            HASH_ADD_STR(g_res, station, data);
        }
        HASH_DEL(g_checkIn, temp);
        free(temp);
    }
}
double undergroundSystemGetAverageTime(UndergroundSystem* obj, char* startStation, char* endStation) {
    double retVal = 0;

    char str[STATION_LEN + STATION_LEN] = {0};
    strcpy(str, startStation);
    strcat(str, "-");
    strcat(str, endStation);

    Hash* temp = NULL;
    HASH_FIND_STR(g_res, str, temp);
    if (temp != NULL) {
        retVal = temp->averageTime;
    }

    return retVal;
}
void undergroundSystemFree(UndergroundSystem* obj) {
    UndergroundSystem* cur = NULL;
    UndergroundSystem* tar = NULL;
    HASH_ITER(hh, g_checkIn, cur, tar) {
        if (cur) {
            HASH_DEL(g_checkIn, cur);
            free(cur);
        }
    }

    Hash* cur1 = NULL;
    Hash* tar1 = NULL;
    HASH_ITER(hh, g_res, cur1, tar1) {
        if (cur1) {
            HASH_DEL(g_res, cur1);
            free(cur1);
        }
    }
}
/**
 * Your UndergroundSystem struct will be instantiated and called as such:
 * UndergroundSystem* obj = undergroundSystemCreate();
 * undergroundSystemCheckIn(obj, id, stationName, t);
 * undergroundSystemCheckOut(obj, id, stationName, t);
 * double param_3 = undergroundSystemGetAverageTime(obj, startStation, endStation);
 * undergroundSystemFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e3)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int id[MAX_SIZE];
        char* stationName[MAX_SIZE];
        int t[MAX_SIZE];
        char* startStation[MAX_SIZE];
        char* endStation[MAX_SIZE];
        int calls;
    } testCase[] = {{{"UndergroundSystem", "checkIn", "checkIn", "checkIn", "checkOut", "checkOut", "checkOut",
                      "getAverageTime", "getAverageTime", "checkIn", "getAverageTime", "checkOut", "getAverageTime"},
                     {0, 45, 32, 27, 45, 27, 32, 0, 0, 10, 0, 10, 0},
                     {"", "Leyton", "Paradise", "Leyton", "Waterloo", "Waterloo", "Cambridge", "", "", "Leyton", "",
                      "Waterloo", ""},
                     {0, 3, 8, 10, 15, 20, 22, 0, 0, 24, 0, 38, 0},
                     {"", "", "", "", "", "", "", "Paradise", "Leyton", "", "Leyton", "", "Leyton"},
                     {"", "", "", "", "", "", "", "Cambridge", "Waterloo", "", "Waterloo", "", "Waterloo"},
                     13},
                    {{"UndergroundSystem", "checkIn", "checkOut", "getAverageTime", "checkIn", "checkOut",
                      "getAverageTime", "checkIn", "checkOut", "getAverageTime"},
                     {0, 10, 10, 0, 5, 5, 0, 2, 2, 0},
                     {"", "Leyton", "Paradise", "", "Leyton", "Paradise", "", "Leyton", "Paradise", ""},
                     {0, 3, 8, 0, 10, 16, 0, 21, 30, 0},
                     {"", "", "", "Leyton", "", "", "Leyton", "", "", "Leyton"},
                     {"", "", "", "Paradise", "", "", "Paradise", "", "", "Paradise"},
                     10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["UndergroundSystem","checkIn","checkIn","checkIn","checkOut",
     *  "checkOut","checkOut","getAverageTime","getAverageTime","checkIn",
     *  "getAverageTime","checkOut","getAverageTime"]
     *  [[],[45,"Leyton",3],[32,"Paradise",8],[27,"Leyton",10],[45,"Waterloo",15],
     *  [27,"Waterloo",20],[32,"Cambridge",22],["Paradise","Cambridge"],["Leyton","Waterloo"],[10,"Leyton",24],
     *  ["Leyton","Waterloo"],[10,"Waterloo",38],["Leyton","Waterloo"]]
     *  Output
     *  [null,null,null,null,null,null,null,14.00000,11.00000,null,11.00000,null,12.00000]
     *
     *  Input
     *  ["UndergroundSystem","checkIn","checkOut","getAverageTime","checkIn",
     *  "checkOut","getAverageTime","checkIn","checkOut","getAverageTime"]
     *  [[],[10,"Leyton",3],[10,"Paradise",8],["Leyton","Paradise"],[5,"Leyton",10],
     *  [5,"Paradise",16],["Leyton","Paradise"],[2,"Leyton",21],[2,"Paradise",30],["Leyton","Paradise"]]
     *  Output
     *  [null,null,null,5.00000,null,null,5.50000,null,null,6.66667]
     */

    UndergroundSystem* obj = NULL;
    double retVal;
    int i, j;
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
            if (strcmp(testCase[i].methods[j], "UndergroundSystem") == 0) {
                ;
            } else if (strcmp(testCase[i].methods[j], "checkIn") == 0) {
                printf("%d,%s,%d", testCase[i].id[j], testCase[i].stationName[j], testCase[i].t[j]);
            } else if (strcmp(testCase[i].methods[j], "checkOut") == 0) {
                printf("%d,%s,%d", testCase[i].id[j], testCase[i].stationName[j], testCase[i].t[j]);
            } else if (strcmp(testCase[i].methods[j], "getAverageTime") == 0) {
                printf("%s,%s", testCase[i].startStation[j], testCase[i].endStation[j]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "UndergroundSystem") == 0) {
                obj = undergroundSystemCreate();
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "checkIn") == 0) {
                undergroundSystemCheckIn(obj, testCase[i].id[j], testCase[i].stationName[j], testCase[i].t[j]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "checkOut") == 0) {
                undergroundSystemCheckOut(obj, testCase[i].id[j], testCase[i].stationName[j], testCase[i].t[j]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "getAverageTime") == 0) {
                retVal = undergroundSystemGetAverageTime(obj, testCase[i].startStation[j], testCase[i].endStation[j]);
                printf("%s%.5f", (j == 0) ? "" : ", ", retVal);
            }
        }
        printf("]\n");

        undergroundSystemFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
