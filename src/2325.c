#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decodeMessage(char* key, char* message) {
    char* pRetVal = NULL;

    int messageLen = strlen(message);
    pRetVal = (char*)malloc((messageLen + 1) * sizeof(char));
    if (pRetVal == NULL) {
        perror("mmalloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((messageLen + 1) * sizeof(char)));

// key consists of lowercase English letters and ' '.
#define MAX_HASHTABLE (26)
    char HashTable[MAX_HASHTABLE];
    memset(HashTable, 0, sizeof(HashTable));
    int keyLen = strlen(key);
    int index = 0;
    int HashTableUse = 0;
    int i;
    for (i = 0; i < keyLen; ++i) {
        if (key[i] == ' ') {
            continue;
        }

        if (HashTableUse == MAX_HASHTABLE) {
            break;
        }

        index = key[i] - 'a';
        if (HashTable[index] == 0) {
            HashTable[index] = HashTableUse + 'a';
            ++HashTableUse;
        }
    }

    for (i = 0; i < messageLen; ++i) {
        if (message[i] == ' ') {
            pRetVal[i] = ' ';
            continue;
        }

        index = message[i] - 'a';
        pRetVal[i] = HashTable[index];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
#define MAX_SIZE (2000)
        char key[MAX_SIZE];
        char message[MAX_SIZE];
    } testCase[] = {{"the quick brown fox jumps over the lazy dog", "vkbs bs t suepuv"},
                    {"eljuxhpwnyrdgtqkviszcfmabo", "zwx hnfx lqantp mnoeius ycgk vcnjrdb"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: key = \"%s\", message = \"%s\"\n", testCase[i].key, testCase[i].message);

        pAnswer = decodeMessage(testCase[i].key, testCase[i].message);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
