#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/snapshot-array/solutions/2302755/cyu-yan-1146-kuai-zhao-shu-zu-by-shua-le-uyw9/

#define MAX_CALLS (50000)  // At most 5 * 10^4 calls will be made to set, snap, and get.
typedef struct {
    int nums[MAX_CALLS];
    int index[MAX_CALLS];
    int idx;
    int snaps[MAX_CALLS];
    int snapId;
} SnapshotArray;
SnapshotArray* snapshotArrayCreate(int length) {
    SnapshotArray* pObj = (SnapshotArray*)malloc(sizeof(SnapshotArray));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    memset(pObj, 0, sizeof(SnapshotArray));

    return pObj;
}
void snapshotArraySet(SnapshotArray* obj, int index, int val) {
    obj->nums[obj->idx] = val;
    obj->index[obj->idx] = index;
    obj->idx += 1;
}
int snapshotArraySnap(SnapshotArray* obj) {
    int retVal = obj->snapId;

    obj->snaps[obj->snapId] = obj->idx;
    obj->snapId += 1;

    return retVal;
}
int snapshotArrayGet(SnapshotArray* obj, int index, int snap_id) {
    int retVal = 0;

    int i;
    for (i = obj->snaps[snap_id] - 1; i >= 0; --i) {
        if (obj->index[i] == index) {
            retVal = obj->nums[i];
            break;
        }
    }

    return retVal;
}
void snapshotArrayFree(SnapshotArray* obj) {
    free(obj);
    obj = NULL;
}
/**
 * Your SnapshotArray struct will be instantiated and called as such:
 * SnapshotArray* obj = snapshotArrayCreate(length);
 * snapshotArraySet(obj, index, val);
 * int param_2 = snapshotArraySnap(obj);
 * int param_3 = snapshotArrayGet(obj, index, snap_id);
 * snapshotArrayFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][3];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {
        {{"SnapshotArray", "set", "snap", "set", "get"}, {{3}, {0, 5}, {}, {0, 6}, {0, 0}}, {1, 2, 0, 2, 2}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: ["SnapshotArray","set","snap","set","get"]
     *  [[3],[0,5],[],[0,6],[0,0]]
     *  Output: [null,null,0,null,5]
     */

    SnapshotArray* obj = NULL;
    int retInt;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[", (j == 0) ? "" : ", ");
            for (k = 0; k < testCase[i].valSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].val[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s", (j == 0) ? "" : ",");

            if (strcmp(testCase[i].methods[j], "SnapshotArray") == 0) {
                obj = snapshotArrayCreate(testCase[i].val[j][0]);
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "set") == 0) {
                snapshotArraySet(obj, testCase[i].val[j][0], testCase[i].val[j][1]);
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "snap") == 0) {
                retInt = snapshotArraySnap(obj);
                printf("%d", retInt);
            } else if (strcmp(testCase[i].methods[j], "get") == 0) {
                retInt = snapshotArrayGet(obj, testCase[i].val[j][0], testCase[i].val[j][1]);
                printf("%d", retInt);
            }
        }
        printf("]\n");

        snapshotArrayFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
