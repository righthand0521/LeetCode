#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BadValue;
bool isBadVersion(int version) {
    if (version < BadValue) {
        return false;
    }

    return true;
}
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);
int firstBadVersion(int n) {
    int retVal = 1;

    int mid;
    while (retVal < n) {
        mid = (retVal / 2) + (n / 2);
        if (isBadVersion(mid) == true) {
            n = mid;
        } else {
            retVal = mid + 1;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int n;
        int bad;
    } testCase[] = {{5, 4}, {1, 1}, {2126753390, 1702766719}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, bad = %d\n", testCase[i].n, testCase[i].bad);

        BadValue = testCase[i].bad;
        answer = firstBadVersion(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
