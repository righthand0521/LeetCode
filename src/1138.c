#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* alphabetBoardPath(char* target) {
    char* pRetVal = NULL;

    int len = strlen(target);
    pRetVal = (char*)calloc(10 * len, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int idx = 0;

    int src[2];
    memset(src, 0, sizeof(src));
    int dest[2];
    memset(dest, 0, sizeof(dest));
    int row, col, move;
    int i;
    for (i = 0; i < len; ++i) {
        dest[0] = (target[i] - 'a') / 5;
        dest[1] = (target[i] - 'a') % 5;

        row = dest[0] - src[0];
        col = dest[1] - src[1];

        /* Because Address of 'z'
         *  Notice that moving down and moving right, may move into a square that doesn't exist.
         *  To avoid this, we put L U before R D.
         *
         *  You may return any path that does so.
         */
        if (row < 0) {
            for (move = 0; move < abs(row); ++move) {
                pRetVal[idx++] = 'U';
            }
        }
        if (col < 0) {
            for (move = 0; move < abs(col); ++move) {
                pRetVal[idx++] = 'L';
            }
        }
        if (row > 0) {
            for (move = 0; move < abs(row); ++move) {
                pRetVal[idx++] = 'D';
            }
        }
        if (col > 0) {
            for (move = 0; move < abs(col); ++move) {
                pRetVal[idx++] = 'R';
            }
        }
        pRetVal[idx++] = '!';

        memcpy(src, dest, sizeof(src));
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char target[MAX_SIZE];
    } testCase[] = {{"leet"}, {"code"}, {"zdz"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: target = "leet"
     *  Output: "DDR!UURRR!!DDD!"
     *
     *  Input: target = "code"
     *  Output: "RR!DDRR!UUL!R!"
     *
     *  Input: target = "zdz"
     *  Output: "DDDDD!UUUUURRR!DDDDLLLD!"
     */

    char* pAnswer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: target=\"%s\"\n", testCase[i].target);

        pAnswer = alphabetBoardPath(testCase[i].target);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
