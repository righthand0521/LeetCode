#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool digitCount(char* num) {
    bool retVal = false;

#define MAX_HASH_TABLE (10 + 1)
    char HashTable[MAX_HASH_TABLE];
    memset(HashTable, '0', sizeof(HashTable));
    HashTable[sizeof(HashTable) - 1] = 0;

    int len = strlen(num);
    int i;
    for (i = 0; i < len; ++i) {
        ++HashTable[num[i] - '0'];
    }

    if (strncmp(HashTable, num, len) == 0) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
#define MAX_SIZE (10)
        char num[MAX_SIZE];
    } testCase[] = {{"1210"}, {"030"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    bool answer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = \"%s\"\n", testCase[i].num);

        answer = digitCount(testCase[i].num);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
