#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPalindrome(int x) {
    bool retVal = false;

    if (x < 0) {
        return retVal;
    }

    // Constraints: -2 ^ 31 <= x <= 2 ^ 31 - 1
    long original = x;
    long palindrome = 0;
    while (x > 0) {
        palindrome *= 10;
        palindrome += (x % 10);
        x /= 10;
    }

    if (original == palindrome) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int x;
    } testCase[] = {{121}, {-121}, {10}, {1234567899}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: x = 121
     *  Output: true
     *
     *  Input: x = -121
     *  Output: false
     *
     *  Input: x = 10
     *  Output: false
     *
     *  Input: x = 1234567899
     *  Output: false
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: x = %d\n", testCase[i].x);

        answer = isPalindrome(testCase[i].x);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
