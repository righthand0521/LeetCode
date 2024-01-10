#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* intToRoman(int num) {
    char* pRetVal = NULL;

#define MAX_ROMAN_SIZE (16)
    pRetVal = (char*)malloc(MAX_ROMAN_SIZE * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (MAX_ROMAN_SIZE * sizeof(char)));

    struct Map {
        int value;
        char* symbol;
    } romanMapping[] = {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"},
                        {40, "XL"},  {10, "X"},   {9, "IX"},  {5, "V"},    {4, "IV"},  {1, "I"}};
    int numberOfRoman = sizeof(romanMapping) / sizeof(romanMapping[0]);

    int i;
    for (i = 0; i < numberOfRoman; ++i) {
        while ((num > 0) && ((num - romanMapping[i].value) >= 0)) {
            num -= romanMapping[i].value;
            strncat(pRetVal, romanMapping[i].symbol, MAX_ROMAN_SIZE - strlen(pRetVal));
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int num;
    } testCase[] = {{3}, {58}, {1994}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = 3
     *  Output: "III"
     *
     *  Input: num = 58
     *  Output: "LVIII"
     *
     *  Input: num = 1994
     *  Output: "MCMXCIV"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num  = %d\n", testCase[i].num);

        pAnswer = intToRoman(testCase[i].num);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
