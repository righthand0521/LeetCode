#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareString(const void* str1, const void* str2) {
    // descending order
    return strcmp(*(char**)str2, *(char**)str1);
}
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** topKFrequent(char** words, int wordsSize, int k, int* returnSize) {
    char** pRetVal = NULL;

    *returnSize = k;
    pRetVal = (char**)malloc((*returnSize) * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        *returnSize = 0;
        return pRetVal;
    }

    // descending order; Time Complexity: O(nlogn)
    qsort(words, wordsSize, sizeof(char*), compareString);

    // 1 <= words.length <= 500
#define COUNT_IDX (1000)
    int idx = 0;
    // Space Complexity: O(n)
    int count[wordsSize];
    count[idx] = idx + COUNT_IDX;
    int i;
    // Time Complexity: O(n)
    for (i = 1; i < wordsSize; ++i) {
        if (strcmp(words[i - 1], words[i]) == 0) {
            count[idx] += COUNT_IDX;
            count[i] = i;
            continue;
        }
        count[i] = i + COUNT_IDX;
        idx = i;
    }

    // descending order; Time Complexity: O(nlogn)
    qsort(count, wordsSize, sizeof(int), compareInteger);

    // Time Complexity: O(n)
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = words[count[i] % 1000];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        int k;
        int returnSize;
    } testCase[] = {{{"i", "love", "leetcode", "i", "love", "coding"}, 6, 2, 0},
                    {{"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"}, 10, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["i","love","leetcode","i","love","coding"], k = 2
     *  Output: ["i","love"]
     *
     *  Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
     *  Output: ["the","is","sunny","day"]
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pAnswer = topKFrequent(testCase[i].words, testCase[i].wordsSize, testCase[i].k, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
