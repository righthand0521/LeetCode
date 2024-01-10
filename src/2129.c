#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* capitalizeTitle(char* title) {
    int len = strlen(title);
    int head = 0;
    int tail = 0;
    for (tail = 0; tail < len; ++tail) {
        if (title[tail] == ' ') {
            if ((tail - head) > 2) {
                title[head] = toupper(title[head]);
            }
            head = tail + 1;
        }
        (title[tail]) = tolower(title[tail]);
    }
    if ((tail - head) > 2) {
        title[head] = toupper(title[head]);
    }

    return title;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char title[MAX_SIZE];
    } testCase[] = {{"capiTalIze tHe titLe"}, {"First leTTeR of EACH Word"}, {"i lOve leetcode"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: title = \"%s\"\n", testCase[i].title);

        pAnswer = capitalizeTitle(testCase[i].title);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}