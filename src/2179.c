#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FENWICKTREE_H
#define FENWICKTREE_H

typedef struct {
    int* tree;
    int size;
} FenwickTree;
FenwickTree* fenwickTreeCreate(int size) {
    FenwickTree* obj = NULL;

    obj = (FenwickTree*)malloc(sizeof(FenwickTree));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }

    obj->size = size;
    obj->tree = (int*)calloc(size + 1, sizeof(int));
    if (obj->tree == NULL) {
        perror("malloc");
        free(obj);
        obj = NULL;
        return obj;
    }

    return obj;
}
void fenwickTreeUpdate(FenwickTree* obj, int index, int delta) {
    index++;
    while (index <= obj->size) {
        obj->tree[index] += delta;
        index += (index & -index);
    }
}
int fenwickTreeQuery(FenwickTree* obj, int index) {
    int retVal = 0;

    index++;
    while (index > 0) {
        retVal += obj->tree[index];
        index -= (index & -index);
    }

    return retVal;
}
void fenwickTreeFree(FenwickTree* obj) {
    free(obj->tree);
    obj->tree = NULL;
    free(obj);
    obj = NULL;
}

#endif  // FENWICKTREE_H
long long goodTriplets(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    long long retVal = 0;

    int* pos2 = (int*)malloc(nums1Size * sizeof(int));
    if (pos2 == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < nums1Size; i++) {
        pos2[nums2[i]] = i;
    }

    int* reversedIndexMapping = (int*)malloc(nums1Size * sizeof(int));
    if (reversedIndexMapping == NULL) {
        perror("malloc");
        free(pos2);
        return retVal;
    }
    for (int i = 0; i < nums1Size; i++) {
        reversedIndexMapping[pos2[nums1[i]]] = i;
    }

    FenwickTree* tree = fenwickTreeCreate(nums1Size);
    if (tree == NULL) {
        perror("malloc");
        free(pos2);
        free(reversedIndexMapping);
        return retVal;
    }

    for (int value = 0; value < nums1Size; value++) {
        int pos = reversedIndexMapping[value];
        int left = fenwickTreeQuery(tree, pos);
        fenwickTreeUpdate(tree, pos, 1);

        int right = (nums1Size - 1 - pos) - (value - left);
        retVal += ((long long)left * right);
    }

    // Free allocated memory
    free(pos2);
    free(reversedIndexMapping);
    fenwickTreeFree(tree);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
    } testCase[] = {{{2, 0, 1, 3}, 4, {0, 1, 2, 3}, 4}, {{4, 0, 1, 3, 2}, 5, {4, 1, 0, 2, 3}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
     *  Output: 1
     *
     *  Input: nums1 = [4,0,1,3,2], nums2 = [4,1,0,2,3]
     *  Output: 4
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums1 = [");
        for (j = 0; j < testCase[i].nums1Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums1[j]);
        }
        printf("], nums2 = [");
        for (j = 0; j < testCase[i].nums2Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums2[j]);
        }
        printf("]\n");

        answer = goodTriplets(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
