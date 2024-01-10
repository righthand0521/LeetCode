#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxConsecutiveAnswers(char* answerKey, int k) {
    int retVal = 0;

    // answerKey[i] is either 'T' or 'F'
#define MAX_RECORD (26)
    int Record[MAX_RECORD];
    memset(Record, 0, sizeof(Record));

    int maxRecord = 0;
    int answerKeySize = strlen(answerKey);
    int left = 0;
    int right = 0;
    while (right < answerKeySize) {
        Record[answerKey[right] - 'A']++;

        maxRecord = fmax(maxRecord, Record[answerKey[right] - 'A']);
        if (right - left + 1 - maxRecord > k) {
            Record[answerKey[left] - 'A']--;
            left++;
        }

        right++;
    }
    retVal = right - left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        char answerKey[MAX_SIZE];
        int k;
    } testCase[] = {{"TTFF", 2}, {"TFFT", 1}, {"TTFTTFTT", 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: answerKey = "TTFF", k = 2
     *  Output: 4
     *
     *  Input: answerKey = "TFFT", k = 1
     *  Output: 3
     *
     *  Input: answerKey = "TTFTTFTT", k = 1
     *  Output: 5
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; i++) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].answerKey, testCase[i].k);

        answer = maxConsecutiveAnswers(testCase[i].answerKey, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
