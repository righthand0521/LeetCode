#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *simplifyPath(char *path) {
    char *pRetVal = NULL;

    int pathSize = strlen(path);
    char *stack[pathSize];
    int stackHead = 0;
#define SEPARATED "/"
    char *pStr = strtok(path, SEPARATED);
    while (pStr != NULL) {
        if (strcmp(pStr, ".") == 0) {
            pStr = strtok(NULL, SEPARATED);
            continue;
        }

        if (strcmp(pStr, "..") == 0) {
            if (stackHead != 0) {
                --stackHead;
                free(stack[stackHead]);
                stack[stackHead] = NULL;
            }
        } else {
            stack[stackHead] = (char *)calloc((strlen(pStr) + 1), sizeof(char));
            if (stack[stackHead] == NULL) {
                perror("calloc");
                return pRetVal;
            }
            snprintf(stack[stackHead], (strlen(pStr) + 1), "%s", pStr);
            ++stackHead;
        }
        pStr = strtok(NULL, SEPARATED);
    }

    pRetVal = (char *)calloc((pathSize + 1), sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int i;
    for (i = 0; i < stackHead; ++i) {
        snprintf(pRetVal + strlen(pRetVal), (pathSize + 1), "/%s", stack[i]);
        free(stack[i]);
        stack[i] = NULL;
    }
    if (strlen(pRetVal) == 0) {
        snprintf(pRetVal, (pathSize + 1), "/");
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (3000)
    struct testCaseType {
        char path[MAX_SIZE];
    } testCase[] = {{"/home/"}, {"/../"}, {"/home//foo/"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: path = "/home/"
     *  Output: "/home"
     *
     *  Input: path = "/../"
     *  Output: "/"
     *
     *  Input: path = "/home//foo/"
     *  Output: "/home/foo"
     */

    char *pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: path = \"%s\"\n", testCase[i].path);

        pAnswer = simplifyPath(testCase[i].path);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
