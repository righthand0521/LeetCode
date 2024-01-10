#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find(int* pUnionFind, int idx) {
    while (pUnionFind[idx] != idx) {
        idx = pUnionFind[idx];
    }

    return idx;
}
void join(int* pUnionFind, int idx1, int idx2) {
    int root1 = find(pUnionFind, idx1);
    int root2 = find(pUnionFind, idx2);
    if (root1 == root2) {
        return;
    }

    if (root1 <= root2) {
        pUnionFind[root2] = root1;
    } else {
        pUnionFind[root1] = root2;
    }
}
char* smallestEquivalentString(char* s1, char* s2, char* baseStr) {
    char* pRetVal = NULL;

    int i;

// s1, s2, and baseStr consist of lowercase English letters.
#define MAX_UNION_FIND (26)
    int UnionFind[MAX_UNION_FIND];
    for (i = 0; i < MAX_UNION_FIND; ++i) {
        UnionFind[i] = i;
    }

    int len = strlen(s1);
    for (i = 0; i < len; ++i) {
        join(UnionFind, s1[i] - 'a', s2[i] - 'a');
    }

    len = strlen(baseStr);
    int returnSize = len + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, returnSize * sizeof(char));
    for (i = 0; i < len; ++i) {
        pRetVal[i] = (char)(find(UnionFind, baseStr[i] - 'a') + 'a');
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char s1[MAX_SIZE];
        char s2[MAX_SIZE];
        char baseStr[MAX_SIZE];
    } testCase[] = {{"parker", "morris", "parser"}, {"hello", "world", "hold"}, {"leetcode", "programs", "sourcecode"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s1 = \"%s\", s2 = \"%s\", baseStr = \"%s\"\n", testCase[i].s1, testCase[i].s2,
               testCase[i].baseStr);

        pAnswer = smallestEquivalentString(testCase[i].s1, testCase[i].s2, testCase[i].baseStr);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
