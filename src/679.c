#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARDS_SIZE (20)
const int TARGET = 24;
const double EPSILON = 1e-6;
enum Operation { ADD = 0, MULTIPLY = 1, SUBTRACT = 2, DIVIDE = 3 };
bool backtracking(double* doubleCards, int doubleCardsSize) {
    bool retVal = false;

    if (doubleCardsSize == 0) {
        return retVal;
    } else if (doubleCardsSize == 1) {
        retVal = fabs(doubleCards[0] - TARGET) < EPSILON;
        return retVal;
    }

    double copyDoubleCards[MAX_CARDS_SIZE];
    for (int i = 0; i < doubleCardsSize; i++) {
        for (int j = 0; j < doubleCardsSize; j++) {
            if (i == j) {
                continue;
            }

            memset(copyDoubleCards, 0, sizeof(copyDoubleCards));
            int copyDoubleCardsSize = 0;
            for (int k = 0; k < doubleCardsSize; k++) {
                if ((k != i) && (k != j)) {
                    copyDoubleCards[copyDoubleCardsSize++] = doubleCards[k];
                }
            }

            for (int k = 0; k < 4; k++) {
                if ((k < 2) && (i > j)) {
                    continue;
                }

                if (k == ADD) {
                    copyDoubleCards[copyDoubleCardsSize++] = doubleCards[i] + doubleCards[j];
                } else if (k == MULTIPLY) {
                    copyDoubleCards[copyDoubleCardsSize++] = doubleCards[i] * doubleCards[j];
                } else if (k == SUBTRACT) {
                    copyDoubleCards[copyDoubleCardsSize++] = doubleCards[i] - doubleCards[j];
                } else if (k == DIVIDE) {
                    if (fabs(doubleCards[j]) < EPSILON) {
                        continue;
                    }
                    copyDoubleCards[copyDoubleCardsSize++] = doubleCards[i] / doubleCards[j];
                }

                if (backtracking(copyDoubleCards, copyDoubleCardsSize) == true) {
                    retVal = true;
                    return retVal;
                }
                copyDoubleCardsSize--;
            }
        }
    }

    return retVal;
}
bool judgePoint24(int* cards, int cardsSize) {
    bool retVal = false;

    double doubleCards[MAX_CARDS_SIZE];
    memset(doubleCards, 0, sizeof(doubleCards));
    int doubleCardsSize = 0;
    for (int i = 0; i < cardsSize; i++) {
        doubleCards[doubleCardsSize++] = cards[i];
    }
    retVal = backtracking(doubleCards, doubleCardsSize);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (4)
    struct testCaseType {
        int cards[MAX_SIZE];
        int cardsSize;
    } testCase[] = {{{4, 1, 8, 7}, 4}, {{1, 2, 1, 2}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: cards = [4,1,8,7]
     *  Output: true
     *
     *  Input: cards = [1,2,1,2]
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].cardsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].cards[j]);
        }
        printf("]\n");

        answer = judgePoint24(testCase[i].cards, testCase[i].cardsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
