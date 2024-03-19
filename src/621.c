#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int leastInterval(char* tasks, int tasksSize, int n) {
    int retVal = 0;

    int frequencySize = 26;
    int frequency[frequencySize];
    memset(frequency, 0, sizeof(frequency));
    int maxFrequency = 0;

    int i;
    for (i = 0; i < tasksSize; ++i) {
        int idx = tasks[i] - 'A';
        frequency[idx]++;
        maxFrequency = fmax(maxFrequency, frequency[idx]);
    }

    int time = (maxFrequency - 1) * (n + 1);
    for (i = 0; i < frequencySize; ++i) {
        if (frequency[i] == maxFrequency) {
            time++;
        }
    }

    retVal = fmax(tasksSize, time);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char tasks[MAX_SIZE];
        int tasksSize;
        int n;
    } testCase[] = {{{'A', 'A', 'A', 'B', 'B', 'B'}, 6, 2},
                    {{'A', 'C', 'A', 'B', 'D', 'B'}, 6, 1},
                    {{'A', 'A', 'A', 'B', 'B', 'B'}, 6, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: tasks = ["A","A","A","B","B","B"], n = 2
     *  Output: 8
     *
     *  Input: tasks = ["A","C","A","B","D","B"], n = 1
     *  Output: 6
     *
     *  Input: tasks = ["A","A","A", "B","B","B"], n = 3
     *  Output: 10
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: tasks = [");
        for (j = 0; j < testCase[i].tasksSize; ++j) {
            printf("%s\"%c\"", (j == 0) ? "" : ",", testCase[i].tasks[j]);
        }
        printf("], n = %d\n", testCase[i].n);

        answer = leastInterval(testCase[i].tasks, testCase[i].tasksSize, testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
