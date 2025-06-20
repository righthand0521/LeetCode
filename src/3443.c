#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxDistance(char* s, int k) {
    int retVal = 0;

    int latitude = 0;
    int longitude = 0;
    int sSize = strlen(s);
    for (int i = 0; i < sSize; i++) {
        switch (s[i]) {
            case 'N':
                latitude++;
                break;
            case 'S':
                latitude--;
                break;
            case 'E':
                longitude++;
                break;
            case 'W':
                longitude--;
                break;
        }
        retVal = fmax(retVal, fmin(abs(latitude) + abs(longitude) + k * 2, i + 1));
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        int k;
    } testCase[] = {{"NWSE", 1}, {"NSWWEW", 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "NWSE", k = 1
     *  Output: 3
     *
     *  Input: s = "NSWWEW", k = 3
     *  Output: 6
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; i++) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        answer = maxDistance(testCase[i].s, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
