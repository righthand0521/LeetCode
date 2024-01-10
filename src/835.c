#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRUTE_FORCE (1)
#if (BRUTE_FORCE)  // Time Complexity: O(n^4), Space Complexity: O(n^2)
int overlap(int** img1, int** img2, int n, int row, int col) {
    int count = 0;

    int i, j;

    // create shifting img1
    int tmp[n][n];
    int x, y;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            tmp[i][j] = 0;

            x = -1;
            if (((i + row) >= 0) && ((i + row) < n)) {
                x = i + row;
            }

            y = -1;
            if (((j + col) >= 0) && ((j + col) < n)) {
                y = j + col;
            }

            if ((x >= 0) && (y >= 0)) {
                tmp[i][j] = img1[x][y];
            }
        }
    }

    // count overlap
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (tmp[i][j] == 0) {
                continue;
            }
            if (tmp[i][j] == img2[i][j]) {
                count++;
            }
        }
    }

    return count;
}
#endif
int largestOverlap(int** img1, int img1Size, int* img1ColSize, int** img2, int img2Size, int* img2ColSize) {
    int retVal = 0;

#if (BRUTE_FORCE)
    int n = img1Size;
    int count;
    int i, j;
    for (i = (-n + 1); i < n; i++) {
        for (j = (-n + 1); j < n; j++) {
            count = overlap(img1, img2, n, i, j);
            retVal = (retVal > count) ? retVal : count;
        }
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (30)
    struct testCaseType {
        int img1[MAX_SIZE][MAX_SIZE];
        int img1Size;
        int img1ColSize[MAX_SIZE];
        int img2[MAX_SIZE][MAX_SIZE];
        int img2Size;
        int img2ColSize[MAX_SIZE];
    } testCase[] = {{{{1, 1, 0}, {0, 1, 0}, {0, 1, 0}}, 3, {3, 3, 3}, {{0, 0, 0}, {0, 1, 1}, {0, 0, 1}}, 3, {3, 3, 3}},
                    {{{1}}, 1, {1}, {{1}}, 1, {1}},
                    {{{0}}, 1, {1}, {{0}}, 1, {1}},
                    {{{0, 0, 0, 0, 1}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}},
                     5,
                     {5, 5, 5, 5, 5},
                     {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {1, 0, 0, 0, 0}},
                     5,
                     {5, 5, 5, 5, 5}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pImg1 = NULL;
    int** pImg2 = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: img1 = [");
        for (j = 0; j < testCase[i].img1Size; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].img1ColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].img1[j][k]);
            }
            printf("]");
        }
        printf("], img2 = [");
        for (j = 0; j < testCase[i].img2Size; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].img2ColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].img2[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pImg1 = (int**)malloc(testCase[i].img1Size * sizeof(int*));
        if (pImg1 == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].img1Size; ++j) {
            pImg1[j] = (int*)malloc(testCase[i].img1ColSize[j] * sizeof(int));
            if (pImg1[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pImg1[k]) {
                        free(pImg1[k]);
                        pImg1[k] = NULL;
                    }
                }
                free(pImg1);
                pImg1 = NULL;
                return EXIT_FAILURE;
            }
            memset(pImg1[j], 0, testCase[i].img1ColSize[j] * sizeof(int));
            memcpy(pImg1[j], testCase[i].img1[j], testCase[i].img1ColSize[j] * sizeof(int));
        }
        pImg2 = (int**)malloc(testCase[i].img2Size * sizeof(int*));
        if (pImg2 == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].img2Size; ++j) {
            pImg2[j] = (int*)malloc(testCase[i].img2ColSize[j] * sizeof(int));
            if (pImg2[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pImg2[k]) {
                        free(pImg2[k]);
                        pImg2[k] = NULL;
                    }
                }
                free(pImg2);
                pImg2 = NULL;
                return EXIT_FAILURE;
            }
            memset(pImg2[j], 0, testCase[i].img2ColSize[j] * sizeof(int));
            memcpy(pImg2[j], testCase[i].img2[j], testCase[i].img2ColSize[j] * sizeof(int));
        }
        answer = largestOverlap(pImg1, testCase[i].img1Size, testCase[i].img1ColSize, pImg2, testCase[i].img2Size,
                                testCase[i].img2ColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].img1Size; ++j) {
            if (pImg1[j]) {
                free(pImg1[j]);
                pImg1[j] = NULL;
            }
        }
        free(pImg1);
        pImg1 = NULL;
        for (j = 0; j < testCase[i].img2Size; ++j) {
            if (pImg2[j]) {
                free(pImg2[j]);
                pImg2[j] = NULL;
            }
        }
        free(pImg2);
        pImg2 = NULL;
    }

    return EXIT_SUCCESS;
}
