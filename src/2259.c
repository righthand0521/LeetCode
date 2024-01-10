#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* removeDigit(char* number, char digit) {
    int len = strlen(number);
    int remove = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (number[i] != digit) {
            continue;
        }
        remove = i;

        if (((i + 1) < len) && (number[i] < number[i + 1])) {
            break;
        }
    }

    for (i = remove + 1; i < len; ++i) {
        number[i - 1] = number[i];
    }
    number[len - 1] = 0;

    return number;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100 + 4)
    struct testCaseType {
        char number[MAX_SIZE];
        char digit;
    } testCase[] = {
        {"123", '3'},
        {"1231", '1'},
        {"551", '5'},
        {"7795478535679443616467964135298543163376223791274561861738666981419251859535331546947347395531332878", '5'}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: number = \"%s\", digit = \"%c\"\n", testCase[i].number, testCase[i].digit);

        pAnswer = removeDigit(testCase[i].number, testCase[i].digit);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
