#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    int frequency;
} Node;
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
bool isNStraightHand(int *hand, int handSize, int groupSize) {
    bool retVal = false;

    if (handSize % groupSize != 0) {
        return retVal;
    }

    qsort(hand, handSize, sizeof(int), compareInteger);

    int i, j;

    Node *pCount = (Node *)malloc(handSize * sizeof(Node));
    if (pCount == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pCount, 0, sizeof(Node) * handSize);
    pCount[0].value = hand[0];
    pCount[0].frequency = 1;
    int cardSize = 0;
    for (i = 1; i < handSize; ++i) {
        if (hand[i] != pCount[cardSize].value) {
            cardSize++;
        }
        pCount[cardSize].value = hand[i];
        pCount[cardSize].frequency++;
    }

    int num;
    int pos = 0;
    for (i = 0; i < handSize; ++i) {
        while ((pos < cardSize) && (pCount[pos].frequency == 0)) {
            pos++;
        }

        if ((pCount[pos].value == hand[i]) && (pCount[pos].frequency > 0)) {
            for (j = 0; j < groupSize; ++j) {
                num = hand[i] + j;
                if ((pCount[pos + j].frequency > 0) && (pCount[pos + j].value == num)) {
                    pCount[pos + j].frequency--;
                } else {
                    goto exit;
                }
            }
        }
    }
    retVal = true;

exit:
    //
    free(pCount);
    pCount = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int hand[MAX_SIZE];
        int handSize;
        int groupSize;
    } testCase[] = {{{1, 2, 3, 6, 2, 3, 4, 7, 8}, 9, 3}, {{1, 2, 3, 4, 5}, 5, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
     *  Output: true
     *
     *  Input: hand = [1,2,3,4,5], groupSize = 4
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: hand = [");
        for (j = 0; j < testCase[i].handSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].hand[j]);
        }
        printf("], groupSize = %d\n", testCase[i].groupSize);

        answer = isNStraightHand(testCase[i].hand, testCase[i].handSize, testCase[i].groupSize);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
