#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
double average(int* salary, int salarySize) {
    double retVal = 0;

    double sum = 0;
    int i;
#if (1)
    int max = salary[0];
    int min = salary[0];
    for (i = 0; i < salarySize; ++i) {
        max = ((max > salary[i]) ? max : salary[i]);
        min = ((min < salary[i]) ? min : salary[i]);
        sum += salary[i];
    }
    sum = sum - max - min;
#else
    qsort(salary, salarySize, sizeof(int), compareInteger);
    for (i = 1; i < (salarySize - 1); ++i) {
        sum += salary[i];
    }
#endif
    retVal = sum / (salarySize - 2);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int salary[MAX_SIZE];
        int salarySize;
    } testCase[] = {{{4000, 3000, 1000, 2000}, 4}, {{1000, 2000, 3000}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: salary = [4000,3000,1000,2000]
     *  Output: 2500.00000
     *
     *  Input: salary = [1000,2000,3000]
     *  Output: 2000.00000
     */

    double answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: salary = [");
        for (j = 0; j < testCase[i].salarySize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].salary[j]);
        }
        printf("]\n");

        answer = average(testCase[i].salary, testCase[i].salarySize);
        printf("Output: %f\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
