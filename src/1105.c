#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minHeightShelves(int **books, int booksSize, int *booksColSize, int shelfWidth) {
    int retVal = 0;

    // dp[i] will store the minimum height of the bookcase containing all books up to and excluding i
    int dp[booksSize + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 0;
    dp[1] = books[0][1];

    int remainingShelfWidth, maxHeight;
    int i, j;
    for (i = 1; i <= booksSize; ++i) {
        // new shelf built to hold current book
        remainingShelfWidth = shelfWidth - books[i - 1][0];
        maxHeight = books[i - 1][1];
        dp[i] = dp[i - 1] + maxHeight;

        // calculate the height when previous books are added onto a new shelf
        j = i - 1;
        while ((j > 0) && (remainingShelfWidth - books[j - 1][0] >= 0)) {
            remainingShelfWidth -= books[j - 1][0];
            maxHeight = fmax(maxHeight, books[j - 1][1]);
            dp[i] = fmin(dp[i], dp[j - 1] + maxHeight);
            j--;
        }
    }
    retVal = dp[booksSize];

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int books[MAX_SIZE][2];
        int booksSize;
        int booksColSize[MAX_SIZE];
        int shelfWidth;
    } testCase[] = {{{{1, 1}, {2, 3}, {2, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 2}}, 7, {2, 2, 2, 2, 2, 2, 2}, 4},
                    {{{1, 3}, {2, 4}, {3, 2}}, 3, {2, 2, 2}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: books = [[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]], shelfWidth = 4
     *  Output: 6
     *
     *  Input: books = [[1,3],[2,4],[3,2]], shelfWidth = 6
     *  Output: 4
     */

    int **pBooks = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: books = [");
        for (j = 0; j < testCase[i].booksSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].booksColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].books[j][k]);
            }
            printf("]");
        }
        printf("], shelfWidth = %d\n", testCase[i].shelfWidth);

        pBooks = (int **)malloc(testCase[i].booksSize * sizeof(int *));
        if (pBooks == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].booksSize; ++j) {
            pBooks[j] = (int *)malloc(testCase[i].booksColSize[j] * sizeof(int));
            if (pBooks[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pBooks[k]);
                    pBooks[k] = NULL;
                }
                free(pBooks);
                pBooks = NULL;
                return EXIT_FAILURE;
            }
            memset(pBooks[j], 0, (testCase[i].booksColSize[j] * sizeof(int)));
            memcpy(pBooks[j], testCase[i].books[j], (testCase[i].booksColSize[j] * sizeof(int)));
        }
        answer = minHeightShelves(pBooks, testCase[i].booksSize, testCase[i].booksColSize, testCase[i].shelfWidth);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].booksSize; ++j) {
            free(pBooks[j]);
            pBooks[j] = NULL;
        }
        free(pBooks);
        pBooks = NULL;
    }

    return EXIT_SUCCESS;
}
