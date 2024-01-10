#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
bool closeStrings(char* word1, char* word2) {
    bool retVal = false;

    int word1Size = strlen(word1);
    int word2Size = strlen(word2);
    if (word1Size != word2Size) {
        return retVal;
    }

#define HASHTABLE_SIZE (26)  // word1 and word2 contain only lowercase English letters.
    int hashTable1[HASHTABLE_SIZE];
    memset(hashTable1, 0, sizeof(hashTable1));
    int hashTable2[HASHTABLE_SIZE];
    memset(hashTable2, 0, sizeof(hashTable2));
    int i;
    for (i = 0; i < word1Size; ++i) {
        ++hashTable1[word1[i] - 'a'];
        ++hashTable2[word2[i] - 'a'];
    }

    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        if ((hashTable1[i] == 0) && (hashTable2[i] != 0)) {
            return retVal;
        } else if ((hashTable1[i] != 0) && (hashTable2[i] == 0)) {
            return retVal;
        }
    }

    qsort(hashTable1, HASHTABLE_SIZE, sizeof(hashTable1[0]), compareInteger);
    qsort(hashTable2, HASHTABLE_SIZE, sizeof(hashTable2[0]), compareInteger);
    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        if (hashTable1[i] != hashTable2[i]) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        char word1[MAX_SIZE];
        char word2[MAX_SIZE];
    } testCase[] = {{"abc", "bca"}, {"a", "aa"}, {"cabbba", "abbccc"}, {"uau", "ssx"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word1 = "abc", word2 = "bca"
     *  Output: true
     *
     *  Input: word1 = "a", word2 = "aa"
     *  Output: false
     *
     *  Input: word1 = "cabbba", word2 = "abbccc"
     *  Output: true
     *
     *  Input: word1 = "uau", word2 = "ssx"
     *  Output: false
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word1 = \"%s\", word2 = \"%s\"\n", testCase[i].word1, testCase[i].word2);

        answer = closeStrings(testCase[i].word1, testCase[i].word2);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
