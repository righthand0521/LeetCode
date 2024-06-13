#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minMovesToSeat(int* seats, int seatsSize, int* students, int studentsSize) {
    int retVal = 0;

    qsort(seats, seatsSize, sizeof(int), compareInteger);
    qsort(students, studentsSize, sizeof(int), compareInteger);

    int i;
    for (i = 0; i < seatsSize; ++i) {
        retVal += abs(seats[i] - students[i]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int seats[MAX_SIZE];
        int seatsSize;
        int students[MAX_SIZE];
        int studentsSize;
    } testCase[] = {
        {{3, 1, 5}, 3, {2, 7, 4}, 3}, {{4, 1, 5, 9}, 4, {1, 3, 2, 6}, 4}, {{2, 2, 6, 6}, 4, {1, 3, 2, 6}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: seats = [3,1,5], students = [2,7,4]
     *  Output: 4
     *
     *  Input: seats = [4,1,5,9], students = [1,3,2,6]
     *  Output: 7
     *
     *  Input: seats = [2,2,6,6], students = [1,3,2,6]
     *  Output: 4
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: seats = [");
        for (j = 0; j < testCase[i].seatsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].seats[j]);
        }
        printf("], students = [");
        for (j = 0; j < testCase[i].studentsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].students[j]);
        }
        printf("]\n");

        answer =
            minMovesToSeat(testCase[i].seats, testCase[i].seatsSize, testCase[i].students, testCase[i].studentsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
