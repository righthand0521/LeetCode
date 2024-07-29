#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numTeams(int* rating, int ratingSize) {
    int retVal = 0;

    int leftLarger, rightSmaller;
    int leftSmaller, rightLarger;
    int middle, left, right;
    for (middle = 0; middle < ratingSize; ++middle) {
        // Count soldiers with smaller ratings on the left side of the current soldier
        leftSmaller = 0;
        for (left = middle - 1; left >= 0; --left) {
            if (rating[left] < rating[middle]) {
                leftSmaller += 1;
            }
        }

        // Count soldiers with larger ratings on the right side of the current soldier
        rightLarger = 0;
        for (right = middle + 1; right < ratingSize; ++right) {
            if (rating[right] > rating[middle]) {
                rightLarger += 1;
            }
        }

        // Calculate and add the number of ascending rating teams (small-middle-large)
        retVal += (leftSmaller * rightLarger);

        // Calculate soldiers with larger ratings on the left and smaller ratings on the right
        leftLarger = middle - leftSmaller;
        rightSmaller = ratingSize - middle - 1 - rightLarger;

        // Calculate and add the number of descending rating teams (large-middle-small)
        retVal += (leftLarger * rightSmaller);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int rating[MAX_SIZE];
        int ratingSize;
    } testCase[] = {{{2, 5, 3, 4, 1}, 5}, {{2, 1, 3}, 3}, {{1, 2, 3, 4}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: rating = [2,5,3,4,1]
     *  Output: 3
     *
     *  Input: rating = [2,1,3]
     *  Output: 0
     *
     *  Input: rating = [1,2,3,4]
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: rating = [");
        for (j = 0; j < testCase[i].ratingSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].rating[j]);
        }
        printf("]\n");

        answer = numTeams(testCase[i].rating, testCase[i].ratingSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
