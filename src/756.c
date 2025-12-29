#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/pyramid-transition-matrix/solutions/3866474/tu-jie-hui-su-vis-you-hua-pythonjavacgo-9kcb9/
#define MAXN (20)
#define MAXGROUP (7)
#define MAXTOPS (10)
bool dfs(int groups[MAXGROUP][MAXGROUP][MAXTOPS], int groupSize[MAXGROUP][MAXGROUP], int* pyramid, unsigned int* vis,
         int i, int j) {
    bool retVal = false;

    if (i < 0) {
        retVal = true;
    } else if (vis[pyramid[i]]) {
        retVal = false;
    } else if (j == i + 1) {
        vis[pyramid[i]] = 1;
        retVal = dfs(groups, groupSize, pyramid, vis, i - 1, 0);
    } else {
        int left = (pyramid[i + 1] >> (j * 3)) & 7;
        int right = (pyramid[i + 1] >> ((j + 1) * 3)) & 7;
        for (int k = 0; k < groupSize[left][right]; k++) {
            int top = groups[left][right][k];
            pyramid[i] &= ~(7 << (j * 3));
            pyramid[i] |= top << (j * 3);
            if (dfs(groups, groupSize, pyramid, vis, i, j + 1)) {
                retVal = true;
                break;
            }
        }
    }

    return retVal;
}
bool pyramidTransition(const char* bottom, char** allowed, int allowedSize) {
    bool retVal = false;

    int groups[MAXGROUP][MAXGROUP][MAXTOPS];
    int groupSize[MAXGROUP][MAXGROUP];
    memset(groups, 0, sizeof(groups));
    memset(groupSize, 0, sizeof(groupSize));

    for (int idx = 0; idx < allowedSize; idx++) {
        char* s = allowed[idx];
        int a = s[0] & 31;
        int b = s[1] & 31;
        int c = s[2] & 31;
        groups[a][b][groupSize[a][b]++] = c;
    }

    int bottomSize = strlen(bottom);
    int pyramid[MAXN] = {0};
    for (int i = 0; i < bottomSize; i++) {
        pyramid[bottomSize - 1] |= (bottom[i] & 31) << (i * 3);
    }

    unsigned int* vis = (unsigned int*)calloc(1 << ((bottomSize - 1) * 3), sizeof(unsigned int));

    retVal = dfs(groups, groupSize, pyramid, vis, bottomSize - 2, 0);

    //
    free(vis);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (216)
    struct testCaseType {
        char* bottom;
        char* allowed[MAX_SIZE];
        int allowedSize;
    } testCase[] = {{"BCD", {"BCC", "CDE", "CEA", "FFF"}, 4}, {"AAAA", {"AAB", "AAC", "BCD", "BBE", "DEF"}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
     *  Output: true
     *
     *  Input: bottom = "AAAA", allowed = ["AAB","AAC","BCD","BBE","DEF"]
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: bottom = %s, allowed = [", testCase[i].bottom);
        for (j = 0; j < testCase[i].allowedSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", testCase[i].allowed[j]);
        }
        printf("]\n");

        answer = pyramidTransition(testCase[i].bottom, testCase[i].allowed, testCase[i].allowedSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
