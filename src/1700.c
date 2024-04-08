#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countStudents(int* students, int studentsSize, int* sandwiches, int sandwichesSize) {
    int retVal = 0;

    int i;

    // The school cafeteria offers circular and square sandwiches at lunch break,
    // referred to by numbers 0 and 1 respectively.
    int circular = 0;
    int square = 0;
    for (i = 0; i < studentsSize; ++i) {
        if (students[i] == 0) {
            circular++;
        } else if (students[i] == 1) {
            square++;
        }
    }

    for (i = 0; i < sandwichesSize; ++i) {
        if ((sandwiches[i] == 0) && (circular != 0)) {
            circular--;
        } else if ((sandwiches[i] == 1) && (square != 0)) {
            square--;
        } else {
            retVal = circular + square;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int students[MAX_SIZE];
        int studentsSize;
        int sandwiches[MAX_SIZE];
        int sandwichesSize;
    } testCase[] = {{{1, 1, 0, 0}, 4, {0, 1, 0, 1}, 4}, {{1, 1, 1, 0, 0, 1}, 6, {1, 0, 0, 0, 1, 1}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: students = [1,1,0,0], sandwiches = [0,1,0,1]
     *  Output: 0
     *
     *  Input: students = [1,1,1,0,0,1], sandwiches = [1,0,0,0,1,1]
     *  Output: 3
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: students = [");
        for (j = 0; j < testCase[i].studentsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].students[j]);
        }
        printf("], sandwiches = [");
        for (j = 0; j < testCase[i].sandwichesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].sandwiches[j]);
        }
        printf("]\n");

        answer = countStudents(testCase[i].students, testCase[i].studentsSize, testCase[i].sandwiches,
                               testCase[i].sandwichesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
